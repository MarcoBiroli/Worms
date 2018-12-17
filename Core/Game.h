#ifndef GAME_H
#define GAME_H

#include "QVector"
#include "QMap"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QtWidgets>
#include <QWidget>
#include <QObject>

#include "../GUI/ground.h"
#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"

#include "Projectile.h"
#include "worms.h"
#include "Barrel.h"
#include "../GUI/ground.h"

class Game{
    private:

      double max_turn_time;
      int nb_teams;

      double turn_timer;
      bool paused;

      int team_playing;
      QVector<int> worms_playing; //index in vector worms of each team (-1 if the team is dead)

      //GRAPHICS

      //maps a class_id to the path of the image to display for objects of that class
      QMap<int, QMap<QString, QPixmap>> pixmap_images =
      {
          {-1, {
               {"left", QPixmap::fromImage(QImage("://Images/Clipart_worm_left.png").scaled(QSize(32,32)))},
               {"right", QPixmap::fromImage(QImage("://Images/Clipart_worm_right.png").scaled(QSize(32,32)))}}
          },
          {0, {
               {"left", QPixmap::fromImage(QImage("://Images/Grenade.png").scaled(QSize(20,20)))},
               {"right", QPixmap::fromImage(QImage(""))}}
          },
          {7, {
               {"left", QPixmap::fromImage(QImage("://Images/Clipart_weapon_7_left.png").scaled(QSize(20,20)))},
               {"right", QPixmap::fromImage(QImage(("")))}}
          },
          {13, {
               {"left", QPixmap::fromImage(QImage("://Images/Clipart_weapon_13_left.png").scaled(QSize(20,20)))},
               {"right", QPixmap::fromImage(QImage(("")))}}
          },
          {4, {
               {"left", QPixmap::fromImage(QImage(("://Images/Bazooka_left.png")))},
               {"right", QPixmap::fromImage(QImage(("://Images/Bazooka_right.png")))}}
          },
          {2, {
               {"left", QPixmap::fromImage(QImage(("://Images/Bat_left.png")))},
               {"right", QPixmap::fromImage(QImage(("://Images/Bat_right.png")))}}
          },
          {3, {
               {"left", QPixmap::fromImage(QImage(("://Images/Boxing_left.png")))},
               {"right", QPixmap::fromImage(QImage(("://Images/Boxing_right.png")))}}
          }
       };

      enum {
          class_worm_id=-1,
          class_projectile_grenade_id=0, //weapon_id for grenade = 0
          class_projectile_shot_id=1, //weapond_id for shot = 1
          class_projectile_bat_id = 2,
          class_projectile_boxing_id = 3,
          class_projectile_bazooka_id = 4,
          class_projectile_dynamite_id=7, //weapon_id for dynamite = 7
          class_projectile_rocket_id=13 //id for rocket (bazooka projectile) = 13
      };

      //maps the name of each spritesheet to the set of corresponding frames
      //1 maps to the set of frames showing the worm dying in an explosion
      //2 maps to the set of frames showing an explosion
      QMap<int, QVector<QPixmap>> spritesheets =
      {
      {1, {QPixmap::fromImage(QImage("://Images/Dying worm version 6-1 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-2 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-3 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-4 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-5 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-6 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-7 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-8 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-9 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-10 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-11 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-12 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-13 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Dying worm version 6-14 (glissées).tiff").scaled(QSize(32,32)))}

       },
       {2, {QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-1 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-2 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-3 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-4 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-5 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-6 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-7 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-8 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-9 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-10 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-11 (glissées).tiff").scaled(QSize(32,32))),
           QPixmap::fromImage(QImage("://Images/Explosions/Explosion 2 frames/Explosion 2-12 (glissées).tiff").scaled(QSize(32,32)))}
       }
      };

      QVector<QGraphicsPixmapItem*> pixmap_items;

      //weapons menu for now it has a worm in it
      QGraphicsPixmapItem* menu = new QGraphicsPixmapItem(pixmap_images[0]["left"].scaled(70,70));

    public:

      //Initializing "GOD"!!!!
      Ground* ground;
      QGraphicsScene *scene;
      QGraphicsView *view;
      PhysicsEngine physics_engine;

      //Initializing the important arrays.
      //Worms and projectiles vectors will contain pointers to the same worms and projectiles pointed in the rigid_bodies vector
      //This is done so that we are able to access Worms and Projectile objects as instances of their respective class.
      //Notbaly necessary for Projectile::explode function.
      //The weapons class stores prebuilt projectiles corresponding to a given weapon. Its Pixmap image is at pixmap_images[weapon_id]
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;
      QVector<Barrel*> barrels;
      QVector<Projectile> weapons;

      //Constructors
      Game(QGraphicsScene *iscene, QGraphicsView *iview,  int nb_worms, double max_turn_time=90000, int nb_teams=2, int ground_size_x=5000, int ground_size_y=3000);

      //Methods
      void weapon_list();

      bool gameIteration(double dt);

      void physics_update(double dt); //general update: time and physics

      void graphics_update(); //update pixmap positions and their respective images (left or right)

      void handleEvents(QKeyEvent *k); //event handler

      void nextWorm(); //get next worm alive of the team supposed to play next (-1 if it does not exist)

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left

      void add_to_scene(int class_id, RigidBody new_body); //add a new body to the graphical scene



};
#endif // GAME_H
