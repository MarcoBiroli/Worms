#include "ground.h"

Ground::Ground(const QImage background): Collider(){
    this -> map = new QImage(background);
    this -> set_map(*this->map);
    this -> is_ground = true;
}

Ground::Ground(const int width, const int height) : Collider(){ //Creates a ground of a given size.
    QString path = ("://Images/game_background.jpg");
    QImage img(path);
    QImage img2 = img.scaled(9000,7000, Qt::KeepAspectRatio);
    this->map = new QImage(width, height, QImage::Format_RGB32); //Initialize the variables.
    this->map->fill(Qt::white);
    this->set_map(*this->map);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(*this->map));
    QPainter painter(this->map);
    painter.drawImage(0,-1500,img2);    //Fill all by blue meaning there is no ground.
    for(int i = 0; i < width; i++){     //By default makes all the pixels that are under (y = 500) ground.
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
    //QImage color_ground("://Images/ground_map.png");
    //item -> setPixmap(QPixmap::fromImage(color_ground));
    return item;
}
QImage* Ground::getMap() const{ //This returns the ground itself.
    return this->map;
}
void Ground::delete_ground(int x, int y){ //This deletes the ground at one point of coordinate (x,y).
    if(this->get_map().pixelColor(x,y) == Qt::black){
        this->map->setPixel(x, y, this->blue_sky);
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

void Ground::randomize(){
    //this->set_map(QImage map);
    //this->change_pixel(int i, int j, Qt::black or Qt::white);
    //QImage new_image = QImage(int width, int height, QImage::Format_RGB32)
    //new_image.fill(Qt::white);
    //new_image.setPixel(int i, int j, Qt::white or Qt::black)

    qDebug() << "hey";
    double period1,period2;
    period1=rand()%1000+400;
    period2=rand()%100+20;
    double phase1=rand()%1000+200;
    double phase2=rand()%1000+200;

    for (int i=0;i<this->map->width();i++){
        for (int j=0;j<this->map->height();j++){
            // I can put any function here...
            //double terrain_height=2000 + 200*qCos(i/period1+phase1)+50*qCos(i/period2+phase2)+200*qCos(i/((period1+period2)/2));
            double terrain_height=2000 + 200*qCos(i/period1+phase1);
            if (j<terrain_height){
                this->map->setPixel(i, j, this->blue_sky);
                this->change_pixel(i, j, Qt::white);
            }
            else {
                this->map->setPixel(i, j, Qt::black);
                this->change_pixel(i, j, Qt::black);
            }
        }
    }
}
