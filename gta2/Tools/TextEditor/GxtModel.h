#ifndef __TOOLS_TEXT_GXT_MODEL_H_
#define __TOOLS_TEXT_GXT_MODEL_H_

#include <QAbstractTableModel>
#include <QVector>
#include <QString>
#include <QHash>
#include "GxtFormat.h"

// Модель таблицы строк .gxt для редактора текстов.
// Колонки: Ключ | Текст | Оригинал (если открыт файл-Справка).
// Поддерживается фильтр по ключу/тексту; правка только колонки «Текст».
class GxtModel : public QAbstractTableModel {
	Q_OBJECT
public:
	explicit GxtModel(QObject* parent = NULL);

	void setFile(gta2::GxtFile* g);            // редактируемый файл
	void setReference(const gta2::GxtFile* r); // справочный файл (перевод-исходник)
	void setFilter(const QString& f);          // фильтр строк
	void refresh();                            // пересчёт видимых строк (после add/del)

	gta2::GxtFile* file() const { return m_g; }
	int sourceIndex(int row) const { return (row >= 0 && row < m_rowMap.size()) ? m_rowMap[row] : -1; }

signals:
	void edited(); // текст строки изменён через редактор таблицы

public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex& index) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
	void rebuild();
	gta2::GxtFile* m_g;
	const gta2::GxtFile* m_ref;
	QHash<QString, int> m_refIndex; // ключ -> индекс в справочнике
	QString m_filter;
	QVector<int> m_rowMap; // номер строки таблицы -> индекс строки в .gxt
};

#endif // !__TOOLS_TEXT_GXT_MODEL_H_