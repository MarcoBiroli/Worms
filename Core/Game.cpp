#include "Game.h"
#include <QPixmap>

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

bool Game::gameIteration(QKeyEvent *k, double dt){
    if(paused){return false;}
    physics_update(dt);

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

/*
void Game::handleEvents(QKeyEvent *k){
    // Find out how to call a certain worm.
    worms[worms_playing[team_playing]]


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
*/

void Game::physics_update(double dt){
    physics_engine.update(dt);
    turn_timer += dt;
}

/*
void Game::graphics_update() {
    //update all worm pixmaps
    QVector<QPair<Worm*, QGraphicsPixmapItem*>>::iterator worm = this->worms.begin();
    for(worm; worm != this->worms.end(); worm++)
    {
        Worm* worm_body = worm->first;
        QGraphicsPixmapItem* worm_pixmap = worm->second;
        if(worm_body->getvx() < 0){
            QImage worm_right(pixmap_images.value(class_worm_id).value("right"));
            worm_pixmap->setPixmap(QPixmap::fromImage(worm_right));
        }
        else{
            QImage worm_left(pixmap_images.value(class_worm_id).value("left"));
            worm_pixmap->setPixmap(QPixmap::fromImage(worm_left));
        }
        worm_pixmap->setPos(worm_body->getX(), worm_body->getY());
    }

    //update projectile
    QVector<QPair<Projectile*, QGraphicsPixmapItem*>>::iterator projectile = this->projectiles.begin();
    for(projectile; projectile != this->projectiles.end(); worm++)
    {
        Projectile* projectile_body = projectile->first;
        QGraphicsPixmapItem* projectile_pixmap = projectile->second;
        if(projectile_body->getvx() < 0){
            int weapon_id = projectile_body->get_id();
            QImage projectile_right(pixmap_images.value(weapon_id).value("right"));
            projectile_pixmap->setPixmap(QPixmap::fromImage(projectile_right));
        }
        else{
            int weapon_id = projectile_body->get_id();
            QImage projectile_left(pixmap_images.value(weapon_id).value("left"));
            projectile_pixmap->setPixmap(QPixmap::fromImage(projectile_left));
        }
        projectile_pixmap->setPos(projectile_body->getX(), projectile_body->getY());
    }
}
*/

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
    QImage initial_image(pixmap_images.value(class_id).value("right"));
    QGraphicsPixmapItem *new_pixmap_body = new QGraphicsPixmapItem(QPixmap::fromImage(initial_image));
    scene.addItem(new_pixmap_body);
    new_pixmap_body->setPos(new_rigid_body.getX(), new_rigid_body.getY());
    pixmap_items.append(new_pixmap_body);
}






