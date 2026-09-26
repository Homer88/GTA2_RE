#include "FieldEditor.h"
#include "SaveFile.h"

#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QSignalBlocker>
#include <QFontDatabase>
#include <algorithm>
#include <climits>

namespace {
QString hexLabel(int off, int w)
{
    return QString("0x%1").arg(off, 4, 16, QLatin1Char('0')).toUpper()
         + (w > 1 ? QString("  (%1 B)").arg(w) : QString());
}
} // namespace

FieldEditor::FieldEditor(QWidget *parent)
    : QWidget(parent)
{
    buildUi();
}

QWidget *FieldEditor::makeEditor(const FieldDef &def, QWidget **outEditor,
                                 QCheckBox **outLock)
{
    QWidget *row = new QWidget(this);
    QHBoxLayout *h = new QHBoxLayout(row);
    h->setContentsMargins(0, 0, 0, 0);
    h->setSpacing(6);

    QWidget *editor = nullptr;

    if (def.kind == FieldKind::Name) {
        QLineEdit *e = new QLineEdit(row);
        e->setMaxLength(24);
        e->setPlaceholderText(QObject::tr("data\\wil.gmp"));
        e->setToolTip(def.note);
        editor = e;
    } else {
        QSpinBox *s = new QSpinBox(row);
        // Qt5.14 tops QSpinBox at INT_MAX; the money field is a full u32, so
        // widen it by hand when the manifest allows more than INT_MAX.
        const quint32 hi = def.max;
        const int spinHi = (hi > static_cast<quint32>(INT_MAX))
                         ? static_cast<int>(std::min<quint64>(hi, 0x7FFFFFFFu))
                         : static_cast<int>(hi);
        s->setRange(static_cast<int>(def.min), spinHi);
        if (hi > static_cast<quint32>(INT_MAX))
            s->setDisplayIntegerBase(10);
        s->setToolTip(def.note);
        s->setKeyboardTracking(false);   // no per-keystroke apply
        editor = s;
    }
    *outEditor = editor;

    // Per-field override so a read-only (dangerous) field can still be poked at
    // deliberately, and a normal field can be pinned if we are mid-experiment.
    QCheckBox *lock = new QCheckBox(row);
    lock->setChecked(!def.editable);
    lock->setToolTip(def.editable
        ? QObject::tr("Pin this field: ignore edits instead of applying them")
        : QObject::tr("Unsafe: tick to allow editing anyway"));
    *outLock = lock;

    h->addWidget(editor, 1);
    h->addWidget(lock);
    return row;
}

void FieldEditor::buildUi()
{
    QVBoxLayout *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    outer->addWidget(scroll);

    QWidget *host = new QWidget(scroll);
    QVBoxLayout *hostLayout = new QVBoxLayout(host);

    // One group box per FieldGroup, in manifest order.
    QVector<FieldGroup> order = {
        FieldGroup::Identity, FieldGroup::Progress, FieldGroup::Bonuses,
        FieldGroup::Gangs, FieldGroup::Arsenal, FieldGroup::Internals,
        FieldGroup::Dangerous
    };

    for (FieldGroup g : order) {
        const QVector<FieldDef> &defs = fieldDefs();
        QVector<FieldDef> inGroup;
        for (const FieldDef &d : defs)
            if (d.group == g) inGroup.append(d);
        if (inGroup.isEmpty()) continue;

        QGroupBox *box = new QGroupBox(fieldGroupTitle(g), host);
        if (g == FieldGroup::Dangerous) {
            QFont f = box->font();
            f.setBold(true);
            box->setFont(f);
        }
        QFormLayout *form = new QFormLayout(box);
        form->setLabelAlignment(Qt::AlignRight);
        form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

        for (const FieldDef &d : inGroup) {
            Slot s;
            s.def = d;
            QWidget *row = makeEditor(d, &s.editor, &s.lock);
            form->addRow(QString("%1\n%2").arg(d.label).arg(hexLabel(d.off, d.width())), row);
            m_slots.append(s);
        }
        hostLayout->addWidget(box);
    }

    hostLayout->addStretch(1);
    scroll->setWidget(host);
}

