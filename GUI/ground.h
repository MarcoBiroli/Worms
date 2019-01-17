#ifndef GROUND_H
#define GROUND_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QCursor>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <qmath.h>
#include "QDebug"
#include <QtGui>
#include "QApplication"

#include "../Physics/Collider.h"
#include <perlinnoise.h>
#include "water.h"

/*The ground class inherits from collider. It is not a rigidbody as it is not subject to physics.
It generates ground*/

class Ground : public Collider
{
    Q_OBJECT
private:
    //Map storing
    QImage* map; // colors colliding_map //This is the image in which we store the information about the ground
    QGraphicsPixmapItem *item; //This is a QGraphicsItem, its an item that can be given to the screen to display.

    //Parameters
    QApplication* a = NULL;
    int height;
    int width;
    QColor terraincolor; //color of the ground
    QColor grasscolor; // color of the grass

    //Neccessary methods for randomize2()
    QVector<QPair<int, int> > getNeighbors(QPair<int, int> source);
    void dilate(QImage kernel);
    void dilate2(QColor color);
    void dilate3(QColor color, int depth);
    int **manhattan();
    void dilate4(QColor color, int depth);


public:
    //Constructors
    Ground();
    Ground(QApplication* a, const int width, const int height, QColor terraincolor, QColor grasscolor);

    //Randomize methods
    void randomize2();
    void randomize3();

    //Water methods
    int WaterHeight(const int counter);
    void Water(const int water_height);
    void fillup(int i, int j, QImage& perlin);

    //Get Methods
    QGraphicsPixmapItem* getPixmap() const; //This returns the Displayable Version of the Ground.
    QImage* getMap() const; //This returns the ground itself.

    //Delete Methods
    void delete_ground(int x, int y); //This deletes the ground at one point of coordinate (x,y).
    //Virtual Methods
    virtual void circ_delete(int x, int y, double radius); //This deletes all points in a circle of center (x,y) and radius "radius".

signals:
    void new_percent();//<- TO BE DELETED?? THIS WAS A TRY FOR THE LOADING BUTTON DIDNT WORK

};
#endif // GROUND_H
