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

void MainWindow::updateManagerDisplayWidget()
{
    ui->managerListWidget->clear();
    ui->managerListWidget->addItems(FManager::getInstance()->getNameList());
}

void MainWindow::updateWatcherListWidget()
{
    int i = ui->watcherListWidget->currentRow();
    ui->watcherListWidget->clear();
    for(int i=0; i<listWatcher.size(); i++)
        ui->watcherListWidget->addItem(listWatcher[i].getToStringInfo());
    ui->watcherListWidget->setCurrentRow(i);
}

void MainWindow::addFileToManager()
{
    if (!((ui->managerLineEdit->text()).isEmpty()))
    {
        QFileInfo file(ui->managerLineEdit->text());
        FManager::getInstance()->addFile(ui->managerLineEdit->text());
        updateManagerListWidget();
        for(int i=0; i<listWatcher.size();i++)
        {
            if(listWatcher[i].getNameFile()==file.absoluteFilePath())
                listWatcher[i].changedState(file.absoluteFilePath(), file.size(),file.exists());
        }
    }
}

void MainWindow::delFileFromManager()
{
    int i=ui->managerListWidget->currentRow();
    FManager::getInstance()->delFile(i);
    updateManagerListWidget();
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




