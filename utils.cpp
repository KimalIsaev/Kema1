#include "utils.h"
using namespace utils;
using namespace std;


void utils::connectObserverList(QList<QPointer<FileObserver>>& observerPointerList){
    for(QPointer<FileObserver> observerPointer: observerPointerList)
        QObject::connect(FileSizeScreamer::getInstance(), &FileSizeScreamer::fileWasChanged, observerPointer, &FileObserver::fileIsChanged);
    FileSizeScreamer::getInstance()->refresh();
}


QStringList utils::observerListToQStringList(const QList<QPointer<FileObserver>>& observerPointerList){
    QStringList result;
    for(QPointer<FileObserver> observerPointer: observerPointerList)
       result.append(observerPointer->getFilePath());
    return result;
}


void utils::addOneToFile(const QString& filePath){
    QFile file(filePath);
    file.open(QIODevice::Append);
    file.write("1");
}


void utils::addOneToFile(const QStringList& filePathList){
    for (QString filePath: filePathList)
        addOneToFile(filePath);
}


void utils::addOneToFile(const QPointer<FileObserver>& observerPointer){
    addOneToFile(observerPointer->getFilePath());
}


void utils::addOneToFile(const QList<QPointer<FileObserver>>& observerList){
    for(QPointer<FileObserver> observerPointer: observerList)
        addOneToFile(observerPointer);
}


