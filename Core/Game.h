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
#include "weapon_menu.h"
#include "crates.h"

class Game{
    private:
      double max_turn_time;
      int nb_teams;

      int number_of_turns;

      double turn_timer;
      bool paused;
      bool has_shot;

      int team_playing;
      QVector<int> worms_playing; //index in vector worms of each team (-1 if the team is dead)
      weapon_menu* menu; //contains all weapons

      //temporary storing of the image of worms until spritesheets work
      QMap<QString, QPixmap> worm_image = {
        {"left", QPixmap::fromImage(QImage("://Images/rigidbodies/Worm_left.png").scaled(32,32))},
        {"right", QPixmap::fromImage(QImage("://Images/rigidbodies/Worm_right.png").scaled(32,32))}
      };

      QPixmap crate_image = QPixmap::fromImage(QImage("://Images/rigidbodies/aid.png").scaled(32,32));


      //GRAPHICS
      QMap<QString, QVector<QPixmap>> spritesheets;

      QGraphicsProxyWidget *proxymenu;

    public:

      //Initializing "GOD"!!!!
      Ground* ground;
      QGraphicsScene *scene;
      QGraphicsView *view;
      PhysicsEngine* physics_engine;

      //Initializing the important arrays.
      //Worms and projectiles vectors will contain pointers to the same worms and projectiles pointed in the rigid_bodies vector
      //This is done so that we are able to access Worms and Projectile objects as instances of their respective class.
      //Notbaly necessary for Projectile::explode function.
      //The weapons class stores prebuilt projectiles corresponding to a given weapon. Its Pixmap image is at pixmap_images[weapon_id]
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;
      QVector<Barrel*> barrels;
      QVector<Projectile*> weapons;
      QVector<Crate*> crates;

      double heightmenu = 150;
      double widthmenu = 200;

      //Constructors
      Game(QGraphicsScene *iscene, QGraphicsView *iview,  int nb_worms, double max_turn_time=90000, int nb_teams=2, int ground_size_x=5000, int ground_size_y=3000);

      ~Game();

      //Methods
      void weapon_list();

      bool gameIteration(double dt);

      void physics_update(double dt); //general update: time and physics

      void graphics_update(); //update pixmap positions and their respective images (left or right)

      void handleEvents(QKeyEvent *k); //event handler

      void nextWorm(); //get next worm alive of the team supposed to play next (-1 if it does not exist)

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left

      void changemenupos(QPoint point);

      void changemenusize(double dx,double dy);
};
#endif // GAME_H
