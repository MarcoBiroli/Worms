#pragma once
#ifndef WORMS_H
#define WORMS_H

#include <string>
#include <QVector>
#include <QtMath>
#include <QGraphicsSimpleTextItem>
#include "QPixmap"
#include "QGraphicsPixmapItem"

#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"
#include "Projectile.h"
#include "../GUI/music.h"

#define NUMBER_OF_WEAPONS 15 //global variable for the number of weapons

/*Worms class inherits from Rigidbody. It defines the worm character*/

class Projectile;

class Worm: public RigidBody {

   public:
      //Constructors/ Destructors
      Worm();
      Worm(int team_number, QString personal_name, double bounciness, int health, double mass, double x, double y, QPixmap isprite);
      virtual ~Worm();

      //Virtual Method
      virtual bool isWormAlive();
      virtual void addAmmo(int weaponID, int amountAmmo);

      //Methods around the Worm being alive
      bool isAlive();
      void changeHealth(int dmg); //negative value to increase health
      void wormDeath(); // call destructor and run death animation <- TO BE DELETED??? DOES NOTHING
      bool damage_taken();
      void fall_damage(); //<- TO BE DELETED????

      //Direction Methods
      bool get_direction();
      void set_direction();
      void change_direction(bool t);

      //Weapon methods and firing
      int getTeam() const;
      int get_weapon();
      void update_weapon();
      void weaponSelect(int weapon_ID);
      Projectile* fireWeapon(double power, QVector<Projectile*> &weapons);
      QVector<Projectile*> fireAirWeapon(double power, QVector<Projectile*> &weapons);

      void pickUpWeapon(int weapon_ID, int ammo); //<- TO BE DELETED? IT DOES THE SAME THING AS ADD_AMMO()
      
      //Parameters public
      QPair<int,int> target = QPair<int,int>();
      int amount_airweapon = 5;
      double weapon_angle = 0; //intially 0

      //GRAPHICS
      QGraphicsPixmapItem* reticle = new QGraphicsPixmapItem(this->sprite);
      QGraphicsTextItem* label;
      QGraphicsPixmapItem * weapon_image = new QGraphicsPixmapItem(this->sprite);
      //Weapons images for the worm to hold
      QVector<QImage> weapons = QVector<QImage>({QImage("://Images/weapons/Bazooka_left.png").scaled(21,21),
                                                    QImage("://Images/weapons/BlueGrenade_left.png").scaled(21,21),
                                                    QImage("://Images/weapons/Grenade_left.png").scaled(21,21),
                                                  QImage("://Images/weapons/Dynamite_left.png").scaled(21,21),
                                                  QImage("://Images/weapons/Gun_left.png").scaled(21,21),
                                                  QImage("://Images/weapons/Holy_Grenade.png").scaled(21,21),
                                                  QImage("://Images/weapons/Banana_left.png").scaled(21,21),
                                                  QImage("://Images/weapons/Bat_left.png").scaled(21,21),
                                                  QImage("://Images/weapons/Firepunch_left.png").scaled(21,21),
                                                QImage("://Images/weapons/detonator.png").scaled(21,21),
                                                QImage("://Images/weapons/detonator.png").scaled(21,21),
                                                QImage("://Images/weapons/help.png").scaled(21,21),
                                                });
private:
      int health;
      int current_weapon = 0;
      int ammo[NUMBER_OF_WEAPONS] = { 0 }; //all entries initialized to 0
      const int team_number;
      QString personal_name = "";
      bool damagetaken=false;
      bool wormdirection=true; //true is to the right
      QGraphicsPixmapItem pixmap; // <- WHEN IS THIS USED?? TO BE DELETED???

};
#endif // WORMS_H
