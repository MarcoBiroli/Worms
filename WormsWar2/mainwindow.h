#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "help_menu.h"
#include <QObject>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool start_game = false;
    help_menu *helpmenu;


private slots:
    void on_pushButton_clicked();
    void on_Help_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
