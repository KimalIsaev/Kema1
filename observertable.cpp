#include "observertable.h"

ObserverTable::ObserverTable()
{

}

void ObserverTable::add(const QString& path){
    QPointer<FileObserver> newObserver(new FileObserver(path));
    observerList.append(newObserver);
    QObject :: connect(ScreamerInstance, &FileSizeScreamer::fileWasChanged, newObserver.data(), &FileObserver::fileIsChanged);
    ScreamerInstance->refreshObserver(path);
}

QList<int> indexListToRowList(const QModelIndexList& indexList){
    QList<int> rowList;
    std::transform  (indexList.begin(), indexList.end(), rowList.begin(),
                    [](QModelIndex index) {return index.row();});
    return rowList;
}

void ObserverTable::del(const QModelIndexList& indexList){
    if (!indexList.empty()){
        QList<int> rowList = indexListToRowList(indexList);
        std::sort(rowList.begin(), rowList.end());
        int k=0;
        for (int i: rowList){
            delete observerList[i-k].data();
            observerList.removeAt(i-k);
            k++;
        }
    }
}

void ObserverTable::rename(const QModelIndexList& indexList, const QString& path){
    if (!(indexList.empty())){
        QList<int> rowList = indexListToRowList(indexList);
        for (int i: rowList){
            observerList[i]->rename(path);
            ScreamerInstance->refreshObserver(path);
        }
    }
}

Qt::ItemFlags ObserverTable::flags(const QModelIndex& index) const{
    return (index.column() == pathColumn) ? Qt::ItemIsSelectable : Qt::NoItemFlags;
}

QVariant ObserverTable::data(const QModelIndex& index, int) const{
    int column = index.column();
    int row = index.row();
    if (column == pathColumn) return QVariant(observerList[row]->getFilePath());
    else if (column == pathColumn) return QVariant(observerList[row]->getFileSize());
    else return QVariant();
}

QVariant ObserverTable::headerData(int section, Qt::Orientation orientation, int) const{
    if (Qt::Horizontal == orientation) {
        return QVariant(section);
    }else{
        if (section == pathColumn) {
            return QVariant("path");
        }else if (section == sizeColumn){
            return QVariant("size");
        }else return QVariant();
    }
}

int ObserverTable::rowCount(const QModelIndex&) const{
    return observerList.size();
}

int ObserverTable::columnCount(const QModelIndex&) const{
    return numberOfColumns;
}
