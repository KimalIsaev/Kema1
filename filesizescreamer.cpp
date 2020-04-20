#include "filesizescreamer.h"


FileSizeScreamer *FileSizeScreamer::instance = NULL;


FileSizeScreamer::FileSizeScreamer(){
    connect(&checkClock, SIGNAL(timeout()), this, SLOT(check()));
    checkClock.start(1000);
}


void FileSizeScreamer::addFilePath(const QString& additionalFilePath){
    fileInfoList.append(QFileInfo(additionalFilePath));
    fileSizeList.append(INT_MIN);
    checkFileWithIndex(fileInfoList.size()-1);
}


void FileSizeScreamer::addFilePathList(const QStringList& additionalFilePathList){
    for (QString p: additionalFilePathList)
        addFilePath(p);
}


void FileSizeScreamer::removeFileWithFilePath(const QString& filePath){
    int delIndex = fileInfoList.indexOf(QFileInfo(filePath));
    if (delIndex != -1)
        removeFileWithIndex(delIndex);
}

void FileSizeScreamer::removeFileWithIndex(const int i){
    fileInfoList.removeAt(i);
    fileSizeList.removeAt(i);
}


void FileSizeScreamer::checkFileWithIndex(const int i){
    fileInfoList[i].refresh();
    const QFileInfo* f = &(fileInfoList[i]);
    int currentFileSize;
    if (f->exists()){
        currentFileSize = f->size();
    }else{
        currentFileSize = -1;
    }
    if (fileSizeList[i] != currentFileSize){
        fileSizeList[i] = currentFileSize;
        emit fileWasChanged(f->absoluteFilePath(), currentFileSize);
    }
}

void FileSizeScreamer::refreshObserver(const int i) const{
    emit fileWasChanged(fileInfoList[i].absoluteFilePath(), fileSizeList[i]);
}

void FileSizeScreamer::refresh() const{
    for(int i=0; i<this->size(); i++)
        refreshObserver(i);
}

void FileSizeScreamer::check()
{
    for(int i=0; i<this->size(); i++)
        checkFileWithIndex(i);
}


QString FileSizeScreamer::getFilePathWithIndex(const int i) const{
    return fileInfoList[i].absoluteFilePath();
}


int FileSizeScreamer::getFileSizeWithIndex(const int i) const{
    return fileSizeList[i];
}


int FileSizeScreamer::size() const{
    return fileInfoList.size();
}
