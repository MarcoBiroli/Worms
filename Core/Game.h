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
               {"left", QPixmap::fromImage(QImage("://Images/Grenade.png"))},
               {"right", QPixmap::fromImage(QImage(""))}}
          },
          {1, {
               {"left", QPixmap::fromImage(QImage(("")))},
               {"right", QPixmap::fromImage(QImage(("")))}}
          }
       };

      enum {
          class_worm_id=-1,
          class_projectile_grenade_id=0, //weapon_id for grenade = 0
          class_projectile_shot_id=1
      };

      QVector<QGraphicsPixmapItem*> pixmap_items;

    public:

      //Initializing "GOD"!!!!
      Ground* ground;
      QGraphicsScene *scene = new QGraphicsScene();
      PhysicsEngine physics_engine;

      //Initializing the important arrays.
      //Worms and projectiles vectors will contain pointers to the same worms and projectiles pointed in the rigid_bodies vector
      //This is done so that we are able to access Worms and Projectile objects as instances of their respective class.
      //Notbaly necessary for Projectile::explode function.
      //The weapons class stores prebuilt projectiles corresponding to a given weapon. Its Pixmap image is at pixmap_images[weapon_id]
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;
      QVector<Barrel*> barrels;
      QVector<Projectile> weapons = QVector<Projectile>({Projectile("Grenade", 0, 0.6, true, 3000, 100, 10, 5, 0, 0, pixmap_images[0]["left"])});

      //Constructors
      Game(QGraphicsScene *iscene, int nb_worms, double max_turn_time=90000, int nb_teams=2, int ground_size_x=5000, int ground_size_y=3000);

      //Methods
      bool gameIteration(double dt);

      void physics_update(double dt); //general update: time and physics

      void graphics_update(); //update pixmap positions and their respective images (left or right)

      void handleEvents(QKeyEvent *k); //event handler

      void nextWorm(); //get next worm alive of the team supposed to play next (-1 if it does not exist)

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left

      void add_to_scene(int class_id, RigidBody new_body); //add a new body to the graphical scene



};
#endif // GAME_H
