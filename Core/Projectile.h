#pragma once

#include "../Physics/ground.h"
#include "../Physics/RigidBody.h"
#include "worms.h"
#include "Barrel.h"

class Worm;
class Barrel;
class RigidBody;

class Projectile : public RigidBody {
    // General projectile class from which different projectiles types inherit
    public:
        Projectile();
        virtual ~Projectile();

        void print();
        //prints the Projectile's specs

        Projectile(std::string name, int weapon_id, double ipower, double bounciness, bool explosion_by_delay, double delay, double explosion_r, double damage, double mass, double x, double y, QPixmap isprite);

        Projectile(const Projectile &other);

        Projectile* clone();
        //Allows cloning of a projectile.

        virtual bool on_collision_do(Collider &other);

        virtual void explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels);
        // if explosion condition is met (collosion or delay timeout), call this function.
        // the function does the following:
        // generates damage in explosion_radius, with linear decrease of damage from
        // position of explosion to distance explosion_radius of the center of explosion.
        // destroys all terrain in radius explosion_radius of center of explosion
        // trigger explosion of barrels in the explosion radius
        // destroy the projectile

        int get_weapon_id() const;

        void set_inital_position(double x, double y);
        // set initial position

        bool change_delay(double dt);
        // changes delay
        bool should_explode = false;



    protected:
        double repulsion_power;
        std::string name;
        bool explosion_by_delay; //if has delay functionning
        double delay;
        double explosion_radius;
        double damage;
        std::string weapon_name;
        int weapon_id;
};


