#include "ground.h"

//Constructors
Ground::Ground() : Collider (){ //Creates an undefined Ground
    this->map = new QImage();
    item = new QGraphicsPixmapItem();
}

Ground::Ground(const int width, const int height, QColor watercolor, QColor terraincolor, QColor grasscolor): Collider(){
    this->width = width;
    this->height = height;
    this->terraincolor = terraincolor;
    this->watercolor = watercolor;
    this->grasscolor = grasscolor;

    this->map = new QImage(width, height, QImage::Format_ARGB32); //Initialize the variables.
    this->set_map(*this->map);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(*this->map));
    for(int i = 0; i < width; i++){
        if(0.05*width < i && i < 0.95*width){
            for(int j = 0; j < height; j++){
                if(j > 1800 && j < 1800 + (2+ qSin((double)i/30))*20){
                    this->change_pixel(i,j, Qt::black);
                    this->map->setPixelColor(i, j, grasscolor);
                }
                else if(j > 1800){
                    this->change_pixel(i,j, Qt::black);
                    this->map->setPixelColor(i, j, terraincolor);

                }
            }
        }
    }
    this->is_ground = true;
}

//get functions

//This gets the Displayable Version of the Ground.
QGraphicsPixmapItem* Ground::getPixmap() const{
    item->setPixmap(QPixmap::fromImage(*this->map));
    return item;
}

QImage* Ground::getMap() const{ //This returns the ground itself.
    return this->map;
}

//It gets the 6 neighbours of a pixel (i,j)
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


//Randomize functions:
// randomize2() is a function which uses random consine/ sine functions
// randomize3() is a function which uses perlin noise

//First randomized function
void Ground::randomize2() {
    srand(time(NULL));
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
                this->map->setPixel(i,j,qRgba(0,0,0,0)); //set the part above the ground to transparent
                this->change_pixel(i, j, Qt::white);
            }
            /*if (j >= terrain_height && j < sea_level){
                this->map->setPixelColor(i, j, terraincolor);  //ground in brown
                this->change_pixel(i, j, Qt::black);*/

            if (j >= terrain_height && j <= grass_height){
                this->map->setPixelColor(i,j,grasscolor);
                this -> change_pixel(i,j, Qt::black);
            }
            if (j > grass_height && j < height){
                this -> map -> setPixelColor(i,j,terraincolor);
                this -> change_pixel(i,j, Qt::black);
            }
            /*
            if (j > height-10){
                this -> change_pixel(i,j, Qt::blue); //temporary solution to avoid the objects (worms, weapons) to fall for ever
            }  //blue pixels are rigid body but can't be delete
            if (i < 10){
                this -> change_pixel(i,j,Qt::blue);
            }
            if (i > width-10){
                this -> change_pixel(i,j,Qt::blue);
            }*/
        }
    }
    this->is_ground = true;
}

//Second randomize
//Neccessary functions for the second randomize:

void Ground::fillup(int i, int j, QImage& perlin)
{
    QVector<QPair<int, int>> stack;
    stack.append(QPair<int, int>(i,j));
    while(stack.length() != 0){
        QPair<int, int> cur = stack.takeLast();
        this->change_pixel(cur.first, cur.second, Qt::black);
        this->map->setPixelColor(cur.first, cur.second, terraincolor);
        if(perlin.pixelColor(cur.first, cur.second) != QColor(0, 0, 0, 255)){
            perlin.setPixelColor(cur.first, cur.second, QColor(0, 0, 0, 255));
            stack.append(getNeighbors(cur));
        }
    }
}

// O(n^2) solution to find the Manhattan distance to "on" pixels in a two dimension array
int** Ground::manhattan(){
    int ** out = new int*[this->width];
    for(int i = 0; i < this->width; i++){
        out[i] = new int[this->height];
    }
    // traverse from top left to bottom right
    for (int i=0; i<this->map->width(); i++){
        for (int j=0; j< this->map->height(); j++){
            if (this->map->pixelColor(i,j) == this->terraincolor){
                // first pass and pixel was on, it gets a zero
                out[i][j] = 0;
            } else {
                // pixel was off
                // It is at most the sum of the lengths of the array
                // away from a pixel that is on
                out[i][j] = this->width + this->height;
                // or one more than the pixel to the north
                if (i>0) out[i][j] = std::min(out[i][j], out[i-1][j]+1);
                // or one more than the pixel to the west
                if (j>0) out[i][j] = std::min(out[i][j], out[i][j-1]+1);
            }
        }
    }
    // traverse from bottom right to top left
    for (int i=this->width-1; i>=0; i--){
        for (int j=this->height-1; j>=0; j--){
            // either what we had on the first pass
            // or one more than the pixel to the south
            if (i+1<this->width) out[i][j] = std::min(out[i][j], out[i+1][j]+1);
            // or one more than the pixel to the east
            if (j+1<this->height) out[i][j] = std::min(out[i][j], out[i][j+1]+1);
        }
    }
    return out;
}

void Ground::dilate4(QColor color, int depth){
    int** distances = this->manhattan();
    for (int i=0; i<this->width; i++){
        for (int j=0; j<this->height; j++){
            if(distances[i][j] <= depth && distances[i][j] != 0){
                this->map->setPixelColor(i, j, color);
                this->change_pixel(i, j, Qt::black);
            }
        }
    }
}

void Ground::dilate3(QColor color, int depth){
    for(int i = 0; i < this->map->width(); i++){
        for(int j = 0; j < this->map->height(); j++){
            if(this->map->pixelColor(i, j) == this->terraincolor){
                for(int k = -(depth-1)/2; k <= (depth-1)/2; k++){
                    for(int l = -(depth-1)/2; l <= (depth-1)/2; l++){
                        if(i+k > 0 && i + k < this->map->width() && j+l > 0 && j+l < this->map->height() && abs(k)+abs(l) < depth &&
                                this->map->pixelColor(i+k,j+l) == QColor(0, 0, 0, 127)){
                            this->map->setPixelColor(i+k, j+l, QColor(0,0,0,127));
                        }
                    }
                }
            }
        }
    }
    for (int i=0; i<this->map->width(); i++){
        for (int j=0; j < this->map->height(); j++){
            if (this->map->pixelColor(i, j) == QColor(0, 0, 0, 127)){
                this->map->setPixelColor(i, j, color);
                this->change_pixel(i, j, Qt::black);
            }
        }
    }
}

void Ground::randomize3()
{
    this->map->fill(QColor(0, 0, 0, 0));
    QImage empty = QImage(this->width, this->height, QImage::Format_RGB32);
    empty.fill(Qt::white);
    this->set_map(empty);
    QImage perlinnoise_map = QImage(width, height, QImage::Format_RGB32);
    double freqx = 150;
    double freqy = 150;
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
    int line5 = height - 800;
    int line6 = height - 1500;
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
    this->dilate4(this->terraincolor, 20);
    this->dilate4(this->grasscolor, 10);
}


//Delete functions for the ground

void Ground::delete_ground(int x, int y){ //This deletes the ground at one point of coordinate (x,y).
    if(this->get_map().pixelColor(x,y) == Qt::black){
        this->change_pixel(x, y, Qt::white);
        this->map->setPixel(x, y, qRgba(255,255,255,0));
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

