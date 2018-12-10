#ifndef GAME_H
#define GAME_H

#include "QVector"
#include "QMap"
#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <QObject>

#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"

#include "Projectile.h"
#include "worms.h"
#include "Barrel.h"

class Game{
    public:
      Game(int nb_worms, double max_turn_time=90000, int nb_teams=2);//Constructor

      bool gameLoop(QKeyEvent *k, double dt);

      void update(double dt); //general update: time and physics

      void handleEvents(QKeyEvent *k); //event handler

      void nextWorm(); //get next worm alive of the team supposed to play next (-1 if it does not exist)

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left


    private:
      //Worms and projectiles vectors will contain pointers to the same worms and projectiles pointed in the rigid_bodies vector
      //This is done so that we are able to access Worms and Projectile objects as instances of their respective class. Notbaly necessary for Projectile::explode function.
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;
      QVector<Barrel*> barrels;

      //Stores prebuilt projectiles corresponding to a given weapon. Copy, set position and force when shooting.
      QList<Projectile> weapons = {Projectile(true, 5, 5, 50, 60, 10, "Grenade", 0, 0), Projectile(false, -1, 0.1, 5, 30, 0.001, "Shot", 0, 0)};

      //store ground, map size (see with GUI team)
      PhysicsEngine physics_engine;
      QVector<int> worms_ids;

      double max_turn_time;
      int nb_teams;

      double turn_timer;
      bool paused;

      int team_playing;
      QVector<int> worms_playing; //index in vector worms of each team (-1 if the team is dead)
};
#endif // GAME_H
