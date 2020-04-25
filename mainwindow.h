#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "filesizescreamer.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FileSizeScreamer* ScreamerInstance = FileSizeScreamer::getInstance();
public slots:
    void addToScreamer();
    void delFromScreamer();
    void updateScreamerDisplayWidget();
    void addWatcher();
    void delWatcher();
    void renameWatcher();
    void updateWatcherDisplayWidget();

};

#endif // MAINWINDOW_H
