#pragma once
#define CUSTOMVIEW
#ifdef CUSTOMVIEW

#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <QObject>
#include <iostream>

#include "../Core/Game.h"

/*This class inherits QGraphicsView. It is responsible for all user interactions and display*/
class Game;

class CustomView : public QGraphicsView
{
public:
    //Constructor /Destructor
    CustomView(QGraphicsScene *parent);
    ~CustomView();

    //Parameters
    Game* game;
    bool has_quitted = false;
    double currentScale = 1.0;  // stores the current scale value.
    const double scaleMin = 0.5; // defines the min scale limit. if you want limit to increase, - scaleMin,
    const double scaleMax = 3; //defines the max scale limit. if you want limit to increase, + scaleMin,
    double prev_mouse_x = -1;
    double prev_mouse_y = -1;
    bool is_paused = false;

    //Methods
    void setup_menu();

protected:
    //User Methods
     void wheelEvent(QWheelEvent *event);
     void keyPressEvent(QKeyEvent *k);
     void mouseMoveEvent(QMouseEvent *event);
     void keyReleaseEvent(QKeyEvent *k);
     void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif //CUSTOMVIEW_H
