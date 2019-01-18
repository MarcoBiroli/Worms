#pragma once
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
#include <QMouseEvent>
#include <QtConcurrent/QtConcurrent>
#include <QSound>
#include <QMediaPlayer>

#include "../GUI/water.h"
#include "../GUI/ground.h"
#include "../GUI/customview.h"
#include "../GUI/spritesheet.h"
#include "../GUI/music.h"

#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"

#include "QThread"
#include "animationthread.h"

#include "Projectile.h"
#include "worms.h"
#include "Barrel.h"
#include "crates.h"
#include "handtohand.h"

#include "weapon_menu.h"
#include "settings.h"
#include "pause.h"
#include "mainwindow.h"

#include "../GUI/customview.h"
#include "../GUI/water.h"
#include "QThread"
#include "animationthread.h"
#include "../GUI/spritesheet.h"
#include "handtohand.h"




/*WHAT IS THIS CLASS???????*/ //Megi this is forward declaration.

class CustomView;
class Game : public QObject{
    Q_OBJECT

    private:
      //Parameters
      double max_turn_time;
      int nb_teams;
      int number_of_turns;
      bool next_turn;
      double turn_timer;

      bool paused; //Game pause -> shows pause menu
      bool has_shot;
      int team_playing;
      int healthcrates;
      QVector<int> worms_playing; //index in vector worms of each team (-1 if the team is dead)

      //Menus
      weapon_menu* weaponmenu; //contains all weapons
      QGraphicsProxyWidget *proxymenu;
      QGraphicsProxyWidget *proxypause;

      //GRAPHICS

      QMap<QString, QPixmap> worm_image = {
        {"left", QPixmap::fromImage(QImage("://Images/rigidbodies/Worm_left.png").scaled(42,42))},
        {"right", QPixmap::fromImage(QImage("://Images/rigidbodies/Worm_right.png").scaled(42,42))}
      };

      QPixmap crate_image = QPixmap::fromImage(QImage("://Images/rigidbodies/aid.png").scaled(32,32));
      QPixmap crate_image_health = QPixmap::fromImage(QImage("://Images/rigidbodies/aid.png").scaled(32,32));
      QPixmap crate_image_weapon = QPixmap::fromImage(QImage("://Images/rigidbodies/wep.png").scaled(32,32));
      QPixmap barrel_image = QPixmap::fromImage(QImage("://Images/rigidbodies/barrel.png").scaled(40,40));


      QMap<QString, QVector<QPixmap>> spritesheets; //<- ??????


      //Colors
      QColor water_blue = qRgba(4, 168, 210, 255);
      QColor water_sun = qRgba(12, 116, 223,255);
      QColor terrain_g = qRgba(6, 86, 19, 255);
      QColor grass_green = qRgba(121,178,51,255);
      QColor water_fire =  qRgba(204, 0, 0,255);
      QColor terrain_brown = qRgba(125,65,6, 255);
      QColor grass_fire =  qRgba(204, 0, 0,255);
      QColor terrain_grey = qRgba(25, 25, 25,255);

      //Neccessary for water animation
      QThread* thread;
      AnimationThread* worker;
      QGraphicsPixmapItem* water_sprite = new QGraphicsPixmapItem();

    public:
      //Initializing "GOD"!!!!
      Ground* ground;
      QGraphicsScene *scene;
      CustomView *view;
      PhysicsEngine* physics_engine;

      //Initializing the important arrays.
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;
      QVector<Barrel*> barrels;
      QVector<Projectile*> weapons;
      QVector<Crate*> crates;

      double heightmenu = 300;
      double widthmenu = 400;
      int power = 20;

      //Constructors / Destructors
      Game(QApplication* a, int number,MainWindow * mainwindow, QGraphicsScene *iscene, CustomView *iview,  Settings *settings, int ground_size_x=5000, int ground_size_y=3000);

      virtual ~Game();

      //Methods

      void weapon_list(); //Stores prebuilt weapons

      bool gameIteration(double dt);
      void physics_update(double dt); //general update: time and physics
      void graphics_update(); //update pixmap positions and their respective images (left or right)
      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left

      void nextWorm(); //get next worm alive of the team supposed to play next (-1 if it does not exist)

      //Menu methods
      void changemenupos(QPoint point);
      void changemenusize(double dx,double dy);

      //User inputs
      void handleEvents(QKeyEvent *k); //event handler
      void handleReleaseEvent(QKeyEvent* k);
      void handleMouseDoubleClickEvent(QMouseEvent *event);

      //Get methods
      int getwinner();
      QVector<int> get_team();


public slots:
      //Neccessary Methods for water animation
      void add_water_to_scene(){
          water_sprite->setPixmap(QPixmap::fromImage(*worker->getMap()));
          water_sprite->setPos(0, this->ground->getHeight() - worker->water_height);
          scene->addItem(water_sprite);
      }
      void refresh_display(){
          water_sprite->setPixmap(QPixmap::fromImage(*worker->getMap()));
          water_sprite->setPos(0, this->ground->getHeight() - worker->water_height);
          QTimer::singleShot(10, this, SLOT(emit_refreshed()));
      }
      void emit_refreshed(){
          emit refreshed();
      }



signals:
      void refreshed();
};
#endif // GAME_H
