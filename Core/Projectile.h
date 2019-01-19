#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <string>
using namespace std;

#include "../GUI/music.h"
#include "../Physics/ground.h"
#include "../Physics/RigidBody.h"
#include "worms.h"
#include "Barrel.h"

/*Projectile Class inherits from Rigidbody as it is subject to physics
  All Weapons and Crates are projectile*/

class Worm;
class Barrel;
class RigidBody;

class Projectile : public RigidBody {

    public:
        //Constructor / Destructors
        Projectile();
        Projectile(std::string name, int weapon_id, double ipower, double bounciness, bool explosion_by_delay, double delay, double explosion_r, double damage, double mass, double x, double y, QPixmap isprite);
        Projectile(const Projectile &other);
        virtual Projectile* clone(); //Allows cloning of a projectile.
        virtual ~Projectile();

        //Type of weapons
        bool is_hand_to_hand = false;
        bool is_airweapon = false;

        //??
        bool should_explode = false;
        Worm* firing_worm;
        //???????
        /*
        void set_firing_worm(Worm* iworm){
            this->firing_worm = iworm;
            this->white_list.append(iworm);
            iworm->white_list.append(this);
        }
        */

        //Redefinition of virtual on_collision_do of Collider
        virtual bool on_collision_do(Collider &other);

        //Exploding of Projectiles
        virtual void explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels);

        //Get/ Set weapons
        int get_weapon_id() const;
        void set_inital_position(double x, double y);

        // Changes the delay of a projectile by dt
        bool change_delay(double dt);

    protected:
        //Parameters
        double repulsion_power;
        std::string name;
        bool explosion_by_delay;
        double delay;
        double explosion_radius;
        double damage;
        std::string weapon_name; // <- TO BE DELETED SAME THING AS NAME
        int weapon_id; // <- TO BE DELETED NOT IMPORTANT
};
#endif // PROJECTILE_H

