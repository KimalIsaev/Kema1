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
    void refreshObserver(const int i) const;

public:
    static FileSizeScreamer* getInstance(){
        if (!instance)
            instance = new FileSizeScreamer;
        return instance;
    }
    void addFilePath(const QString&);
    void addFilePathList(const QStringList&);
    void removeFileWithFilePath(const QString&);
    int size() const;
    QString getFilePathWithIndex(const int) const;
    int getFileSizeWithIndex(const int) const;
    void refresh() const;
public slots:
    void check();

signals:
    void fileWasChanged(QString fileName, int size) const;
};

#endif // SCREAMER_H
