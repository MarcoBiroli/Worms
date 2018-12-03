#ifndef GAME_H
#define GAME_H

#include "QVector"
#include "QMap"

#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsEngine.h"

#include "Projectile.h"
#include "worms.h"

class Game{
    public:
      Game(int nb_worms, double max_turn_time=90000, unsigned int nb_teams=2);

      void update(double dt); //general update: deal with physics

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left


    private:
      //Worms and projectiles vectors will contain pointers to the same worms and projectiles pointed in the rigid_bodies vector
      //This is done so that we are able to access Worms and Projectile objects as instances of their respective class. Notbaly necessary for Projectile::explode function.
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;

      //Stores prebuilt projectiles corresponding to a given weapon. Copy, set position and force when shooting.
      QList<Projectile> weapons = {Projectile(true, 5, 5, 50, 60, 10, "Grenade", 0, 0), Projectile(false, -1, 0.1, 5, 30, 0.001, "Shot", 0, 0)};

      //store ground, map size (see with GUI team)
      PhysicsEngine physics_engine;
      QVector<int> worms_ids;

      double max_turn_time;

      double turn_timer;

      QVector<int> worms_playing; //index in vector worms of each team
      bool finished; //false
};
#endif // GAME_H
