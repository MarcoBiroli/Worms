#pragma once

#include <string>

#include "RigidBody.hpp"

#define NUMBER_OF_WEAPONS 2 //global variable fixed for the all execution

class Worm: public RigidBody {
    public:
      Worm(int team_number, std::string personal_name, int health, double mass, double x, double y, ...): RigidBody(mass, x, y, ...);

      bool isAlive();

      void move(bool right);//move right (if right=True, left if right=false) by modyfying x-velocity  ***(how deal with slopes, etc?)
      void jump();//adds upwards velocity
      void pickUpWeapon(int weapon_ID, int ammo);

      void weaponSelect(int weapon_ID);
      void changeAngle(double angle_change); //modifes weapon angle attribute of worms by angle_change (clockwise is positive, counter-clockwise is negative)
      void fireWeapon(double power, std::vector* projectile_list); //with the power from the user input and the angle stored in the Worms class, create projectile(s) specific to current_weapon and add them to the list of projectiles of the game loop

      ~Worm(); //free the weapons array

    private:
      int health;
      int current_weapon;
      int weapon_angle;

      int ammo [NUMBER_OF_WEAPONS];
      
      const int team_number; //team number
      const std::string personal_name;


};