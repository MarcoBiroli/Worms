#pragma once
#include "Force.h"

class RigidBody{
    private:
        double mass = 0, x = 0, y = 0, vx = 0, vy = 0, ax = 0, ay = 0;
        double bouciness_f = 0;
        QVector currentForce = QVector(0, 0);
        bool stable = false; 
        int id;
    public:
        void addForce(Force F);
        double distance(RigidBody other);
        void simulate(double dt);


        void setbounciness();
        void setm(); 
        void setx(); 
        void sety(); 
        void setvx(); 
        void setvy(); 
        void setax();
        void setay();
        bool getstable();
       
};
