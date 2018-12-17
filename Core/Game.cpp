#include "Game.h"
#include <QPixmap>

//Initialize all weapons
void Game::weapon_list()
{
    Projectile grenade = Projectile("Grenade", 0, 5000, 0.6, true, 3000, 100, 60, 5, 0, 0, pixmap_images[0]["left"]);
    grenade.set_map(QImage("://Images/grenade_collider.png").scaled(20,20));
    weapons.append(grenade);
}

Game::Game(QGraphicsScene* iscene, int nb_worms, double max_turn_time, int nb_teams, int ground_size_x, int ground_size_y){
    QImage bw_ground("://Images/bw_ground_map.jpg");
    scene = iscene;
    physics_engine = PhysicsEngine();
    ground = new Ground(ground_size_x, ground_size_y);
    //ground = new Ground(bw_ground);
    scene->addItem(ground->getPixmap());
    physics_engine.add_Collider(ground);

    this->weapon_list();

    this->menu->setFlag(QGraphicsItem::ItemIsSelectable);
    this->menu->hide();
    scene->addItem(menu);

    this->nb_teams = nb_teams;
    this->max_turn_time = max_turn_time;
    paused = false;

    for(int team=0; team<nb_teams; team++){
        worms_playing.append(team*nb_worms);
        for(int i=0; i<nb_worms; i++){
            Worm* newWorm = new Worm(team, "Roger",0 , 100, 50, 100 + 100*i, 100+team*100, pixmap_images[-1]["right"]);//positions are arbitrary
            physics_engine.add_RigidBody(newWorm);
            worms.append(newWorm);
            scene->addItem(newWorm->sprite);
        }
    }

    team_playing=0;

    turn_timer=0;
}



bool Game::gameIteration(double dt){
    if(paused){return false;}
    physics_update(dt); //updates the turn timer as well as the physics engine

    if(turn_timer > max_turn_time){ //if shoot -> turn_timer = max_turn_time-5000, if take dmg ->  turn_timer = max_turn_time
        team_playing = (team_playing+1)%nb_teams;

        while (worms_playing[team_playing] == -1){ // -1 represents the team is dead
            team_playing = (team_playing +1)%nb_teams;
            //danger if all teams dead infinite loop but should not happen as only called is isFinished false
        }

        nextWorm();
        turn_timer = 0;
    }

    for (int i=0; i<projectiles.size(); i++) {
        if(projectiles[i]->change_delay(dt)){
            projectiles[i]->explode(*ground, physics_engine, projectiles, worms, barrels);
        }
    }

    return isFinished();
}

void Game::nextWorm(){
    if(worms_playing[team_playing] == worms.length()-1){worms_playing[team_playing] = 0;}
    else{worms_playing[team_playing] +=1;}

    int count = 0; //counts all worms checked to check if not all dead in team
    while(worms[worms_playing[team_playing]]->getTeam() != team_playing && !(worms[worms_playing[team_playing]]->isAlive()) && count != worms.length()){
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
    Worm* active_worm = worms[worms_playing[team_playing]];

    if(!active_worm->is_grounded.first){return;}

    active_worm->setstable(false);
    double speed = 50;
    double theta = qAtan2(-active_worm->is_grounded.second.first, active_worm->is_grounded.second.second);
    double M[4] = {qCos(theta), qSin(theta), -qSin(theta), qCos(theta)}; //rotational matrix of angle theta.
    double ve = (M[0]*speed); // component of the velocity parallel to the tangent line at the collision point.
    double vu = 0; // component of the velocity perpendicular to the tangent line at the collision point.
    double M2[4] = {qCos(theta), -qSin(theta), qSin(theta), qCos(theta)};
    double vx, vy;

    if(k->key() == 0x41){ // key == A move left
        ve *= -1;
        vx = M2[0]*ve + M2[1]*vu;
        vy = M2[2]*ve + M2[3]*vu;
        active_worm->setvx(vx);
        active_worm->setvy(vy);
        if(k->isAutoRepeat() == true && k->key() == 0x41){
            active_worm->setvx(vx);
            active_worm->setvy(vy);
        }
    }

    if(k->key() == 0x44){ //key == D move right
        vx = M2[0]*ve + M2[1]*vu;
        vy = M2[2]*ve + M2[3]*vu;
        active_worm->setvx(vx);
        active_worm->setvy(vy);
        if(k->isAutoRepeat() == true && k->key() == 0x44){
            active_worm->setvx(vx);
            active_worm->setvy(vy);
        }
    }

    if (k->key() == 0x57){ // key == W  jumping
        active_worm->addForce(QPair<double, double>(0, -5000*active_worm->getm())); //TO DO: decrease the force
        active_worm->setstable(false);
        }

    if(k->key() == Qt::Key_0) {//0 to select weapons
        this->menu->show();
    }

    if(menu->isSelected()){// if you have clicked on a weapon then u can increase decrease angle
        if (k-> key() == 0x49){// key == I increases the angle 0- 90
            if (0<= active_worm->weapon_angle && active_worm->weapon_angle<= 80){
                active_worm->weapon_angle += 10;
            }
        }
        if (k-> key() == 0x4B){// key == K decreases the angle }
            if (10<= active_worm->weapon_angle && active_worm->weapon_angle<=90){
                active_worm->weapon_angle -= 10;
            }
        }

        if (k-> key() == 0x20){//key == Space shoots the projectile
            int power = 200;
            /*if(k->isAutoRepeat() == true && k->key() == 0x20){ //if you press space for a long time the power increases
                power += 10;
            }*/
            Projectile* current_projectile = active_worm->fireWeapon(power, weapons);
            physics_engine.add_RigidBody(current_projectile);
            projectiles.append(current_projectile);
            scene->addItem(current_projectile->sprite);
            this->turn_timer = this->max_turn_time - 5000;
        }
    }
}

//http://doc.qt.io/archives/qt-4.8/qt.html#Key-enum


void Game::physics_update(double dt){
    for (int i = 0; i < 10; i++){
        physics_engine.update(dt);
    }
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
    /*for(int i=0; i <worms.length(); i++){
        if(worms_playing[i] != -1){
            teams_alive +=1;
        }
    }*/
    if(teams_alive < 2){return true;}
    return false;
}

void Game::add_to_scene(int class_id, RigidBody new_rigid_body)
{
    QPixmap initial_image(pixmap_images[class_id]["right"]);
    QGraphicsPixmapItem *new_pixmap_body = new QGraphicsPixmapItem(initial_image);
    scene->addItem(new_pixmap_body);
    new_pixmap_body->setPos(new_rigid_body.getX(), new_rigid_body.getY());
    pixmap_items.append(new_pixmap_body);
}




