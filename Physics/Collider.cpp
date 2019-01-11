#include "Collider.h"
#include "qdebug.h"

//Constructors
bool Collider::on_collision_do(Collider &other)
{
    return false; // not deleted by default
}

void Collider::circ_delete(int x, int y, double radius)
{

}

Collider::Collider()
{
}

Collider::Collider(double ix, double iy, QImage map)
{
    //initialization of the parameters
    this->x = ix;
    this->y = iy;
    this->colliding_map = map;
    this->cmx = 0;
    this ->cmy = 0;
    this->countblack = 0;

    //It loops over the width and height of the colliding map; checks the pixel color; increments the countblack parameter.
    //and adds all the x-coordinates and y-coordinates seperately.

    for (int i = 0; i< this->colliding_map.width(); i++){
        for (int j = 0; j< this-> colliding_map.height(); j++){
            if (this->colliding_map.pixelColor(i,j) == Qt::black || this->colliding_map.pixelColor(i,j) == Qt::blue) { //temporary solution to avoid the objects (worms, weapons) to fall for ever
                this->cmx += i;
                this->cmy += j;
                this->countblack += 1;
            }
        }
    }

    //Assuming that the collider has uniform density the cmx will be the sum of the x-coordinates of black pixels over the total number
    //of black pixels. Same for the cmy.
    this->cmx = cmx / this->countblack;
    this->cmy = cmy / this->countblack;

    //Converting the skin_depth_percent to skin_depth_pixels
    this->skin_depth_pixels = this->skin_depth_percent*this->countblack;
}

Collider::Collider(double ix, double iy)
{
    //Same principle as the second constructor
    this->x = ix;
    this->y = iy;
    this->colliding_map.fill(QColor(0, 0, 0));
    this->cmx = 0;
    this ->cmy = 0;
    this->countblack = 0;
    for (int i = 0; i< this->colliding_map.width(); i++){
        for (int j = 0; j< this-> colliding_map.height(); j++){
            if (this->colliding_map.pixelColor(i,j) == Qt::black || this->colliding_map.pixelColor(i,j) == Qt::blue) {
                this->cmx += i;
                this->cmy += j;
                this->countblack += 1;
            }
        }
    }
    this->cmx = cmx / this->countblack;
    this->cmy = cmy / this->countblack;
    this->skin_depth_pixels = this->skin_depth_percent*this->countblack;
}

Collider::~Collider()
{

}

//Get and Set private variables

int Collider::getId() const { return this->id;}
void Collider::setId(int iid) {this->id = iid;}


void Collider::setSkin(double depth_percent) {
    this->skin_depth_percent = depth_percent;
    //Updates the skin_depth_pixels
    this->skin_depth_pixels = this->skin_depth_percent * this->countblack;
}

double Collider::getX() const {return this->x;}
double Collider::getY() const {return this->y;}

void Collider::setX(double x1) {this->x = x1;}
void Collider::setY(double y1) {this->y = y1;}


double Collider::getcmX() const {return this->cmx;}
double Collider::getcmY() const {return this->cmy;}

void Collider::setcmX(double cx) {this->cmx = cx;}
void Collider::setcmY(double cy) {this->cmy = cy;}

QImage Collider::get_map() const {return this->colliding_map;}

void Collider::set_map(QImage map) {
    this->colliding_map = map;
    //updates the countblack parameter through the loop
    this->countblack = 0;
    for (int i = 0; i< this->colliding_map.width(); i++){
        for (int j = 0; j< this-> colliding_map.height(); j++){
            if (this->colliding_map.pixelColor(i,j) == Qt::black || this->colliding_map.pixelColor(i,j) == Qt::blue) {
                this->countblack += 1;
            }
        }
    }
    //updates the skin_depth_pixels
    this->skin_depth_pixels = this->skin_depth_percent * this->countblack;
}

int Collider::getWidth() const
{
    return this->colliding_map.width();
}

int Collider::getHeight() const
{
    return this->colliding_map.height();
}

void Collider::change_pixel(int i, int j, QColor color) {
    //if the color we give is black and the current color of pixel(i,j) is not black we increment the parameter countblack
    //otherwise we do not change anything
    if (color == Qt::black  || color == Qt::blue){
        if (this->colliding_map.pixelColor(i,j) != Qt::black && this->colliding_map.pixelColor(i,j) != Qt::blue){
            this->countblack += 1;
            this->colliding_map.setPixelColor(i,j,color);
        }
    }
    //if the color is not black and the current color of pixel(i,j) is black we decrease the parameter countblack
    //otherwise we do not change anything
    else {
        if (this->colliding_map.pixelColor(i,j) == Qt::black || this->colliding_map.pixelColor(i,j) == Qt::blue){
            this->countblack -= 1;
            this->colliding_map.setPixelColor(i,j,color);
        }
    }
    //update the skin_depth_pixels
    this->skin_depth_pixels = this->skin_depth_percent * this->countblack;
}

QRgb Collider::get_color(int i, int j) const
{
    return this->colliding_map.pixel(i, j);
}


//Collision check method

QPair<bool, QPair<double, double> > Collider::check_collision(Collider &other)
{
    //Broadband phase AABB collision
    if(!(this->getX() < other.getX() + other.getWidth() &&
          this->getX() + this->getWidth() > other.getX() &&
          this->getY() < other.getY() + other.getHeight() &&
          this->getY() + this->getHeight() > other.getY()))
      {
          return QPair<bool, QPair<double, double>>(false, QPair<double, double>());
      }

    //Specific Phase
    //Initializing the parameters
    bool colliding = false;
    double cm_otherx = 0, cm_othery = 0;
    int nb_colliding_pixels = 0;

    //It loops over the width and height of the colliding map checking where the black pixels overlap
    for (int i = 0; i < this->getWidth(); i++) {
        for (int j = 0; j < this->getHeight(); j++){
            if (this->colliding_map.pixelColor(i,j) == Qt::black || this->colliding_map.pixelColor(i,j) == Qt::blue){
                //If the pixel (i,j) is part of the others collider map, taking care of the x,y change of coordinates (top-left corner)
                if (other.x <= x+i && x + i< other.x + other.getWidth() && other.y <= y + j && y + j < other.y + other.getHeight()){
                    //check if this pixel is black
                    if (other.colliding_map.pixelColor(x+i-other.x, y+j - other.y) == Qt::black || other.colliding_map.pixelColor(x+i-other.x, y+j - other.y) == Qt::blue){
                        //update the parameters
                        colliding = true;
                        cm_otherx += i; cm_othery += j; nb_colliding_pixels++;
                    }
                }
            }
        }
    }

    //computing the colliding center of mass as done previously in the constructor
    cm_otherx = cm_otherx / nb_colliding_pixels;
    cm_othery = cm_othery / nb_colliding_pixels;

    //ignore collision if the skin_depth threshold hasn't been met
    if(nb_colliding_pixels <= this->skin_depth_pixels){
        return QPair<bool, QPair<double, double>>(false, QPair<double, double>());
    }
    //return bool colliding, and the x,y - coordinates of the normal.
    return QPair<bool, QPair<double, double>> (colliding, QPair<double, double> (cmx-cm_otherx,cmy-cm_othery));
}

bool Collider::isWorm(){
    return false;
}

void Collider::addAmmo(int weaponID, int amountAmmo){
    return; //set by default, used only for Worms and Crates
}
