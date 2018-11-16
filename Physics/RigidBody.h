#pragma once
#include "Force.h"

class RigidBody{
    private:
        double mass = 0, x = 0, y = 0, vx = 0, vy = 0, ax = 0, ay = 0;
        Force currentForce;
    public:
        void addForce(Force F);
};
