#ifndef GROUND_H
#define GROUND_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QCursor>
#include <QGraphicsView>
#include "Collider.h"

class Ground: public Collider
{
public:
    Ground() : Collider(){ //Creates an undefined Ground
    }
    Ground(const int width, const int height): Collider(){ //Creates a ground of a given size.
        QImage default_ground = QImage(width, height, QImage::Format_RGB32); //Initialize the variables.
        default_ground.fill(Qt::white); //Fill all by white meaning there is no ground.
        this->set_map(default_ground);
        for(int i = 0; i < width; i++){ //By default makes all the pixels that are under (y = 250) ground.
            for(int j = 0; j < height; j++){
                if(j > 250){
                    this->change_pixel(i, j, Qt::black);
                }
            }
        }
    }


    void delete_ground(int x, int y){ //This deletes the ground at one point of coordinate (x,y).
        this->change_pixel(x, y, Qt::white);
    }
    void circ_delete(int x, int y, double radius){ //This deletes all points in a circle of center (x,y) and radius "radius".
        double distance;
        for(int i = (int)(x-radius); i < (int)(x + radius); ++i){
            for(int j = (int)(y - radius); j < (int)(y + radius); ++j){
                distance = (double)(i - x)*(double)(i - x) + (double)(j - y)*(double)(j - y);
                if(distance <= radius*radius){
                    this->delete_ground(i, j);
                }
            }
        }
    }
};

#endif // GROUND_H
