#include "../Physics/RigidBody.h"
#include "Projectile.h"
#include "worms.h"

#include <QVector>


class Game{
    public:
      Game();

      void update(); //general update: deal with physics 


      void updateRigidBodies(); //iterates over the array of rigid bodies to make them move if needed. Should be called eah game loop

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left


    private:
      QVector<RigidBody*> rigid_bodies; //Includes worms, projectiles... Rigid bodies such as projectiles may be created in methods of worms and will thus be created in the heap to be stored.
      //dynamic array as we don't know before Game initialisation the number of worms. Worms should also still be in the rigid_bodies array, however having them here allows to directly locate
      //them and iterate over them for the game.

      //Worms and projectiles vectors will contain pointers to the same worms and projectiles pointed in the rigid_bodies vector
      //This is done so that we are able to access Worms and Projectile objects as instances of their respective class. Notbaly necessary for Projectile::explode function.
      QVector<Worm*> worms;
      QVector<Projectile*> projectiles;
      //store ground, map size (see with GUI team)
};
