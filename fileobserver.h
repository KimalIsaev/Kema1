#ifndef FILE_OBSERVER_H
#define FILE_OBSERVER_H


#include <QString>
#include <QObject>

class FileObserver: public QObject
{
    Q_OBJECT
protected:
    int fileSize;
    QString filePath;
public:
    FileObserver(const QString&);
    QString getFilePath() const;
    int getFileSize() const;
    void rename(const QString&);
    void sendPrintSignal();
public slots:
    void fileIsChanged(const QString&, const int);
signals:
    void printSignal(const QString&, const int);
};

#endif // FILE_OBSERVER_H
