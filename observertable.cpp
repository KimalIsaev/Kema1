#include "observertable.h"

ObserverTable::ObserverTable()
{

}
/*
add{
    QPointer<FileObserver> newObserver(new FileObserver(path));
    observerList.append(newObserver);
    QObject :: connect(ScreamerInstance, &FileSizeScreamer::fileWasChanged, newObserver.data(), &FileObserver::fileIsChanged);
    QObject :: connect(newObserver.data(), &FileObserver::printSignal, this, &MainWindow::updateObserverDisplayWidget);
}

del{
    delete observerList[i].data();
    observerList.removeAt(i);
}

*/
Qt::ItemFlags ObserverTable::flags(const QModelIndex& index) const{
    return (index.column() == pathColumn) ? Qt::ItemIsSelectable : Qt::NoItemFlags;
}
