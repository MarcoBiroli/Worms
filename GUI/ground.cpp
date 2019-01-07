#include "ground.h"

Ground::Ground() : Collider (){ //Creates an undefined Ground
    this->map = new QImage();
    item = new QGraphicsPixmapItem();
    //this->set_map(*this->map);
}
Ground::Ground(const QImage bw_ground): Collider(){
    this -> set_map(bw_ground);
    this -> item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/ground_map_(3).png").scaled(2100,730)));
    this -> is_ground = true;
}

Ground::Ground(const int width, const int height) : Collider(){ //Creates a ground of a given size.
    
    //srand(time(NULL));//make random 
    this->map = new QImage(width, height, QImage::Format_ARGB32); //Initialize the variables.
    this->set_map(*this->map);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(*this->map));
    //create random phase and random period for two cosine functions within a range that is reasonable to obtain
    //a good mountain-like terrain
    double period1,period2;
    period1=rand()%int(0.16*width)+int(0.08*width);
    period2=rand()%int(0.08*width)+int(0.04*width);
    double phase1=rand()%int(0.2*width)+int(0.04*width);
    double phase2=rand()%int(0.2*width)+int(0.04*width);
    double terrain_height;
    double sea_level = 0.87*height;
    //color in black every pixel under the superposition of the two functions
    for (int i = 0; i < width; i++){
        if(0.05*width < i && i < 0.95*width){
            terrain_height = 0.53*height + 0.083*height*qCos(i/period1+phase1)+0.067*height*qCos(i/period2+phase2);
        }
        else{
            terrain_height = height+1;
        }
        for (int j = 0; j < height ; j++){
            if (j < terrain_height){
                this->map->setPixel(i,j,qRgba(255,255,255,0)); //set the part above the ground to transparent
                this->change_pixel(i, j, Qt::white);
            }
            if (j >= terrain_height && j < sea_level){
                this->map->setPixel(i, j, this -> brown);  //ground in brown
                this->change_pixel(i, j, Qt::black);
            }
            if (j >= sea_level) {
                this -> map -> setPixel(i,j,this -> blue_sea);
            }
            if (j > height-10){
                this -> change_pixel(i,j, Qt::blue); //temporary solution to avoid the objects (worms, weapons) to fall for ever
            }  //blue pixels are rigid body but can't be delete
            if (i < 10){
                this -> change_pixel(i,j,Qt::blue);
            }
            if (i > width-10){
                this -> change_pixel(i,j,Qt::blue);
            }
        }
    }
    /*QPainter painter(this->map);
    painter.drawImage(0,-1500,img2);    //Fill all by blue meaning there is no ground.
    for(int i = 0; i < width; i++){     //By default makes all the pixels that are under (y = 500) ground.
        for(int j = 0; j < height; j++){
            this->map->setPixel(i, j, Qt::white);
            this->change_pixel(i,j, Qt::black);
            }
        }*/
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
    //for (int i = x - radius;)
    for(int i = int (x-radius); i < int (x + radius); ++i){
        for(int j = int (y - radius); j < int (y + radius); ++j){
            distance = double(i - x)*double(i - x) + double(j - y)*double(j - y);
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




