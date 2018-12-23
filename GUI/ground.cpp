#include "ground.h"


Ground::Ground(const QImage bw_ground): Collider(){
    //this -> set_map(bw_ground);
    //this -> item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/ground_map_(3).png").scaled(2100,730)));
    //this -> is_ground = true;
}

Ground::Ground(const int width, const int height) : Collider(){ //Creates a ground of a given size.
    QString path = ("://Images/game_background.jpg");
    QImage img(path);
    QImage img2 = img.scaled(width,height, Qt::KeepAspectRatio);

    //this->map = new QImage(width, height, QImage::Format_ARGB32); //Initialize the variables.
    //this->map->fill(Qt::white);
    this->map = new QImage("://Images/game_background.jpg");
    *this->map = this->map->scaled(width, height);

    QImage collider = QImage("://Images/bw_ground.jpg");
    collider = collider.scaled(width, height);
    this->set_map(collider);

    for(int i = 0; i <width; i++){
        for(int j = 0; j < height; j++){
            if(this->get_map().pixelColor(i,j) == Qt::white){
                this->map->setPixel(i, j, qRgba(255,255,255,0));
            }
        }
    }

    item = new QGraphicsPixmapItem(QPixmap::fromImage(*this->map));

    /*
    //QPainter painter(this->map);
    //painter.drawImage(0, -1500,img2);    //Fill all by blue meaning there is no ground.
    for(int i = 0; i < width; i++){     //By default makes all the pixels that are under (y = 500) ground.
        for(int j = 0; j < height; j++){
            if(j > 500){
                this->map->setPixel(i, j, qRgba(125, 65, 6, 255));
                this->change_pixel(i,j, Qt::black);
            }
            /*
            if(j > 2000){
                this->map->setPixel(i,j,blue_sea);
                this->change_pixel(i,j, Qt::white);
            }
        }
    }
    */

    this->is_ground = true;
}

QGraphicsPixmapItem* Ground::getPixmap() const{ //This returns the Displayable Version of the Ground.
    item->setPixmap(QPixmap::fromImage(*this->map));
    //QImage color_ground("://Images/ground_map.png");
    //item -> setPixmap(QPixmap::fromImage(color_ground));
    return item;
}
QImage* Ground::getMap() const{ //This returns the ground itself.
    return this->map;
}
void Ground::delete_ground(int x, int y){ //This deletes the ground at one point of coordinate (x,y).
    if(this->get_map().pixelColor(x,y) == Qt::black){
        this->map->setPixel(x, y, qRgba(255,255,255,0));
        this->change_pixel(x, y, Qt::white);
    }
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
    item->setPixmap(QPixmap::fromImage(*this->map));
}




//WORK IN PROGRESS
void Ground::randomize(){
    //this first function creates a random terrain made of a superpositon of cosine

    //QImage display_image = QImage(5000,3000,QImage::Format_ARGB32);
    //display_image.fill(QColor(Qt::white).rgb());
    //create random phase and random period for two cosine functions within a range that is reasonable to obtain
    //a good mountain-like terrain
    double period1,period2;
    period1=rand()%800+400;
    period2=rand()%400+200;
    double phase1=rand()%1000+200;
    double phase2=rand()%1000+200;
    double terrain_height;
    //color in black every pixel under the superposition of the two functions
    for (int i=0;i<this->map->width();i++){
        for (int j=0;j<this->map->height();j++){
            if(0 < i && i < 8400){
                terrain_height=1600 + 250*qCos(i/period1+phase1)+200*qCos(i/period2+phase2);
            }
            else{
                terrain_height = 2500;
            }
            if (j<terrain_height){
                this->map->setPixel(i,j,qRgba(255,255,255,0));
                this->change_pixel(i, j, Qt::white);
            }
            if (j >= terrain_height && j < 2600){
                this->map->setPixel(i, j, this -> brown);
                this->change_pixel(i, j, Qt::black);
            }
            if (j >= 2600) {
                this -> map -> setPixel(i,j,this -> blue_sea);
            }
        }
    }
    item->setPixmap(QPixmap::fromImage(*this->map));
}




