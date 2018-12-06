#include "game.h"

Game::Game(int nb_worms, double max_turn_time, int nb_teams){
    physics_engine = PhysicsEngine();

    this->nb_teams = nb_teams;
    this->max_turn_time = max_turn_time;
    paused = false;


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
    if(paused){return false;}
    update(dt);

    if(turn_timer > max_turn_time){
        team_playing = (team_playing +1)%nb_teams;

        while (worms_playing[team_playing] == -1){ // -1 represents the team is dead
            team_playing = (team_playing +1)%nb_teams;
            //danger if all teams dead infinite loop but should not happen as only called is isFinished false
        }

        nextWorm();
        turn_timer = 0;
    }

    return isFinished();
}

void Game::nextWorm(){
    if(worms_playing[team_playing] == worms.length()-1){worms_playing[team_playing] = 0;}
    else{worms_playing[team_playing] +=1;}

    int count = 0; //counts all worms checked to check if not all dead in team
    while(worms[worms_playing[team_playing]]->getTeam() != team_playing || !(worms[worms_playing[team_playing]]->isAlive()) || count != worms.length()){
        if(worms_playing[team_playing] == worms.length()-1){worms_playing[team_playing] = 0;}
        else{worms_playing[team_playing] +=1;}

        count +=1;
    }

    if(count == worms.length()){ //if all in such team dead try next
        worms_playing[team_playing] = -1;

        team_playing = (team_playing +1)%nb_teams;
        nextWorm(); //careful with infinite loop
    }
}

void Game::handleEvents(QKeyEvent *k){
    // Find out how to call a certain worm.


    // MOVE TO THE RIGHT
 {
     if(k->key() == 0x44){           //If the input key is the right arrow which has code 0x01000014, then give force to the right to the rigid body.
       this->active_worm->addForce(QPair<double, double>(500, 0));
       this->active_worm->setstable(false);
       if(k->isAutoRepeat() == true && k->key() == 0x44){      // If the user stays on the right arrow, repeatedly give 5 speed to the right.
         this->active_worm->addForce(QPair<double, double>(500, 0));                                             // The way int QKeyEvent::key() const and bool QKeyEvent::isAutoRepeat() const work are explained in the text under.
         }
     }

     // MOVE TO THE LEFT
     if (k->key() == 0x41){ // To move to the left just take out 5 velocity.
       qDebug() << "debug left";
       this-> ->addForce(QPair<double, double>(-500, 0));
       this->active_worm->setstable(false);
       }
       if(k->isAutoRepeat() == true && k->key() == 0x41){
         this->active_worm->addForce(QPair<double, double>(-500, 0));
       }
     // JUMP
     int jump_counter = 0; // Make sure that no more than 2 jumps are made.
     if (k->key() == 0x57){ // To move jump give a negative force to the y-axis
             if (jump_counter <= 2){ // If the player did not hit more than twice the jump button
                 jump_counter += 1;
                 this->active_worm->addForce(QPair<double, double>(0, -1000));
                 this->active_worm->setstable(false);
                 }

       }






     // QUIT
     if (k->key() == 0x50) { //press key p
       this->has_quitted = true;        //exit while loop
     }
 }



}

void Game::update(double dt){
    physics_engine.update(dt);
    turn_timer +=dt;
}

bool Game::isFinished(){
    int teams_alive = 0;
    for(int i=0; i <worms.length(); i++){
        if(worms_playing[i] != -1){
            teams_alive +=1;
        }
    }
    if(teams_alive < 2){return true;}
    return false;
}
