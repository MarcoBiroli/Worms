#include "game.h"

Game::Game(int nb_worms, double max_turn_time, int nb_teams){
    physics_engine = PhysicsEngine();

    this->nb_teams = nb_teams;
    this->max_turn_time = max_turn_time;
    finished = false;


    for(int team=0; team<nb_teams; team++){
        for(int i=0; i<nb_worms; i++){
            Worm* newWorm = new Worm(team, "Roger", 100, 50, 32*i, team*32);//positions are arbitrary
            physics_engine.add_RigidBody(newWorm);
            worms.append(newWorm);
        }
        worms_playing.append(0);
    }

    turn_timer=0;
}

bool Game::gameLoop(QKeyEvent *k, double dt){
    handleEvents(k);
    update(double dt);

    if(turn_timer > max_turn_time){
        turn_timer = 0;
        team_playing = (team_playing +1)%nb_teams;
    }

    return isFinished();
}

void Game::handleEvents(QKeyEvent *k){

}

void Game::update(double dt){
    physics_engine.update(dt);
    turn_timer +=dt;

}
