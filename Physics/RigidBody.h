#pragma once
#include "Force.h"

class RigidBody{
    private:
        double mass = 0, x = 0, y = 0, vx = 0, vy = 0, ax = 0, ay = 0;
        double bouciness_f = 0;
        QVector currentForce = QVector(0, 0);
        bool stable = false; 
    public:
        void addForce(Force F);
        double distance(RigidBody other);
        void simulate(double dt);


        void setbounciness();
        void setm(); setx(); sety(); setvx(); setvy(); 


};
