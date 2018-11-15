#ifndef WORM_H
#define WORM_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRect>

class Worm
{
public:
    Worm(){

    }
    Worm(int ix, int iy, bool ifl){
        this->coor = QPair<int, int>(ix, iy);
        this->facing_left = ifl;
    }
//    void move_right(QPair<double, double> normal, QPair<double, double> gravity){
//        double mag_norm = gravity.se
//        this->facing_left = false;
//    }
//    void move_left(QPair<double, double> normal, QPair<double, double> gravity){
//        this->x -= this->speed;
//        this->facing_left = true;
//    }
private:
    int health = 100;
    int speed = 5;
    int jump = 10;
    QPair<int, int> coor = QPair<int, int>(0, 0);
    bool facing_left = true;
    QRect rect = QRect(coor.first - 5, coor.second - 5, 10, 10);
};

#endif // WORM_H
