#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include "mainwindow.h"
#include "../GUI/music.h"

/*Settings class allows the user to customize some of the parameters of the game*/

class MainWindow;

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    MainWindow* mainwindow;
    //different setting for worm game
    int numberOfTeams = 2;
    int wormsLife = 100;
    int wormperteam = 3;
    int healthcrates = 25;
    int timeprturn = 30;
    int amobazooka = -1;
    int amogrenade = -1;
    int amopistol = 10;
    int amoairstrike = 1;
    int amobanana = 5;
    int amomonster = 2;
    int ammoclusterbomb = 10;
    int ammoholy = 2;
    int ammodynamite = 10;
    int ammofirepunch = 5;
    int ammoarma = 1;
    int amobat = 5;


private slots:
    void on_mainmenu_clicked();
    //Methods for changing the value of scrollers and lcd number displayes
    void on_scrlnbteams_valueChanged(int value);

    void on_scrlwormhp_valueChanged(int value);

    void on_scrlwrmprteam_valueChanged(int value);

    void on_scrlhealthcrates_valueChanged(int value);

    void on_scrltimeprturn_valueChanged(int value);

    void on_scrlpistol_valueChanged(int value);

    void on_scrairstrike_valueChanged(int value);

    void on_scrlbananabomb_valueChanged(int value);

    void on_scrlmonster_valueChanged(int value);

    void on_scrclustebomb_valueChanged(int value);

    void on_scrlholy_valueChanged(int value);

    void on_scrldynamite_valueChanged(int value);

    void on_scrlfirepunch_valueChanged(int value);

    void on_scrlarma_valueChanged(int value);

    void on_scrlbat_valueChanged(int value);



private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
