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

        void print();
        //prints the Projectile's specs

        Projectile(std::string name, int weapon_id, double bounciness, bool explosion_by_delay, double delay, double explosion_r, double damage, double mass, double x, double y, QPixmap isprite);

        Projectile(const Projectile &other);
        Projectile* clone();
        //Allows cloning of a projectile.

        virtual bool on_collision_do(Collider &other);
        void explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels);

        int get_id();
        // if explosion condition is met (collosion or delay timeout), call this function.
        // the function does the following: 
        // generates damage in explosion_radius, with linear decrease of damage from
        // position of explosion to distance explosion_radius of the center of explosion.
        // destroys all terrain in radius explosion_radius of center of explosion
        // trigger explosion of barrels in the explosion radius
        // destroy the projectile

        void set_inital_position(double x, double y);

        bool change_delay(double dt);



    private:
        std::string name;
        bool explosion_by_delay; //if has delay functionning
        double delay;
        double explosion_radius;
        double damage;
        std::string weapon_name; //? Whats the weapon name for
        int weapon_id;
        double fire_time;
};


