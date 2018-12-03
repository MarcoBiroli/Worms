#pragma once

#include "../Physics/ground.h"
#include "../Physics/RigidBody.h"
#include "worms.h"

class Worm;

class Projectile : public RigidBody {
    // General projectile class from which different projectiles types inherit
    public:
        Projectile();
        Projectile(bool is_bouncy, double delay, double r, double explosion_r, double damage, double m, std::string weapon_name, double x, double y);
        void print();
        //prints the Projectile's specs

        void explode(Ground &ground, QMap<int, RigidBody*> &rigidbodies, QVector<Projectile*> &projectiles, QVector<Worm*> &worms) ;
        // if explosion condition is met (collosion or delay timeout), call this function.
        // the function does the following: 
        // generates damage in explosion_radius, with linear decrease of damage from
        // position of explosion to distance explosion_radius of the center of explosion.
        // destroys all terrain in radius explosion_radius of center of explosion

        void set_inital_position(double x, double y);

        Projectile* clone();
        //Allows cloning of a projectile. 

    private:
        bool is_bouncy;
        double delay;
        double radius; 
        double explosion_radius;
        double damage;
        double mass; 
        std::string weapon_name;
        double fire_time;
};

//Stores prebuilt projectiles corresponding to a given weapon. Copy, set position and force when shooting.
