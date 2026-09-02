#include "GxtModel.h"

#include <QBrush>
#include <QColor>

GxtModel::GxtModel(QObject* parent)
	: QAbstractTableModel(parent), m_g(NULL), m_ref(NULL)
{
}

void GxtModel::setFile(gta2::GxtFile* g)
{
	m_g = g;
	rebuild();
}

void GxtModel::setReference(const gta2::GxtFile* r)
{
	m_ref = r;
	m_refIndex.clear();
	if (r) {
		for (int i = 0; i < (int)r->Strings().size(); i++)
			m_refIndex.insert(QString::fromStdString(r->Strings()[i].key), i);
	}
	rebuild();
}

void GxtModel::refresh()
{
	rebuild();
}

void GxtModel::setFilter(const QString& f)
{
	m_filter = f;
	rebuild();
}

void GxtModel::rebuild()
{
	beginResetModel();
	m_rowMap.clear();
	if (!m_g) {
		endResetModel();
		return;
	}
	for (int i = 0; i < (int)m_g->Strings().size(); i++) {
		const gta2::GxtString& s = m_g->Strings()[i];
		if (m_filter.isEmpty())
			m_rowMap.push_back(i);
		else {
			QString key = QString::fromStdString(s.key);
			QString text = QString::fromStdWString(s.text);
			QString ref = m_ref ? QString::fromStdWString(m_ref->Strings()[m_refIndex.value(key, -1)].text) : QString();
			if (key.contains(m_filter, Qt::CaseInsensitive) ||
			    text.contains(m_filter, Qt::CaseInsensitive) ||
			    (!ref.isEmpty() && ref.contains(m_filter, Qt::CaseInsensitive)))
				m_rowMap.push_back(i);
		}
	}
	endResetModel();
}

int GxtModel::rowCount(const QModelIndex& parent) const
{
	return parent.isValid() ? 0 : m_rowMap.size();
}

int GxtModel::columnCount(const QModelIndex& parent) const
{
	return parent.isValid() ? 0 : (m_ref ? 3 : 2);
}

QVariant GxtModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || !m_g)
		return QVariant();
	int src = sourceIndex(index.row());
	if (src < 0 || src >= (int)m_g->Strings().size())
		return QVariant();
	const gta2::GxtString& s = m_g->Strings()[src];

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		switch (index.column()) {
		case 0: return QString::fromStdString(s.key);
		case 1: return QString::fromStdWString(s.text);
		case 2: {
			if (!m_ref) return QVariant();
			int ri = m_refIndex.value(QString::fromStdString(s.key), -1);
			if (ri < 0) return QVariant();
			return QString::fromStdWString(m_ref->Strings()[ri].text);
		}
		}
		return QVariant();
	}

	if (role == Qt::ForegroundRole) {
		if (index.column() == 0)
			return QBrush(QColor(120, 120, 120));
		if (index.column() == 1 && s.text.empty())
			return QBrush(QColor(190, 60, 60));
	}

	if (role == Qt::BackgroundRole) {
		if (!m_ref) return QVariant();
		int ri = m_refIndex.value(QString::fromStdString(s.key), -1);
		if (ri >= 0 && m_ref->Strings()[ri].text != s.text)
			return QBrush(QColor(255, 244, 214)); // отличающиеся от оригинала
	}

	if (role == Qt::TextAlignmentRole) {
		if (index.column() == 0)
			return (int)(Qt::AlignRight | Qt::AlignVCenter);
	}

	return QVariant();
}

Qt::ItemFlags GxtModel::flags(const QModelIndex& index) const
{
	if (!index.isValid() || !m_g)
		return Qt::NoItemFlags;
	Qt::ItemFlags f = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	if (index.column() == 1)
		f |= Qt::ItemIsEditable;
	return f;
}

bool GxtModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid() || role != Qt::EditRole || index.column() != 1 || !m_g)
		return false;
	int src = sourceIndex(index.row());
	if (src < 0)
		return false;
	if (!m_g->SetText((size_t)src, value.toString().toStdWString()))
		return false;
	emit dataChanged(index, index);
	emit edited();
	return true;
}

QVariant GxtModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
		return QVariant();
	switch (section) {
	case 0: return QString::fromUtf8("Ключ");
	case 1: return QString::fromUtf8("Текст (этот язык)");
	case 2: return QString::fromUtf8("Оригинал (справка)");
	}
	return QVariant();
}