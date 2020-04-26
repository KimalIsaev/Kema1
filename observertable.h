#ifndef QOBSERVERTABLE_H
#define QOBSERVERTABLE_H
#include "filesizescreamer.h"
#include <QAbstractTableModel>

class ObserverTable : public QAbstractTableModel
{
    QList<QPointer<FileObserver>> observerList;
    static const constexpr int pathColumn = 0;
    static const constexpr int sizeColumn = 1;
    static const constexpr int numberOfColumns = 2;
    FileSizeScreamer* ScreamerInstance = FileSizeScreamer::getInstance();
public:
    ObserverTable();
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void add(const QString &path);
    void del(const QModelIndexList&);
    void rename(const QModelIndexList&, const QString &path);
};

#endif // QOBSERVERTABLE_H
