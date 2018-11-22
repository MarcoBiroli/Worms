#include <iostream>
#include <vector>

#include "RigidBody.hpp"

#include "Projectile.hpp"
#include "worms.hpp"

class Game{
    public:
      void updateRigidBodies(); //iterates over the array of rigid bodies to make them move if needed. Should be called eah game loop

      bool isFinished(); //returns if the game is finished, i.e. if there is only worms of one team left


    private:
      std::vector<*RigidBody> rigid_bodies;
      


};