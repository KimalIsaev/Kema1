#include "fileobserver.h"
FileObserver::FileObserver(const QString& givenFilePath){
    filePath = givenFilePath;
    fileSize = INT_MIN;
}


void FileObserver::fileIsChanged(const QString& givenFilePath, const int size){
    if (filePath == givenFilePath){
        fileSize = size;
        sendPrintSignal();
    }
}

QString FileObserver::getFilePath() const{
    return filePath;
}

int FileObserver::getFileSize() const{
    return fileSize;
}

void FileObserver::rename(const QString& givenFilePath){
    filePath = givenFilePath;
    fileSize = INT_MIN;
}

void FileObserver::sendPrintSignal(){
    emit printSignal(filePath, fileSize);
}
