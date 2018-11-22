#pragma once

//#include "RigidBody.hpp"

class Projectile {
    // General projectile class from which different projectiles types inherit
    public:
        Projectile(bool is_bouncy, int delay, double radius, double explosion_radius, int damage, double mass, std::string weapon_name);

        ~Projectile();

        void print(); 
        //prints the Projectile's specs

        void explode();
        // if explosion condition is met (collosion or delay timeout), call this function
        // which generates damage in explosion_radius, with linear decrease of damage from
        // position of explosion to distance explosion_radius of the center of explosion.

    private:
        bool is_bouncy;
        int delay;
        double radius; 
        double explosion_radius; 
        int damage; 
        double mass; 
        std::string weapon_name;
};

// for now global variables for projectiles Grenade and Shot
Projectile Grenade = Projectile(true, 5, 5, 50, 60, 10, "Grenade");
Projectile Shot = Projectile(false, -1, 0.1, 5, 30, 0.001, "Shot");

// dictionary mapping weapon_id to its Projectile
std::map<int, Projectile> = {0: Grenade, 1: Shot}; 