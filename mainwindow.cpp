#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateScreamerDisplayWidget() {
    ui->screamerListWidget->clear();
    ui->screamerListWidget->addItems(ScreamerInstance->getFilePathList());
}

void MainWindow::updateObserverDisplayWidget() {
    int i = ui->observerListWidget->currentRow();
    /*
    ui->watcherList->clear();
    for(int i=0; i<listWatcher.size(); i++)
        ui->watcherListWidget->addItem(listWatcher[i].getToStringInfo());
    ui->watcherListWidget->setCurrentRow(i);
    */
}

void MainWindow::addToScreamer() {
    QString path = ui->screamerLine->text();
    if (!(path.isEmpty())) {
        ScreamerInstance->addFilePath(path);
        QString absolutePath = ScreamerInstance->getAbsoluteFilePath(path);
        int fileSize = ScreamerInstance->getFileSizeWithPath(path);
        updateScreamerDisplayWidget();

        for(int i=0; i<observerList.size();i++)
            if(observerList[i]->getFilePath()==absolutePath)
                observerList[i]->fileIsChanged(absolutePath, fileSize);
    }
}

void MainWindow::delFromScreamer() {
    int i = ui->screamerListWidget->currentRow();
    ScreamerInstance->removeFileWithPath(i);
    updateScreamerDisplayWidget();
}

void MainWindow::addObserver(){
    QString path = ui->observerLine->text();
    if (!(path.isEmpty())) {
        QPointer<FileObserver> newObserver(new FileObserver(path));
        observerList.append(newObserver);
        QObject :: connect(ScreamerInstance, &FileSizeScreamer::fileWasChanged, newObserver.data(), &FileObserver::fileIsChanged);
        QObject :: connect(newObserver.data(), &FileObserver::printSignal, this, &MainWindow::updateObserverDisplayWidget);
        ScreamerInstance->refreshObserver(ScreamerInstance->getIndexOfFile(path));
    }
}

void MainWindow::delObserver() {
    int i=ui->observerListWidget->currentRow();
    delete observerList[i].data();
    observerList.removeAt(i);
    updateObserverDisplayWidget();
}

void MainWindow::renameObserver() {
    int i = ui->observerListWidget->currentRow();
    QString path = ui->observerLine->text();
    if (i>=0 && !path.isEmpty()){
        observerList[i]->rename(path);
        ScreamerInstance->updateIndex(ScreamerInstance->getIndexOfFile(path));
        updateWatcherListWidget();
    }
}




