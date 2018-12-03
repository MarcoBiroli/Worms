#include "game.h"

Game::Game(int nb_worms, double max_turn_time){
    physics_engine = PhysicsEngine();

    this->max_turn_time = max_turn_time;
    finished = false;

    for(int i=0; i<nb_worms; i++){
        for(int team=1; team<2; team++){
            Worm* newWorm = new Worm(team, "Roger", 100, 50, 32*i, team*32);//positions are arbitrary
            physics_engine.add_RigidBody(newWorm);
            worms_ids.insert(0, 1, newWorm->getId());
        }
    }

    worm_playing=0;
    turn_timer=0;
}

void Game::update(double dt){
    physics_engine.update(dt);
    turn_timer +=dt;
}
