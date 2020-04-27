#include <QApplication>
#include "filesizescreamer.h"
#include "fileobserver.h"
#include "utils.h"
#include <QPointer>
#include <iostream>
#include <QTimer>
#include <QStringList>
#include <mainwindow.h>
using namespace std;

void printObserver(const QString &filePath, const int size){
    cout << (QString("path:") + filePath + QString(" size:") + QString::number(size)).toStdString() << endl;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*
    FileSizeScreamer *screamer = FileSizeScreamer::getInstance();
    QList<QPointer<FileObserver>> observerList;//definition at utils.h

    observerList.append(QPointer<FileObserver>(new FileObserver("E:/qt/file/tum.txt")));
    observerList.append(QPointer<FileObserver>(new FileObserver("E:/qt/file/rum.txt")));
    observerList.append(QPointer<FileObserver>(new FileObserver("E:/qt/file/rum.txt")));
    for (QPointer<FileObserver> observ: observerList)
        QObject::connect(observ, &FileObserver::printSignal, printObserver);
    screamer->addFilePathList(utils::observerListToQStringList(observerList));
    utils::connectObserverList(observerList);

    screamer->check();
    utils::addOneToFile(observerList);
   // screamer->addFilePathList(utils::observerListToQStringList(observerList));
    for(int i=0; i<200000; i++){
        observerList.append(QPointer<FileObserver>(new FileObserver("E:/qt/file/tum.txt")));
        utils::connectObserverList(observerList);
        delete observerList[0].data();
        observerList.removeAt(0);
    }
    //for (QPointer<FileObserver> observ: observerList)
    //   delete observ.data();
    */
    return a.exec();
}
