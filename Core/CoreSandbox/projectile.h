#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QString>

#include "RigidBody.h"

class Projectile : public RigidBody {
    // General projectile class from which different projectiles types inherit
    public:
        Projectile(bool is_bouncy, int delay, double radius, double explosion_radius, int damage, double mass, QString weapon_name, double x, double y, bool explode, double fire_time);
        void print();
        //prints the Projectile's specs

        void set_inital_position(double x, double y);

        Projectile* clone();
        //Allows cloning of a projectile.

    private:
        bool is_bouncy;
        int delay;
        double radius;
        double explosion_radius;
        int damage;
        double mass;
        std::string weapon_name;
};

//Stores prebuilt projectiles corresponding to a given weapon. Copy, set position and force when shooting.
Projectile weapons[2] = {Projectile(true, 5, 5, 50, 60, 10, "Grenade", 0, 0, false, 0), Projectile(false, -1, 0.1, 5, 30, 0.001, "Shot", 0, 0, false, 0)};

#endif // PROJECTILE_H
