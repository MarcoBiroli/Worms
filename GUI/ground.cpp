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
                this->map->setPixelColor(i, j, this -> brown);  //ground in brown
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
    this->randomize2();
}

QGraphicsPixmapItem* Ground::getPixmap() const{ //This returns the Displayable Version of the Ground.
    item->setPixmap(QPixmap::fromImage(*this->map));
    //QImage color_ground("://Images/ground_map.png");
    //item -> setPixmap(QPixmap::fromImage(color_ground));
    return item;
}

QVector<QPair<int, int>> Ground::getNeighbors(QPair<int, int> source){
    QVector<QPair<int, int>> neighbours;
    QVector<QPair<int, int>> L({QPair<int, int>(0,1), QPair<int, int>(1, 1), QPair<int, int>(1, 0), QPair<int, int>(1, -1), QPair<int, int>(0, -1),
                               QPair<int, int>(-1, -1), QPair<int, int>(-1,0), QPair<int, int>(-1, 1)});
    for(int k = 0; k < 8; k++){
        if(L[k].first + source.first < this->map->width() && L[k].first + source.first >= 0 &&
                L[k].second + source.second < this->map->height() && L[k].second + source.second >= 0){
            neighbours.append(QPair<int, int>(L[k].first + source.first, L[k].second + source.second));
        }
    }
    return neighbours;
}

void Ground::fillup(int i, int j, QImage& perlin)
{
    QVector<QPair<int, int>> stack;
    stack.append(QPair<int, int>(i,j));
    while(stack.length() != 0){
        QPair<int, int> cur = stack.takeLast();
        this->change_pixel(cur.first, cur.second, Qt::black);
        this->map->setPixelColor(cur.first, cur.second, this->brown);
        if(perlin.pixelColor(cur.first, cur.second) != QColor(0, 0, 0, 255)){
            perlin.setPixelColor(cur.first, cur.second, QColor(0, 0, 0, 255));
            stack.append(getNeighbors(cur));
        }
    }
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
                this->map->setPixelColor(i, j, this -> brown);
                this->change_pixel(i, j, Qt::black);
            }
            if (j >= 2600) {
                this -> map -> setPixel(i,j,this -> blue_sea);
            }
        }
    }
    item->setPixmap(QPixmap::fromImage(*this->map));
}

void Ground::dilate2() {
    // Best dilate by one solution
    for (int i=0; i<this->map->width(); i++){
        for (int j=0; j < this->map->height(); j++){
            if (this->map->pixelColor(i, j) == this->brown){
                if (i>0 && this->map->pixelColor(i-1, j) != this->brown) this->map->setPixelColor(i-1, j, QColor(0,0,0,255));
                if (j>0 && this->map->pixelColor(i, j-1) != this->brown) this->map->setPixelColor(i, j-1, QColor(0, 0, 0, 255));
                if (i+1< this->map->width() && this->map->pixelColor(i+1, j) != this->brown) this->map->setPixelColor(i+1, j, QColor(0, 0, 0, 255));
                if (j+1< this->map->height() && this->map->pixelColor(i, j+1) != this->brown) this->map->setPixelColor(i, j+1, QColor(0, 0, 0, 255));
            }
        }
    }
    for (int i=0; i<this->map->width(); i++){
        for (int j=0; j < this->map->height(); j++){
            if (this->map->pixelColor(i, j) == QColor(0, 0, 0, 255)){
                this->map->setPixelColor(i, j, this->brown);
                this->change_pixel(i, j, Qt::black);
            }
        }
    }
}


// grayscale image, binary mask
void Ground::dilate(QImage kernel) {
 // half size of the kernel, kernel size is n*n (easier if n is odd)
     int sz = (kernel.width() - 1 ) / 2;
     for(int i = 0; i < this->map->width(); i++){
         for(int j = 0; j < this->map->height(); j++){
             QRgb color = Qt::white;
             for(int k = 0; k < kernel.width(); k++){
                 for(int l = 0; l < kernel.height(); l++){
                     if(i+k-sz < 0 || i+k-sz > this->map->width() || j+l-sz < 0 || j+l-sz > this->map->height()){
                         continue;
                     }
                     if(kernel.pixel(k,l) == Qt::black && this->map->pixelColor(i+k-sz, j+l-sz) == this->brown){
                         color = Qt::black;
                     }
                 }
             }
             if(color == Qt::black){
                 this->map->setPixelColor(i, j, this->brown);
                 this->change_pixel(i, j, color);
             }
         }
     }
}


void Ground::randomize2()
{
    int width = this->map->width();
    int height = this->map->height();
    this->map->fill(QColor(0, 0, 0, 0));
    QImage empty = QImage(width, height, QImage::Format_RGB32);
    empty.fill(Qt::white);
    this->set_map(empty);
    QImage perlinnoise_map = QImage(width, height, QImage::Format_RGB32);
    double freqx = 100;
    double freqy = 100;
    // Create a PerlinNoise object with the reference permutation vector
    PerlinNoise pn(width/freqx + 1, height/freqy + 1);
    // Visit every pixel of the image and assign a color generated with Perlin noise
    for(int i = 0; i < height; ++i) {     // y
        for(int j = 0; j < width; ++j) {  // x
            double x = (double)j/(freqx);
            double y = (double)i/(freqy);
            double n = pn.noise(x,y,0);
            if(fabs(n) > 0.1)
            {
                perlinnoise_map.setPixel(j,i, qRgba(255, 255, 255, 255));
            }
            else{
                perlinnoise_map.setPixel(j,i, qRgba(0, 0, 0 , 255));
            }
        }
    }
    int line1 = height - 50;
    int line2 = height - 100;
    int line3 = height - 200;
    int line4 = height - 300;
    int line5 = height - 500;
    int line6 = height - 2000;
    double prob = 0.25;
    bool checked = false;
    bool success = false;
    QRandomGenerator r(QDateTime::currentMSecsSinceEpoch() / 1000);
    for(int i = 0; i < width; i++){
        if(perlinnoise_map.pixelColor(i, line1) == QColor(255, 255, 255, 255)){
            this->fillup(i, line1, perlinnoise_map);
        }
        if(perlinnoise_map.pixelColor(i, line2) == QColor(255, 255, 255, 255)){
            this->fillup(i, line2, perlinnoise_map);
        }
        if(perlinnoise_map.pixelColor(i, line3) == QColor(255, 255, 255, 255)){
            this->fillup(i, line3, perlinnoise_map);
        }
        if(perlinnoise_map.pixelColor(i, line4) == QColor(255, 255, 255, 255)){
            this->fillup(i, line4, perlinnoise_map);
        }
        if(perlinnoise_map.pixelColor(i, line5) == QColor(255, 255, 255, 255)){
            this->fillup(i, line5, perlinnoise_map);
        }
        if(perlinnoise_map.pixelColor(i, line6) == QColor(255, 255, 255, 255)){
            if(checked == false){
                if(r.generateDouble() <= prob){
                    success = true;
                }
                else{
                    success = false;
                }
                checked = true;
            }
            if(success){
                this->fillup(i, line6, perlinnoise_map);
            }
        }
        else{
            checked = false;
            success = false;
        }
    }
    QImage kernel(5, 5, QImage::Format_RGB32);
    kernel.fill(Qt::black);
    for(int i = 0; i < 10; i++){
        this->dilate2();
    }

}



