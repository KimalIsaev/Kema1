#ifndef QOBSERVERTABLE_H
#define QOBSERVERTABLE_H
#include "filesizescreamer.h"
#include <QAbstractTableModel>

class ObserverTable : public QAbstractTableModel
{
    QList<QPointer<FileObserver>> observerList;
    static const constexpr uchar pathColumn = 0;
    static const constexpr uchar sizeColumn = 1;
public:
    ObserverTable();
    Qt::ItemFlags flags(const QModelIndex & index) const;
};

#endif // QOBSERVERTABLE_H
