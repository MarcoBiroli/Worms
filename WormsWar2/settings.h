#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H


#include <QMainWindow>
#include "mainwindow.h"
#include "../GUI/music.h"

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
    int numberOfTeams = 2;
    int wormsLife = 100;
    int wormperteam = 3;
    int healthcrates = 25;
    int timeprturn = 30;
    int amobazooka = -1;
    int amogrenade = -1;
    int amopistol = 10;
    int amolandmine = 3;
    int amoairstrike = 1;
    int amobanana = 5;
    int amomonster = 2;
    int ammoclusterbomb = 10;
    int ammoholy = 2;
    int ammodynamite = 10;
    int ammofirepunch = 5;
    int ammoarma = 1;


private slots:
    void on_mainmenu_clicked();
    void on_scrlnbteams_valueChanged(int value);
    void on_scrlwormhp_valueChanged(int value);

    void on_scrlwrmprteam_valueChanged(int value);

    void on_scrlhealthcrates_valueChanged(int value);

    void on_scrltimeprturn_valueChanged(int value);

    void on_scrlbazooka_valueChanged(int value);

    void on_scrlgrenade_valueChanged(int value);

    void on_scrlpistol_valueChanged(int value);

    void on_scrllandmine_valueChanged(int value);

    void on_scrairstrike_valueChanged(int value);

    void on_scrlbananabomb_valueChanged(int value);

    void on_scrlmonster_valueChanged(int value);

    void on_scrclustebomb_valueChanged(int value);

    void on_scrlholy_valueChanged(int value);

    void on_scrldynamite_valueChanged(int value);

    void on_scrlfire_valueChanged(int value);

    void on_scrlarma_valueChanged(int value);

    void on_infinitebazooka_stateChanged(int arg1);

    void on_infinitegrenade_stateChanged(int arg1);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
