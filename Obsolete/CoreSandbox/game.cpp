#include "game.h"

Game::Game(int nb_worms, double max_turn_time){
    physics_engine = PhysicsEngine();

    this->max_turn_time = max_turn_time;
    finished = false;


    for(int team=1; team<2; team++){
        worms.append
        for(int i=0; i<nb_worms; i++){
            Worm* newWorm = new Worm(team, "Roger", 100, 50, 32*i, team*32);//positions are arbitrary
            physics_engine.add_RigidBody(newWorm);
            worms.();
        }
    }

    worm_playing=0;
    turn_timer=0;
}

void Game::update(double dt){
    physics_engine.update(dt);
    turn_timer +=dt;

    if(turn_timer > max_turn_time){
        turn_timer = 0;
    }
}
