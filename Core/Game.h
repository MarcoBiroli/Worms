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

#include "../GUI/ground.h"

#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"

#include "Projectile.h"
#include "worms.h"
#include "Barrel.h"
#include "weapon_menu.h"
#include "crates.h"
#include "settings.h"
#include "mainwindow.h"
#include "../GUI/customview.h"
#include "../GUI/water.h"
#include "QThread"
#include "animationthread.h"
#include "../GUI/spritesheet.h"
#include <QtConcurrent/QtConcurrent>
#include "handtohand.h"
#include <QMouseEvent>


class CustomView;
class Game : public QObject{
    Q_OBJECT
    private:
      double max_turn_time;
      int nb_teams;
      //Water water;
      int number_of_turns;

      double turn_timer;
      bool paused;
      bool has_shot;
      bool next_turn;

      int team_playing;
      QVector<int> worms_playing; //index in vector worms of each team (-1 if the team is dead)
      weapon_menu* menu; //contains all weapons

      //temporary storing of the image of worms until spritesheets work
      QMap<QString, QPixmap> worm_image = {
        {"left", QPixmap::fromImage(QImage("://Images/rigidbodies/Worm_left.png").scaled(42,42))},
        {"right", QPixmap::fromImage(QImage("://Images/rigidbodies/Worm_right.png").scaled(42,42))}
      };

      QPixmap crate_image = QPixmap::fromImage(QImage("://Images/rigidbodies/aid.png").scaled(32,32));
      QPixmap barrel_image = QPixmap::fromImage(QImage("://Images/rigidbodies/barrel.png").scaled(40,40));


      //GRAPHICS
      QMap<QString, QVector<QPixmap>> spritesheets;

      QGraphicsProxyWidget *proxymenu;
      QGraphicsProxyWidget *proxypause;


      QColor water_blue = qRgba(4, 168, 210, 255);
      QColor water_sun = qRgba(12, 116, 223,255);
      QColor terrain_g = qRgba(6, 86, 19, 255);
      QColor grass_green = qRgba(121,178,51,255);
      QColor water_fire =  qRgba(204, 0, 0,255);
      QColor terrain_brown = qRgba(125,65,6, 255);
      QColor grass_fire =  qRgba(204, 0, 0,255);
      QColor terrain_grey = qRgba(25, 25, 25,255);
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
      //Worms and projectiles vectors will contain pointers to the same worms and projectiles pointed in the rigid_bodies vector
      //This is done so that we are able to access Worms and Projectile objects as instances of their respective class.
      //Notbaly necessary for Projectile::explode function.
      //The weapons class stores prebuilt projectiles corresponding to a given weapon. Its Pixmap image is at pixmap_images[weapon_id]
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;
      QVector<Barrel*> barrels;
      QVector<Projectile*> weapons;
      QVector<Crate*> crates;

      double heightmenu = 300;
      double widthmenu = 400;

      //Constructors
      Game(QApplication* a, int number,MainWindow * mainwindow, QGraphicsScene *iscene, CustomView *iview,  Settings *settings, int ground_size_x=5000, int ground_size_y=3000);

      virtual ~Game();

      //Methods
      void weapon_list();

      bool gameIteration(double dt);

      void physics_update(double dt); //general update: time and physics

      void graphics_update(); //update pixmap positions and their respective images (left or right)

      void handleEvents(QKeyEvent *k); //event handler
      void handleReleaseEvent(QKeyEvent* k);
      void handleMouseClickEvent(QMouseEvent *event);

      void nextWorm(); //get next worm alive of the team supposed to play next (-1 if it does not exist)

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left

      void changemenupos(QPoint point);

      void changemenusize(double dx,double dy);

      int getwinner();
      QVector<int> get_team();

      int power = 20;

public slots:
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
