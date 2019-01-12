#pragma once

#ifndef PAUSE_H
#define PAUSE_H

#include <QWidget>
#include "mainwindow.h"
#include "../GUI/music.h"
#include "../GUI/customview.h"

class MainWindow;

namespace Ui {
class Pause;
}

class Pause : public QWidget
{
    Q_OBJECT

public:
    explicit Pause(QWidget *parent = nullptr);
    ~Pause();
    MainWindow *MainWindow;
    bool mainmenu = false;
    bool quitgame = false;
    CustomView *view;


private slots:

    void on_mainButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::Pause *ui;
};

#endif // PAUSE_H
