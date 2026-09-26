#include "DatTable.h"
#include "SaveFile.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalBlocker>
#include <QFontDatabase>

DatTable::DatTable(QWidget *parent)
    : QWidget(parent)
{
    buildUi();
}

void DatTable::buildUi()
{
    QVBoxLayout *v = new QVBoxLayout(this);

    QLabel *hint = new QLabel(
        tr("best / last are <b>money</b> snapshots written by PlayerData::sub_4A8F90 - "
           "they are not a score. Record index maps to location as arena = idx/4, sub = idx%4."),
        this);
    hint->setWordWrap(true);
    v->addWidget(hint);

    QHBoxLayout *nameRow = new QHBoxLayout;
    nameRow->addWidget(new QLabel(tr("Player name:"), this));
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setMaxLength(5);
    nameRow->addWidget(m_nameEdit, 1);
    v->addLayout(nameRow);

    m_table = new QTableWidget(SaveFile::kDatRecCount, 6, this);
    m_table->setHorizontalHeaderLabels(
        { tr("rec"), tr("arena"), tr("sub"), tr("flag"), tr("best (money)"), tr("last (money)") });
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setVisible(false);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setEditTriggers(QAbstractItemView::DoubleClicked
                             | QAbstractItemView::EditKeyPressed
                             | QAbstractItemView::AnyKeyPressed);
    m_table->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    v->addWidget(m_table, 1);

    QHBoxLayout *btnRow = new QHBoxLayout;
    btnRow->addStretch(1);
    QPushButton *reload = new QPushButton(tr("Discard edits"), this);
    QPushButton *apply  = new QPushButton(tr("Apply to .dat"), this);
    btnRow->addWidget(reload);
    btnRow->addWidget(apply);
    v->addLayout(btnRow);

    connect(reload, &QPushButton::clicked, this, &DatTable::reload);
    connect(apply,  &QPushButton::clicked, this, [this]{ this->apply(); });
}

void DatTable::setSave(SaveFile *save)
{
    m_save = save;
    m_dirty = false;
    emit dirtyChanged(false);
    reload();
}

void DatTable::reload()
{
    if (!m_save || !m_save->hasDat())
        return;
    m_loading = true;

    if (auto *le = qobject_cast<QLineEdit *>(m_nameEdit)) {
        QSignalBlocker b(le);
        le->setText(m_save->datPlayerName());
        le->setEnabled(true);
    }

    for (int i = 0; i < SaveFile::kDatRecCount; ++i) {
        m_table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        m_table->item(i, 0)->setFlags(Qt::ItemIsEnabled);
        m_table->setItem(i, 1, new QTableWidgetItem(QString::number(i / 4)));
        m_table->item(i, 1)->setFlags(Qt::ItemIsEnabled);
        m_table->setItem(i, 2, new QTableWidgetItem(QString::number(i % 4)));
        m_table->item(i, 2)->setFlags(Qt::ItemIsEnabled);
        m_table->setItem(i, 3, new QTableWidgetItem(QString::number(m_save->datFlag(i))));
        m_table->setItem(i, 4, new QTableWidgetItem(QString::number(m_save->datBest(i))));
        m_table->setItem(i, 5, new QTableWidgetItem(QString::number(m_save->datLast(i))));
    }
    m_loading = false;
    m_dirty = false;
    emit dirtyChanged(false);
}

bool DatTable::apply()
{
    if (!m_save || !m_save->hasDat())
        return false;
    m_loading = true;

    for (int i = 0; i < SaveFile::kDatRecCount; ++i) {
        if (QTableWidgetItem *it = m_table->item(i, 3))
            m_save->setDatFlag(i, static_cast<quint8>(it->text().toUInt()));
        if (QTableWidgetItem *it = m_table->item(i, 4))
            m_save->setDatBest(i, it->text().toUInt());
        if (QTableWidgetItem *it = m_table->item(i, 5))
            m_save->setDatLast(i, it->text().toUInt());
    }
    if (auto *le = qobject_cast<QLineEdit *>(m_nameEdit))
        m_save->setDatPlayerName(le->text());

    m_loading = false;
    m_dirty = false;
    emit dirtyChanged(false);
    return true;
}
