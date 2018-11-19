#pragma once
#include "math.h"

class Force{
    private:
        double magnitude = 0, x = 0, y = 0;
    public:
        void computeMagnitude(){
            this->magnitude = pow(pow(x, 2) + pow(y, 2), 0.5);
        }
        void setX(double ix){
            this->x = ix;
            this->computeMagnitude();
        }
        void setY(double iy){
            this->y = iy;
            this->computeMagnitude();
        }
        void set
        Force operator+(const Force& other){

        }

};