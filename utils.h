#ifndef UTILS_H
#define UTILS_H


#include <QPointer>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QObject>
#include "fileobserver.h"
#include "filesizescreamer.h"
class FileObserver;

namespace utils{
    void connectObserverList(QList<QPointer<FileObserver>>&);
    QStringList observerListToQStringList(const QList<QPointer<FileObserver>>&);
    void addOneToFile(const QString& filepath);
    void addOneToFile(const QStringList&);
    void addOneToFile(const QPointer<FileObserver>&);
    void addOneToFile(const QList<QPointer<FileObserver>>&);
}



#endif // UTILS_H
