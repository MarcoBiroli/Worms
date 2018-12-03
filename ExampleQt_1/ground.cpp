#include "ground.h"


Ground::Ground(){ //Creates an undefined Ground
    this->map = new QImage();
    item = new QGraphicsPixmapItem();
}
Ground::Ground(const int width, const int height){ //Creates a ground of a given size.
    this->map = new QImage(width, height, QImage::Format_RGB32); //Initialize the variables.
    item = new QGraphicsPixmapItem(QPixmap::fromImage(*this->map));
    this->map->fill(blue); //Fill all by white meaning there is no ground.
    for(int i = 0; i < width; i++){ //By default makes all the pixels that are under (y = 250) ground.
        for(int j = 0; j < height; j++){
            if(j > 250){
                this->map->setPixel(i, j, green);
            }
        }
    }
}
QGraphicsPixmapItem* Ground::getPixmap() const{ //This returns the Displayable Version of the Ground.
    item->setPixmap(QPixmap::fromImage(*this->map));
    return item;
}
QImage* Ground::getMap() const{ //This returns the ground itself.
    return this->map;
}
void Ground::delete_ground(int x, int y){ //This deletes the ground at one point of coordinate (x,y).
    this->map->setPixel(x, y, this->brown);
}
void Ground::circ_delete(int x, int y, double radius){ //This deletes all points in a circle of center (x,y) and radius "radius".
    double distance;
    for(int i = (int)(x-radius); i < (int)(x + radius); ++i){
        for(int j = (int)(y - radius); j < (int)(y + radius); ++j){
            distance = (double)(i - x)*(double)(i - x) + (double)(j - y)*(double)(j - y);
            if(distance <= radius*radius && j > 250){
                this->delete_ground(i, j);
            }
        }
    }
}
