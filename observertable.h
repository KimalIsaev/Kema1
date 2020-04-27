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
    void updateSize(FileObserver*);
public:
    ObserverTable();
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void add(const QString &path);
    void del(const QModelIndexList&);
    void rename(const QModelIndexList&, const QString &path);
    bool insertRows(int row, int count, const QModelIndex &index) override;
    bool removeRows(int row, int count, const QModelIndex &index) override;
};

#endif // QOBSERVERTABLE_H
