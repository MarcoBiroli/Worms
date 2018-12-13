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
#include "../GUI/customview.h"
#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"

#include "Projectile.h"
#include "worms.h"
#include "Barrel.h"
#include "../GUI/ground.h"

class Game{
    public:
      Ground ground; //Public to be able to modify it at creation in main

      Game(int nb_worms, double max_turn_time=90000, int nb_teams=2, int ground_size_x=5000, int ground_size_y=3000s);//Constructor

      bool gameIteration(QKeyEvent *k, double dt);

      void update(double dt); //general update: time and physics

      void handleEvents(QKeyEvent *k); //event handler

      void nextWorm(); //get next worm alive of the team supposed to play next (-1 if it does not exist)

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left

      void add_to_scene(QGraphicsScene &scene, int class_id, RigidBody new_body); //add a new body to the graphical scene

    private:
      //Worms and projectiles vectors will contain pointers to the same worms and projectiles pointed in the rigid_bodies vector
      //This is done so that we are able to access Worms and Projectile objects as instances of their respective class. Notbaly necessary for Projectile::explode function.
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;
      QVector<Barrel*> barrels;

      //Stores prebuilt projectiles corresponding to a given weapon. Copy, set position and force when shooting.
      QList<Projectile> weapons = {Projectile(true, 5000, 5, 50, 60, 10, "Grenade", 0, 0), Projectile(false, -1, 0.1, 5, 30, 0.001, "Shot", 0, 0)};

      PhysicsEngine physics_engine;

      double max_turn_time;
      int nb_teams;

      double turn_timer;
      bool paused;

      int team_playing;
      QVector<int> worms_playing; //index in vector worms of each team (-1 if the team is dead)

      //GRAPHICS

      //maps a class_id to the path of the image to display for objects of that class
      QMap<int, QMap<QString, QImage>> image_path =
      {
          {-1, {
               {"left", QImage("://Images/Clipart_worm_right.png").scaled(QSize(32,32))},
               {"right", QImage("://Images/Clipart_worm_right.png").scaled(QSize(32,32))}}
          },
          {0, {
               {"left", QImage("")},
               {"right", QImage("")}}
          },
          {1, {
               {"left", QImage("")},
               {"right", QImage("")}}
          }
       };

      enum {
          class_worm_id=-1,
          class_projectile_grenade_id=0,
          class_projectile_shot_id=1
      };

      QVector<QGraphicsPixmapItem*> pixmap_items;

};
#endif // GAME_H
