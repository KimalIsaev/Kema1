#include "observertable.h"
#include <iostream>
ObserverTable::ObserverTable()
{

}

void ObserverTable::add(const QString& path){
    insertRow(observerList.size());
    observerList[observerList.size()-1]->rename(path);
    ScreamerInstance->refreshObserver(path);
    emit dataChanged(QAbstractItemModel::createIndex(observerList.size()-1, 0),
                     QAbstractItemModel::createIndex(observerList.size()-1, numberOfColumns-1),
                     {Qt::DisplayRole});
}

bool ObserverTable::insertRows(int row, int count, const QModelIndex& index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), row, row+count-1);
    std::cout << count << std::endl;
    for (int i=0; i < count; i++) {
        QPointer<FileObserver> newObserver(new FileObserver(""));
        observerList.append(newObserver);
        QObject :: connect(ScreamerInstance, &FileSizeScreamer::fileWasChanged, newObserver.data(), &FileObserver::fileIsChanged);
    }

    endInsertRows();
    return true;
}

QList<int> indexListToRowList(const QModelIndexList& indexList){
    QList<int> rowList;
    for(QModelIndex index: indexList)
        rowList.append(index.row());
    return rowList;
}

void ObserverTable::del(const QModelIndexList& indexList){
    if (!indexList.empty()){
        QList<int> rowList = indexListToRowList(indexList);
        std::sort(rowList.begin(), rowList.end());
        int k=0;
        for (int i: rowList){
            removeRow(i-k);
            k++;
        }
    }
}

bool ObserverTable::removeRows(int row, int count, const QModelIndex& index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), row, row+count-1);
    for (int i=0; i < count; ++i) {
        delete observerList[i].data();
        observerList.removeAt(i);
    }
    endRemoveRows();
    return true;
}

void ObserverTable::rename(const QModelIndexList& indexList, const QString& path){
    if (!(indexList.empty())){
        QList<int> rowList = indexListToRowList(indexList);
        for (int i: rowList){
            observerList[i]->rename(path);
            ScreamerInstance->refreshObserver(path);
        }
        for (QModelIndex i: indexList)
            emit dataChanged(i, i, {Qt::DisplayRole});
    }
}

Qt::ItemFlags ObserverTable::flags(const QModelIndex& index) const{
    return (index.column() == pathColumn) ? Qt::ItemIsSelectable : Qt::NoItemFlags;
}

QVariant ObserverTable::data(const QModelIndex& index, int role) const{
    if (role == Qt::DisplayRole){
        int column = index.column();
        int row = index.row();

        if (column == pathColumn) return observerList[row]->getFilePath();
        else if (column == sizeColumn) return observerList[row]->getFileSize();
        else return QVariant();
    } else return QVariant();
}

QVariant ObserverTable::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole){
        if (Qt::Vertical == orientation) {
            return section;
        }else{
            if (section == pathColumn) {
                return "path";
            }else if (section == sizeColumn){
                return "size";
            }else return QVariant();
        }
    } else return QVariant();
}

int ObserverTable::rowCount(const QModelIndex&) const{
    return observerList.size();
}

int ObserverTable::columnCount(const QModelIndex&) const{
    return numberOfColumns;
}
