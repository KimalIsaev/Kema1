#ifndef SCREAMER_H
#define SCREAMER_H


#include <QList>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QFileInfo>
#include "utils.h"


class FileSizeScreamer:public QObject
{
    Q_OBJECT
    static FileSizeScreamer *instance;
    QList<int> fileSizeList;
    QTimer checkClock;
    QList<QFileInfo> fileInfoList;
    FileSizeScreamer();
    void checkFileWithIndex(int);
    ~FileSizeScreamer(){delete instance;};
    void removeFileWithIndex(const int i);
    QString getFilePathWithIndex(const int) const;
    int getIndexOfFile(const QString&) const;
    int getFileSizeWithIndex(const int) const;
    void refreshObserverWithIndex(const int i) const;
public:
    static FileSizeScreamer* getInstance(){
        if (!instance)
            instance = new FileSizeScreamer;
        return instance;
    }
    void refreshObserver(const QString&) const;
    void add(const QString&);
    void addList(const QStringList&);
    void remove(const QString&);
    int size() const;
    int getFileSize(const QString&) const;
    void refresh() const;
    QStringList getFileList() const;
    QString getAbsoluteFilePath(const QString&) const;
public slots:
    void check();

signals:
    void fileWasChanged(QString fileName, int size) const;
};

#endif // SCREAMER_H
