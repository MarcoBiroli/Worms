#ifndef GROUND_H
#define GROUND_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QCursor>
#include <QGraphicsPixmapItem>

class Ground
{
private:
    QImage* map; //This is the image in which we store the information about the ground
    QRgb white = qRgb(255, 255, 255);   //I define colors here so later in the code i can just us "black" or "white"
    QRgb black = qRgb(0, 0, 0);         //insted of having to write the full rgb code each time.
    QGraphicsPixmapItem *item; //This is a QGraphicsItem, its an item that can be given to the screen to display.

public:
    Ground(){ //Creates an undefined Ground
        this->map = new QImage();
        item = new QGraphicsPixmapItem();
    }
    Ground(const int width, const int height){ //Creates a ground of a given size.
        this->map = new QImage(width, height, QImage::Format_RGB32); //Initialize the variables.
        item = new QGraphicsPixmapItem(QPixmap::fromImage(*this->map));
        this->map->fill(white); //Fill all by white meaning there is no ground.
        for(int i = 0; i < width; i++){ //By default makes all the pixels that are under (y = 250) ground.
            for(int j = 0; j < height; j++){
                if(j > 250){
                    this->map->setPixel(i, j, black);
                }
            }
        }
    }
    QGraphicsPixmapItem* getPixmap() const{ //This returns the Displayable Version of the Ground.
        item->setPixmap(QPixmap::fromImage(*this->map));
        return item;
    }
    QImage* getMap() const{ //This returns the ground itself.
        return this->map;
    }
    void delete_ground(int x, int y){ //This deletes the ground at one point of coordinate (x,y).
        this->map->setPixel(x, y, this->white);
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
