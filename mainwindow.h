#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
public slots:
    void addToManager();
    void delFromManager();
    void addWatcher();
    void delWatcher();
    void renameWatcher();
    void updateWatcherDisplayWidget();
    void updateManagerDisplayWidget();
};

#endif // MAINWINDOW_H
