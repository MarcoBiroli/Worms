#pragma once

#include <string>
#include <QVector>

#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"
#include "Projectile.h"
#include <QtMath>
#include <QGraphicsSimpleTextItem>
#include "QPixmap"
#include "QGraphicsPixmapItem"


#define NUMBER_OF_WEAPONS 15 //global variable fixed for the all execution

class Projectile;

class Worm: public RigidBody {
    public:
      virtual bool isWormAlive();
      virtual void addAmmo(int weaponID, int amountAmmo);

      Worm();
      Worm(int team_number, QString personal_name, double bounciness, int health, double mass, double x, double y, QPixmap isprite);

      virtual ~Worm(); //free the weapons array

      bool isAlive();

      int getTeam() const;
      
      bool damage_taken();

      void fall_damage();

      void pickUpWeapon(int weapon_ID, int ammo);
      
      void weaponSelect(int weapon_ID);

      void changeHealth(int dmg); //negative value to increase health

      //change angle clockwise parameter doesnt make that much sense? change angle += 1
      //void changeAngle(bool clockwise);
      //modifes weapon angle attribute of worms by angle_change (clockwise is positive, counter-clockwise is negative)
      
      Projectile* fireWeapon(double power, QVector<Projectile*> &weapons);
      //with the power from the user input and the angle stored in the Worms class, create
      //projectile(s) specific to current_weapon and add them to the list of projectiles of the game loop

      void wormDeath(); // call destructor and run death animation
    
      bool get_direction();
    
      void set_direction();

      void change_direction(bool t);

      double weapon_angle = 0; //intially 0
      QGraphicsPixmapItem* reticle = new QGraphicsPixmapItem(this->sprite);
      QGraphicsTextItem* label;
      QGraphicsPixmapItem * weapon_image = new QGraphicsPixmapItem(this->sprite);
      QVector<QImage> weapons = QVector<QImage>({QImage("://Images/weapons/Bazooka_left.png").scaled(21,21),
                                                    QImage("://Images/weapons/BlueGrenade_left.png").scaled(21,21),
                                                    QImage("://Images/weapons/Grenade_left.png").scaled(21,21),
                                                  QImage("://Images/weapons/Dynamite_left.png").scaled(21,21),
                                                  QImage("://Images/weapons/Gun_left.png").scaled(21,21),
                                                  QImage("://Images/weapons/Holy_Grenade.png").scaled(21,21),
                                                  QImage("://Images/weapons/Banana_left.png").scaled(21,21)});

      void update_weapon();
private:
      int health;
      int current_weapon = 0;
      int ammo[NUMBER_OF_WEAPONS] = { 0 }; //all entries initialized to 0
      const int team_number; //team number
      QString personal_name = "";
      //int weapon_ID = 0;
      bool damagetaken=false;
      bool wormdirection=true; //true is to the right
      QGraphicsPixmapItem pixmap;
};
