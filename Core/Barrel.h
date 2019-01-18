#pragma once

#include <QVector>

#include "../Physics/RigidBody.h"
#include "Projectile.h"

/*WHAT DOES IT DO??*/

class Projectile;

class Barrel : public RigidBody {
    //Class for the exploding oil barrels
    protected :
        bool should_explode;
    public :
        Barrel();
        Barrel(double m, double x, double y, QPixmap isprite);

        //getter && setter of should_explode
        void setExplode(bool exp);
        bool getExplode();

        void explode(PhysicsEngine &engine, QVector<Projectile*> &projectiles,  QVector<Projectile*> &weapons);
        //Call this function when the barrel is caught in an explosion
        //The function does the following:
        //Remove the barrel from the game
        //Generate a projectile with delay 0.01 at the position of the barrel
        //The explosion of the barrel is in fact the explosion of this new projectile
};
