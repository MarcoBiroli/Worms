#pragma once

#include <string>

#include "RigidBody.hpp"

class Worms: public RigidBody {
    public:
      Worms(std::string team_name, std::string personal_name, int health, double mass, double x, double y, ...): RigidBody(mass, x, y, ...);

      bool isAlive();

      void pickUpWeapon(int weapon_ID, int ammo);

      void weaponSelect(int weapon_ID);
      void changeAngle(double angle_change); //modifes weapon angle attribute of worms by angle_change (clockwise is positive, counter-clockwise is negative)
      void fireWeapon(double power, std::vector* projectile_list); //

    private:
      int health;
      int current_weapon;
      int weapon_angle;

      int* weapons[];
      
      const std::string team_name;
      const std::string personal_name;


};