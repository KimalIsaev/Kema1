#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScreamerDisplayWidget()
{
    ui->screamerList->clear();
    ui->screamerList->addItems(ScreamerInstance->getFilePathList());
}

void MainWindow::updateWatcherDisplayWidget()
{
    int i = ui->watcherList->currentRow();
    /*
    ui->watcherList->clear();
    for(int i=0; i<listWatcher.size(); i++)
        ui->watcherListWidget->addItem(listWatcher[i].getToStringInfo());
    ui->watcherListWidget->setCurrentRow(i);
    */
}

void MainWindow::addToScreamer()
{
    QString path = ui->screamerLine->text();
    if (!(path.isEmpty()))
    {
        ScreamerInstance->addFilePath(path);
        int indexOfFileInScreamer = ScreamerInstance->getIndexOfFile(path);
        QString absolutePath = ScreamerInstance->getFilePathWithIndex(indexOfFileInScreamer);
        int fileSize = ScreamerInstance->getFileSizeWithIndex(indexOfFileInScreamer);
        updateScreamerDisplayWidget();

        for(int i=0; i<listWatcher.size();i++)
            if(listWatcher[i].getNameFile()==absolutePath)
                listWatcher[i].changedState(absolutePath, fileSize);
    }
}

void MainWindow::delFromScreamer()
{
    int i=ui->screamerList->currentRow();
    ScreamerInstance->removeFileWithIndex(i);
    updateScreamerDisplayWidget();
}

void MainWindow::addFileToListWatcher()
{
    if (!((ui->watcherLineEdit->text()).isEmpty()))
    {
        listWatcher.append(FWatcher(ui->watcherLineEdit->text()));
        QObject :: connect(FManager::getInstance(), &FManager::alterWatcher, &(listWatcher.last()), &FWatcher::changedState);
        FManager::getInstance()->updateIndex(FManager::getInstance()->findFile(ui->watcherLineEdit->text()));
        //FManager::getInstance()->updateAll();
        updateWatcherListWidget();
        QObject :: connect(&(listWatcher.last()), &FWatcher::signalUpdateWiget, this, &MainWindow::updateWatcherListWidget);
    }
}

void MainWindow::delFileFromListWatcher()
{
    int i=ui->watcherListWidget->currentRow();
    listWatcher.removeAt(i);
    updateWatcherListWidget();
}

void MainWindow::renameWatcher()
{
    int i=ui->watcherListWidget->currentRow();
    if (i>=0 && !(ui->watcherLineEdit->text()).isEmpty())
    listWatcher[i].renameFile(ui->watcherLineEdit->text());
    FManager::getInstance()->updateIndex(FManager::getInstance()->findFile(ui->watcherLineEdit->text()));
    updateWatcherListWidget();
}




