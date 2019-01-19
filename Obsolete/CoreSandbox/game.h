#ifndef GAME_H
#define GAME_H

#include "QVector"
include "QMap"

#include "RigidBody.h"
#include "PhysicsEngine.h"

#include "Projectile.h"
#include "worms.h"

class Game{
    public:
      Game(int nb_worms, double max_turn_time=90000);

      void update(double dt); //general update: deal with physics

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left


    private:
      PhysicsEngine physics_engine;
      QVector<int> worms_ids;

      double max_turn_time;

      double turn_timer;

      int worm_playing; //index in vector worms
      bool finished; //false

      QVector< QVector<Worm*> > worms;
      QVector<Projectile*> projectiles;
};
#endif // GAME_H
