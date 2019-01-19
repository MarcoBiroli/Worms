#pragma once

#ifndef PAUSE_H
#define PAUSE_H

#include <QWidget>
#include "mainwindow.h"
#include "../GUI/music.h"
#include "../GUI/customview.h"

/*Pause class creates the pause menu. It appears/disappears when user presses ESCAPE.
  It stops game loop but does not quit it unless user presses the button QUIT
*/

class MainWindow;
class CustomView;

namespace Ui {
class Pause;
}

class Pause : public QWidget
{
    Q_OBJECT

public:
    explicit Pause(QWidget *parent = nullptr);
    ~Pause();
    MainWindow *Mainwindow;
    CustomView *view;

    //Parameters
    bool mainmenu = false;
    bool quitgame = false;



private slots:
    //Methods
    void on_mainButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::Pause *ui;
};

#endif // PAUSE_H
