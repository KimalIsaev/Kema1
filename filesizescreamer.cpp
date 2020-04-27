#include "filesizescreamer.h"


FileSizeScreamer *FileSizeScreamer::instance = NULL;


FileSizeScreamer::FileSizeScreamer(){
    connect(&checkClock, SIGNAL(timeout()), this, SLOT(check()));
    checkClock.start(1000);
}


void FileSizeScreamer::add(const QString& additionalFilePath){
    if (getIndexOfFile(additionalFilePath) < 0){
        fileInfoList.append(QFileInfo(additionalFilePath));
        fileSizeList.append(INT_MIN);
        checkFileWithIndex(fileInfoList.size()-1);
    }
}


void FileSizeScreamer::addList(const QStringList& additionalFilePathList){
    for (QString p: additionalFilePathList)
        add(p);
}


void FileSizeScreamer::remove(const QString& filePath){
    int delIndex = getIndexOfFile(filePath);
    if (delIndex >= 0)
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

void FileSizeScreamer::refreshObserverWithIndex(const int i) const{
    if (i>=0)
        emit fileWasChanged(fileInfoList[i].absoluteFilePath(), fileSizeList[i]);
}

void FileSizeScreamer::refreshObserver(const QString& path) const{
    refreshObserverWithIndex(getIndexOfFile(path));
}

void FileSizeScreamer::refresh() const{
    for(int i=0; i<this->size(); i++)
        refreshObserverWithIndex(i);
}

void FileSizeScreamer::check()
{
    for(int i=0; i<this->size(); i++)
        checkFileWithIndex(i);
}


QString FileSizeScreamer::getFilePathWithIndex(const int i) const{
    return fileInfoList[i].absoluteFilePath();
}

QStringList FileSizeScreamer::getFileList() const{
    QStringList r;
    for (QFileInfo f: fileInfoList)
        r.append(f.absoluteFilePath());
    return r;
}

QString FileSizeScreamer::getAbsoluteFilePath(const QString& path) const{
    return QFileInfo(path).absoluteFilePath();
}

int FileSizeScreamer::getIndexOfFile(const QString& path) const{
    return getFileList().indexOf(getAbsoluteFilePath(path));
}

int FileSizeScreamer::getFileSizeWithIndex(const int i) const{
    return fileSizeList[i];
}


int FileSizeScreamer::size() const{
    return fileInfoList.size();
}
