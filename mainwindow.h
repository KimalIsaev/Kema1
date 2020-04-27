#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "filesizescreamer.h"
#include <QMainWindow>
#include "observertable.h"
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
    ObserverTable observerCollection;
public slots:
    void addToScreamer();
    void delFromScreamer();
    void updateScreamerDisplayWidget();
    void addObserver();
    void delObserver();
    void renameObserver();
    void pushStandartValue();
};

#endif // MAINWINDOW_H
