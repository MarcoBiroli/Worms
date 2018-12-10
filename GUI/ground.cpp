#include "ground.h"



Ground::Ground(const int width, const int height) : Collider(){ //Creates a ground of a given size.
    QString path = ("game_background.jpg");
    QImage img(path);
    QImage img2 = img.scaled(10000,5000, Qt::KeepAspectRatio);
    this->map = new QImage(width, height, QImage::Format_RGB32); //Initialize the variables.
    this->map->fill(Qt::white);
    this->set_map(*this->map);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(*this->map));
    QPainter painter(this->map);
    painter.drawImage(0,-1500,img2);//Fill all by blue meaning there is no ground.
    for(int i = 0; i < width; i++){ //By default makes all the pixels that are under (y = 500) ground.
        for(int j = 0; j < height; j++){
            if(j > 500){
                this->map->setPixel(i, j, Qt::red);
                this->change_pixel(i,j, Qt::black);
            }
            if(j > 2000){
                this->map->setPixel(i,j,blue_sea);
                this->change_pixel(i,j, Qt::white);
            }
        }
    }
    this->is_ground = true;
}

QGraphicsPixmapItem* Ground::getPixmap() const{ //This returns the Displayable Version of the Ground.
    item->setPixmap(QPixmap::fromImage(*this->map));
    return item;
}
QImage* Ground::getMap() const{ //This returns the ground itself.
    return this->map;
}
void Ground::delete_ground(int x, int y){ //This deletes the ground at one point of coordinate (x,y).
    this->map->setPixel(x, y, this->blue_sky);
    this->change_pixel(x, y, Qt::white);
}
void Ground::circ_delete(int x, int y, double radius){ //This deletes all points in a circle of center (x,y) and radius "radius".
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