void FieldEditor::setSave(SaveFile *save)
{
    m_save = save;
    m_dirty = false;
    emit dirtyChanged(false);
    reload();
}

quint32 FieldEditor::currentValue(const Slot &s) const
{
    if (s.def.kind == FieldKind::Name)
        return 0;
    if (auto *sb = qobject_cast<QSpinBox *>(s.editor))
        return static_cast<quint32>(sb->value());
    return 0;
}

void FieldEditor::setCurrentValue(Slot &s, quint32 v)
{
    if (auto *sb = qobject_cast<QSpinBox *>(s.editor)) {
        QSignalBlocker b(sb);
        sb->setValue(static_cast<int>(v));
    }
}

void FieldEditor::reload()
{
    if (!m_save || !m_save->hasSvg())
        return;
    for (Slot &s : m_slots) {
        if (!s.editor) continue;
        if (s.def.kind == FieldKind::Name) {
            if (auto *le = qobject_cast<QLineEdit *>(s.editor)) {
                QSignalBlocker b(le);
                le->setText(m_save->nameAt(s.def.off));
            }
            continue;
        }
        quint32 v = 0;
        switch (s.def.size) {
        case 1: v = m_save->u8 (s.def.off); break;
        case 2: v = m_save->u16(s.def.off); break;
        case 4: v = m_save->u32(s.def.off); break;
        default: break;
        }
        setCurrentValue(s, v);
    }
    refreshLocks();
    m_dirty = false;
    emit dirtyChanged(false);
}

void FieldEditor::refreshLocks()
{
    for (const Slot &s : m_slots) {
        if (!s.editor || !s.lock) continue;
        const bool allowed = !s.lock->isChecked();
        s.editor->setEnabled(allowed);
        if (auto *le = qobject_cast<QLineEdit *>(s.editor))
            le->setReadOnly(!allowed);
    }
}

bool FieldEditor::hasPendingEdits() const
{
    if (!m_save || !m_save->hasSvg())
        return false;
    for (const Slot &s : m_slots) {
        if (!s.editor) continue;
        if (s.def.kind == FieldKind::Name) {
            auto *le = qobject_cast<QLineEdit *>(s.editor);
            if (le && !s.lock->isChecked() && le->text() != m_save->nameAt(s.def.off))
                return true;
            continue;
        }
        if (s.lock->isChecked())
            continue;
        quint32 cur = 0;
        switch (s.def.size) {
        case 1: cur = m_save->u8 (s.def.off); break;
        case 2: cur = m_save->u16(s.def.off); break;
        case 4: cur = m_save->u32(s.def.off); break;
        default: break;
        }
        if (currentValue(s) != cur)
            return true;
    }
    return false;
}

bool FieldEditor::apply()
{
    if (!m_save || !m_save->hasSvg())
        return false;

    int written = 0;
    for (Slot &s : m_slots) {
        if (!s.editor || s.lock->isChecked())
            continue;   // pinned or not-permitted

        if (s.def.kind == FieldKind::Name) {
            auto *le = qobject_cast<QLineEdit *>(s.editor);
            if (!le) continue;
            const QString text = le->text().trimmed();
            if (text != m_save->nameAt(s.def.off)) {
                m_save->setNameAt(s.def.off, text);
                ++written;
            }
            continue;
        }

        const quint32 v = currentValue(s);
        quint32 old = 0;
        switch (s.def.size) {
        case 1: old = m_save->u8 (s.def.off); break;
        case 2: old = m_save->u16(s.def.off); break;
        case 4: old = m_save->u32(s.def.off); break;
        default: break;
        }
        if (v == old)
            continue;
        switch (s.def.size) {
        case 1: m_save->setU8 (s.def.off, static_cast<quint8 >(v)); break;
        case 2: m_save->setU16(s.def.off, static_cast<quint16>(v)); break;
        case 4: m_save->setU32(s.def.off, static_cast<quint32>(v)); break;
        default: break;
        }
        ++written;
    }

    m_dirty = false;
    emit dirtyChanged(false);
    return written > 0;
}
