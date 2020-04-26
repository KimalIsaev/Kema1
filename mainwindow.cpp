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
    ui->screamerListWidget->addItems(ScreamerInstance->getFileList());
}

void MainWindow::addToScreamer() {
    QString path = ui->screamerLine->text();
    if (!(path.isEmpty())) {
        ScreamerInstance->add(path);
        QString absolutePath = ScreamerInstance->getAbsoluteFilePath(path);
        updateScreamerDisplayWidget();
        ScreamerInstance->refreshObserver(path);
    }
}

void MainWindow::delFromScreamer() {
    QString path = ui->screamerListWidget->currentItem()->text();
    ScreamerInstance->remove(path);
    updateScreamerDisplayWidget();
}

void MainWindow::addObserver(){
    QString path = ui->observerLine->text();
    if (!(path.isEmpty())) {
        observerCollection.add(path);
        ScreamerInstance->refreshObserver(path);
    }
}

void MainWindow::delObserver() {
    QItemSelectionModel *select = ui->observerDisplayWidget->selectionModel();
    if (select->hasSelection())
        observerCollection.del(select->selectedRows());
}

void MainWindow::renameObserver() {
    QItemSelectionModel *select = ui->observerDisplayWidget->selectionModel();
    QString newPath = ui->observerLine->text();
    if (!(newPath.isEmpty())) {
        observerCollection.rename(select->selectedRows(), newPath);
        ScreamerInstance->refreshObserver(newPath);
    }
}




