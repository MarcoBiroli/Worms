#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include "settings.h"
#include "help.h"

/*The MainWindow class is the MAIN MENU of the game. Here the user can choose its level, settings, quit, get help.*/

class Settings;
class Help;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //Parameters for level initialization
    bool start_easy = false;
    bool start_medium = false;
    bool start_hard = false;
    bool quit_button = false;
    bool through_esc = false;

    Settings * settingmenu;
    Help *helpmenu;

public slots:
    void add_percent(); //CHANGE---> LOADING BUTTON

private slots:
    //Method to change the parameters
    void on_Easy_clicked();

    void on_Medium_clicked();

    void on_Hard_clicked();

    void on_Help_clicked();

    void on_Settings_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
