#pragma once

#include "../Physics/ground.h"
#include "../Physics/RigidBody.h"
#include "worms.h"
#include "Barrel.h"

class Worm;
class Barrel;

class Projectile : public RigidBody {
    // General projectile class from which different projectiles types inherit
    public:
        Projectile();
        Projectile(bool explosion_by_delay, double delay, double r, double explosion_r, double damage, double m, std::string weapon_name, double x, double y);
        void print();
        //prints the Projectile's specs

        void explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels);
        // if explosion condition is met (collosion or delay timeout), call this function.
        // the function does the following: 
        // generates damage in explosion_radius, with linear decrease of damage from
        // position of explosion to distance explosion_radius of the center of explosion.
        // destroys all terrain in radius explosion_radius of center of explosion
        // trigger explosion of barrels in the explosion radius
        // destroy the projectile

        void set_inital_position(double x, double y);

        bool change_delay(double dt);

        Projectile* clone();
        //Allows cloning of a projectile. 

    private:
        bool explosion_by_delay; //if has delay functionning
        double delay;
        double radius; 
        double explosion_radius;
        double damage;
        std::string weapon_name;
        double fire_time; //  ms time elapsed since projectile fire. if fire_time >= delay, then call explode()
};


