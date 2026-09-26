#include "HexView.h"
#include "SaveFile.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QFontDatabase>
#include <QPushButton>
#include <QFileInfo>

// ===========================================================================
MissionTableView::MissionTableView(QWidget *parent) : QWidget(parent)
{
    buildUi();
}

void MissionTableView::buildUi()
{
    QVBoxLayout *v = new QVBoxLayout(this);

    QLabel *hint = new QLabel(
        tr("<b>Map-derived, not player state.</b> MissionManager::sub_47EE70 walks all 6000 "
           "script slots and rebuilds this table on <i>every</i> save, keeping only markers of "
           "type 275/276. That is why the id range differs per map (wil starts at 414, bil at 67) "
           "but is identical for every slot of the same map. Editing it here would have no effect - "
           "the game overwrites it. The per-mission progress bits at 0x12C/0x130 index RAM arrays "
           "that are never saved, which is why forcing them crashes the load."),
        this);
    hint->setWordWrap(true);
    v->addWidget(hint);

    m_summary = new QLabel(this);
    QFont mono = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    m_summary->setFont(mono);
    v->addWidget(m_summary);

    m_table = new QTableWidget(300, 4, this);
    m_table->setHorizontalHeaderLabels({ tr("#"), tr("offset"), tr("id"), tr("extra") });
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setVisible(false);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setFont(mono);
    v->addWidget(m_table, 1);
}

void MissionTableView::setSave(SaveFile *save)
{
    m_save = save;
    reload();
}

void MissionTableView::reload()
{
    if (!m_save || !m_save->hasSvg())
        return;
    const QVector<SaveFile::MissionRow> rows = m_save->missions();
    for (int i = 0; i < rows.size(); ++i) {
        const SaveFile::MissionRow &r = rows.at(i);
        m_table->setItem(i, 0, new QTableWidgetItem(QString::number(r.index)));
        m_table->setItem(i, 1, new QTableWidgetItem(
            QString("0x%1").arg(r.off, 4, 16, QLatin1Char('0')).toUpper()));
        m_table->setItem(i, 2, new QTableWidgetItem(r.used ? QString::number(r.id) : QString("-")));
        m_table->setItem(i, 3, new QTableWidgetItem(r.extra ? QString::number(r.extra) : QString("-")));
        if (!r.used)
            for (int c = 0; c < 4; ++c)
                if (QTableWidgetItem *it = m_table->item(i, c))
                    it->setForeground(QColor(0x88, 0x88, 0x88));
    }
    m_summary->setText(tr("count field @0x12A = %1    non-empty rows = %2    of 300 slots")
                        .arg(m_save->missionCountField())
                        .arg(m_save->missionUsedCount()));
}

// ===========================================================================
HexView::HexView(QWidget *parent) : QWidget(parent)
{
    buildUi();
}

void HexView::buildUi()
{
    QVBoxLayout *v = new QVBoxLayout(this);

    QHBoxLayout *row = new QHBoxLayout;
    row->addWidget(new QLabel(tr("Region:"), this));
    m_target = new QComboBox(this);
    m_target->addItem(tr("block0 (1864 B)"),      int(Target::Block0));
    m_target->addItem(tr("whole .svg"),          int(Target::SvgFile));
    m_target->addItem(tr(".dat records"),         int(Target::Dat));
    row->addWidget(m_target, 1);
    QPushButton *refresh = new QPushButton(tr("Refresh"), this);
    row->addWidget(refresh);
    v->addLayout(row);

    m_text = new QPlainTextEdit(this);
    m_text->setReadOnly(true);
    m_text->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_text->setLineWrapMode(QPlainTextEdit::NoWrap);
    v->addWidget(m_text, 1);

    connect(m_target, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this]{ reload(); });
    connect(refresh, &QPushButton::clicked, this, &HexView::reload);
}

void HexView::setSave(SaveFile *save)
{
    m_save = save;
    reload();
}

void HexView::setTarget(Target t)
{
    const int idx = m_target->findData(int(t));
    if (idx >= 0)
        m_target->setCurrentIndex(idx);
    reload();
}

void HexView::reload()
{
    m_text->clear();
    if (!m_save)
        return;
    const Target t = Target(m_target->currentData().toInt());

    QByteArray bytes;
    QString title;
    switch (t) {
    case Target::Block0:
        if (!m_save->hasSvg()) { m_text->setPlainText(tr("no .svg loaded")); return; }
        bytes = m_save->block0();
        title = tr("block0 of %1").arg(QFileInfo(m_save->svgPath()).fileName());
        break;
    case Target::SvgFile: {
        if (!m_save->hasSvg()) { m_text->setPlainText(tr("no .svg loaded")); return; }
        // reassemble the on-disk image: block0 + [u32 len][data] * 3
        for (char c : m_save->block0()) bytes.append(c);
        for (const QByteArray &blk : m_save->trailing()) {
            const quint32 len = static_cast<quint32>(blk.size());
            for (int i = 0; i < 4; ++i) bytes.append(char((len >> (8 * i)) & 0xFF));
            bytes.append(blk);
        }
        title = tr("full .svg image (%1 B)").arg(bytes.size());
        break;
    }
    case Target::Dat: {
        if (!m_save->hasDat()) { m_text->setPlainText(tr("no .dat loaded")); return; }
        // the .dat is private to SaveFile, so show the decoded records instead
        QStringList out;
        out << tr("player = '%1'    header = 18 B    12 records x 9 B")
                   .arg(m_save->datPlayerName());
        out << QString("rec arena sub flag      best          last");
        for (int i = 0; i < SaveFile::kDatRecCount; ++i) {
            out << QString("%1  %2    %3   %4   %5   %6")
                       .arg(i, 3).arg(i / 4, 5).arg(i % 4, 3)
                       .arg(m_save->datFlag(i), 4)
                       .arg(m_save->datBest(i), 11)
                       .arg(m_save->datLast(i), 11);
        }
        m_text->setPlainText(out.join('\n'));
        return;
    }
    }

    QStringList out;
    out << title;
    for (int row = 0; row * 16 < bytes.size(); ++row) {
        QString hex, asc;
        const int base = row * 16;
        for (int i = 0; i < 16; ++i) {
            if (base + i < bytes.size()) {
                const quint8 b = static_cast<quint8>(bytes[base + i]);
                hex += QString("%1 ").arg(b, 2, 16, QLatin1Char('0')).toUpper();
                asc += (b >= 0x20 && b < 0x7F) ? QChar(b) : QLatin1Char('.');
            } else {
                hex += QString("   ");
                asc += QLatin1Char(' ');
            }
        }
        out << QString("%1  %2  %3")
                   .arg(QString("%1").arg(base, 6, 16, QLatin1Char('0')).toUpper(), -7)
                   .arg(hex, -48).arg(asc);
    }
    m_text->setPlainText(out.join('\n'));
}
