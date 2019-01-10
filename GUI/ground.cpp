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
    this->width = width;
    this->height = height;
    srand(time(NULL));//make random 
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
    double grass_height;
    //double sea_level = 0.87*height;
    //color in black every pixel under the superposition of the two functions
    for (int i = 0; i < width; i++){
        if(0.05*width < i && i < 0.95*width){
            terrain_height = 0.53*height + 0.083*height*qCos(i/period1+phase1)+0.067*height*qCos(i/period2+phase2);
            grass_height = terrain_height + 0.03*(0.53*height + 0.083*height*qCos(100*i/period1+phase1)+0.067*height*qCos(100*i/period2+phase2));
        }
        else{
            terrain_height = height+1;
            grass_height = height + 2;// Comment this line to get ground up to the edges of the screen.
        }
        for (int j = 0; j < height ; j++){
            if (j < terrain_height){
                this->map->setPixel(i,j,qRgba(255,255,255,0)); //set the part above the ground to transparent
                this->change_pixel(i, j, Qt::white);
            }
            if (j >= terrain_height && j <= grass_height){
                this->map->setPixel(i,j,this -> green);
                this -> change_pixel(i,j, Qt::black);
            }
            if (j > grass_height && j < height){
                this -> map -> setPixel(i,j,this->brown);
                this -> change_pixel(i,j, Qt::black);
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


int Ground::WaterHeight(const int counter){
    qInfo() << "counter: " << counter;
    if (counter < 2){
        return int(0.87*height);
    }
    if (counter >= 2 && counter < 2000){
        return int(0.87*height - 100*(counter));
    }
}

void Ground::Water(const int water_height){
    for (int i = 0; i < width; i++){
        for (int j = water_height; j < height ; j++){
            this->map->setPixel(i,j,blue_sea);
        }
    }
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
        this->change_pixel(x, y, Qt::white);
        if (this->map->pixelColor(x,y) != blue_sea){
            this->map->setPixel(x, y, qRgba(255,255,255,0));
        }
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




void Ground::randomize2(){
    //final version of randomize2. It creates random points in a chosen interval and it creates a ground by interpolating these
    //points with straight lines. It is not weel suited for the game of worms but it was a good starting to make random grounds.
    
    srand(time(NULL));
    int a=500;//width of the ground i.e. b-a
    int b=4500;//a,b are multiples of 10;
    int c=500;//c must divide (b-a); this to make it easy.
    int numb_points=(b-a)/c+1;
    double terrain_height;
    double points [numb_points];
    double x[numb_points]; //x coordinates

    for (int t=0;t<=numb_points-1;t++){
        points[t]=rand()%(400) + 1300;//choose a reasonable range
    }
    for (int t=0;t<=numb_points-1;t++){
        x[t]=a+t*c;
    }
    int cn=0;
    //color in black every pixel under the superposition of the two functions
    for (int i=0;i<this->map->width();i++){

        for (int j=0;j<this->map->height();j++){
                if(a <= i && i <= b){
                terrain_height=points[cn]+(points[cn+1]-points[cn])/(x[cn+1]-x[cn])*(i-x[cn]);
                            }
            else{
                terrain_height = 2500;
            }
            if (j<terrain_height){
                this->map->setPixel(i, j, this->blue_sky);
                this->change_pixel(i, j, Qt::white);
            }
            else {
                this->map->setPixel(i, j, Qt::black);
                this->change_pixel(i, j, Qt::black);
            }
        }
        cn=((i-i%c)-a)/c;
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
            if (j >= terrain_height){
                this->map->setPixel(i, j, this -> brown);
                this->change_pixel(i, j, Qt::black);
            }

        }
    }
    item->setPixmap(QPixmap::fromImage(*this->map));

}


