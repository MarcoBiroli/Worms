#pragma once

#include <string>
#include <QVector>

#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"
#include "Projectile.h"
#include <QtMath>


#define NUMBER_OF_WEAPONS 2 //global variable fixed for the all execution

class Projectile;

class Worm: public RigidBody {
    public:
      Worm();
      Worm(int team_number, std::string personal_name, int health, double mass, double x, double y);

      ~Worm(); //free the weapons array

      bool isAlive() const;

      int getTeam() const;
      
      bool damage_taken();

      void fall_damage();

      void pickUpWeapon(int weapon_ID, int ammo);
      
      void weaponSelect(int weapon_ID);

      void changeHealth(int dmg); //negative value to increase health

      void changeAngle(bool clockwise); //modifes weapon angle attribute of worms by angle_change (clockwise is positive, counter-clockwise is negative)
      
      void fireWeapon(double power, QVector<Projectile> weapons, PhysicsEngine &engine, QVector<Projectile*> &projectiles); //with the power from the user input and the angle stored in the Worms class, create projectile(s) specific to current_weapon and add them to the list of projectiles of the game loop

      void move(bool right);//move right (if right=True, left if right=false) by modyfying x-velocity  ***(how deal with slopes, etc?)
      
      void wormDeath(); // call destructor and run death animation

    private:
      int health;
      int current_weapon;
      double weapon_angle = 0; //intially 0
      int ammo[NUMBER_OF_WEAPONS] = { 0 }; //all entries initialized to 0
      const int team_number; //team number
      const std::string personal_name;
      bool isTurn;
      int weapon_ID = 0;
      bool damagetaken=false;

};
