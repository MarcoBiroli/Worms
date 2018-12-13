#include "Game.h"
#include <QPixmap>

Game::Game(int nb_worms, double max_turn_time, int nb_teams, int ground_size_x, int ground_size_y){
    physics_engine = PhysicsEngine();
    ground = Ground(ground_size_x, ground_size_y);

    this->nb_teams = nb_teams;
    this->max_turn_time = max_turn_time;
    paused = false;


    for(int team=0; team<nb_teams; team++){
        for(int i=0; i<nb_worms; i++){
            Worm* newWorm = new Worm(team, "Roger", 100, 50, 32*i, team*32);//positions are arbitrary
            newWorm->setbounciness(0);
            physics_engine.add_RigidBody(newWorm);
            worms.append(newWorm);
        }
        worms_playing.append(0);
    }

    turn_timer=0;
}

bool Game::gameIteration(QKeyEvent *k, double dt){
    if(paused){return false;}
    update(dt);

    if(turn_timer > max_turn_time){ //if shoot -> turn_timer = max_turn_time-5000, if take dmg
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

void Game::handleEvents(QKeyEvent *k){}
//http://doc.qt.io/archives/qt-4.8/qt.html#Key-enum


void Game::update(double dt){
    physics_engine.update(dt);
    turn_timer += dt;
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

void Game::add_to_scene(QGraphicsScene &scene, int class_id, RigidBody new_rigid_body)
{
    QImage initial_image(image_path.value(class_id).value("right"));
    QGraphicsPixmapItem *new_pixmap_body = new QGraphicsPixmapItem(QPixmap::fromImage(initial_image));
    scene.addItem(new_pixmap_body);
    new_pixmap_body->setPos(new_rigid_body.getX(), new_rigid_body.getY());
    pixmap_items.append(new_pixmap_body);
}






