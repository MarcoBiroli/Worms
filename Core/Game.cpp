#include "Game.h"
#include <QPixmap>
#include <QSound>
#include <QMediaPlayer>
#include "../GUI/music.h"

//Initialize all weapons
void Game::weapon_list()
{
    //Bazooka weapon_id = 0
    QPixmap img = QPixmap::fromImage(QImage("://Images/weapons/Bazooka_projectile_left.png").scaled(20,20));
    Projectile bazooka = Projectile("Bazooka", 0, 20, 0, false, 0, 100, 100, 5, 0, 0, img);
    bazooka.set_map(QImage("://Images/weapons/Bazooka_projectile_collider_left.png").scaled(20,20));
    weapons.append(bazooka);
    //BlueGrenade weapon id = 1
    QPixmap img1 = QPixmap::fromImage(QImage("://Images/weapons/BlueGrenade_left.png").scaled(20,20));
    Projectile bluegrenade = Projectile("BlueGrenade", 1, 50, 0.6, true, 3000, 100, 100, 5, 0, 0, img1);
    bluegrenade.set_map(QImage("://Images/weapons/Grenades_collider_left.png").scaled(20,20));
    weapons.append(bluegrenade);
    //green Grenade weapon id = 2
    QPixmap img2 = QPixmap::fromImage(QImage("://Images/weapons/Grenade_left.png").scaled(20,20));
    Projectile grenade = Projectile("Grenade", 1, 50, 0.6, true, 3000, 100, 100, 5, 0, 0, img2);
    grenade.set_map(QImage("://Images/weapons/Grenades_collider_left.png").scaled(20,20));
    weapons.append(grenade);
    //Dynamite weapon id = 3
    QPixmap img3 = QPixmap::fromImage(QImage("://Images/weapons/Dynamite_left.png").scaled(20,20));
    Projectile dynamite = Projectile("Dynamite", 1, 50, 0.6, true, 3000, 100, 100, 5, 0, 0, img3);
    dynamite.set_map(QImage("://Images/weapons/Dynamite_collider_left.png").scaled(20,20));
    weapons.append(dynamite);
    //Gun weapon id = 4
    QPixmap img4 = QPixmap::fromImage(QImage("://Images/weapons/Bazooka_projectile_left.png").scaled(20,20));
    Projectile gun = Projectile("Gun", 1, 50, 0, false, 0, 100, 100, 5, 0, 0, img4);
    gun.set_map(QImage("://Images/weapons/Bazooka_projectile_collider_left.png").scaled(20,20));
    weapons.append(gun);
}

Game::Game(QGraphicsScene* iscene, QGraphicsView* iview, int nb_worms, double max_turn_time, int nb_teams, int ground_size_x, int ground_size_y){
    scene = iscene;
    view = iview;
    physics_engine = PhysicsEngine();
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/grounds/sunset_mountains.png").scaled(ground_size_x,ground_size_y)));
    scene -> addItem(background);

    backgroundmusic("qrc:/Music/ES_Sophisticated Gentlemen 2 - Magnus Ringblom.wav");

    scene = iscene;
    ground = new Ground(ground_size_x, ground_size_y);
    //ground->randomize();
    scene->addItem(ground->getPixmap());
    physics_engine.add_Collider(ground);
    view->centerOn(ground->getPixmap());

    this->weapon_list();
    this->menu = new weapon_menu();
    QGraphicsProxyWidget *item = scene->addWidget(menu);
    item->setPos(0,0);
    item->setZValue(100);
    item->hide();

    this->nb_teams = nb_teams;
    this->max_turn_time = max_turn_time;
    paused = false;

    for(int team=0; team<nb_teams; team++){
        worms_playing.append(team*nb_worms);
        for(int i=0; i<nb_worms; i++){
            Worm* newWorm = new Worm(team, "Roger", 0, 100, 50, 1000 + 500*team, 100, worm_image["right"]);//positions are arbitrary
            newWorm->set_map(QImage("://Images/rigidbodies/Worm_collider.png").scaled(32,32));
            physics_engine.add_RigidBody(newWorm);
            worms.append(newWorm);
            scene->addItem(newWorm->sprite);
        }

        if(team != 0){
            worms_playing[team] -=1;
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
        if(projectiles[i]->change_delay(dt) || projectiles[i]->should_explode){
            projectiles[i]->explode(*ground, physics_engine, projectiles, worms, barrels);
            nextWorm();
        }
    }

    return isFinished();
}

void Game::nextWorm(){
    if(worms_playing[team_playing] == worms.length()-1){worms_playing[team_playing] = 0;}
    else{worms_playing[team_playing] +=1;}

    int count = 0; //counts all worms checked to check if not all dead in team
    while((worms[worms_playing[team_playing]]->getTeam() != team_playing || !(worms[worms_playing[team_playing]]->isAlive())) && count < worms.length()){ //condition and break if count too big
        if(worms_playing[team_playing] == worms.length()-1){worms_playing[team_playing] = 0;}
        else{worms_playing[team_playing] +=1;}

        count +=1;
    }

    if(count == worms.length()){ //if all in such team dead try next
        worms_playing[team_playing] = -1;

        team_playing = (team_playing +1)%nb_teams;
        if(this->isFinished()){
            return;
        }
        nextWorm(); //careful with infinite loop
    }
    menu->active_worm = worms[worms_playing[team_playing]];
}

void Game::handleEvents(QKeyEvent *k){
    Worm* active_worm = worms[worms_playing[team_playing]];

    if(!active_worm->is_grounded.first){return;}

    double speed = 50;
    double theta = qAtan2(-active_worm->is_grounded.second.first, active_worm->is_grounded.second.second);
    double M[4] = {qCos(theta), qSin(theta), -qSin(theta), qCos(theta)}; //rotational matrix of angle theta.
    double ve = (M[0]*speed); // component of the velocity parallel to the tangent line at the collision point.
    double vu = 0; // component of the velocity perpendicular to the tangent line at the collision point.
    double M2[4] = {qCos(theta), -qSin(theta), qSin(theta), qCos(theta)};
    double vx, vy;

    //QGraphicsPixmapItem* pause_image = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/menu/circled_pause.png").scaled(500,500)));

    if(k->key() == Qt::Key_Escape){ // key = Escape for pausing
       if(not paused){
           this->paused = true;
           //scene->addItem(pause_image);
       }
       else {
           this->paused = false;
           //pause_image->hide();
           //scene->removeItem(pause_image);
       }
    }

    if(not paused){
        if(k->key() == Qt::Key_A){ // key == A move left
            ve *= -1;
            vx = M2[0]*ve + M2[1]*vu;
            vy = M2[2]*ve + M2[3]*vu;
            active_worm->setvx(vx);
            active_worm->setvy(vy);
            active_worm->set_direction();
            active_worm->sprite->setPixmap(worm_image["left"]);
            if(k->isAutoRepeat() == true && k->key() == 0x41){
                active_worm->setvx(vx);
                active_worm->setvy(vy);
                active_worm->set_direction();
            }
        }

        if (k->isAutoRepeat() == false && k->key() == Qt::Key_Q){// key == Q jump to the left
            //get_direction == True means you are facing right
                  if (active_worm->get_direction()){ //backflips have greater forces of jumping

                      active_worm->addForce(QPair<double, double> (-1000*active_worm->getm(),-5000*active_worm->getm()));
                      active_worm->setstable(false);
                  }
                  else{ //normal jumping to the left
                      active_worm->addForce(QPair<double, double> (-1000*active_worm->getm(),-2500*active_worm->getm()));
                      active_worm->setstable(false);
                  }
                  active_worm->sprite->setPixmap(worm_image["left"]);
                  active_worm->change_direction(false);
        }

        if (k->isAutoRepeat() == false && k->key()== Qt::Key_E){ // key == E jump to the right
                 if (active_worm->get_direction()){ //normal jumping to the right
                     active_worm->setforce(QPair<double,double>(0,0));
                     active_worm->addForce(QPair<double, double> (1000*active_worm->getm(),-2500*active_worm->getm()));
                     active_worm->setstable(false);
                 }
                 else{ //backflips have greater forces of jumping
                     active_worm->setforce(QPair<double,double>(0,0));
                     active_worm->addForce(QPair<double, double> (1000*active_worm->getm(),-5000*active_worm->getm()));
                     active_worm->setstable(false);
                 }
                 active_worm->sprite->setPixmap(worm_image["right"]);
                 active_worm->change_direction(true);
        }

        if (k->key()== 0x01000012){ //left arrow == change facing to left
            if(active_worm->getstable()){
            active_worm->change_direction(false);
            active_worm->sprite->setPixmap(worm_image["left"]);
            }
        }

        if (k->key()== 0x01000014){ //right arrow === change facing to right
            if(active_worm->getstable()){
            active_worm->change_direction(true);
            active_worm->sprite->setPixmap(worm_image["right"]);
            }
        }


        if(k->key() == Qt::Key_D){ //key == D move right
            vx = M2[0]*ve + M2[1]*vu;
            vy = M2[2]*ve + M2[3]*vu;
            active_worm->setvx(vx);
            active_worm->setvy(vy);
            active_worm->set_direction();
            active_worm->sprite->setPixmap(worm_image["right"]);
            if(k->isAutoRepeat() == true && k->key() == 0x44){
                active_worm->setvx(vx);
                active_worm->setvy(vy);
                active_worm->set_direction();
            }
        }

        if (k->isAutoRepeat() == false && k->key() == Qt::Key_W){ // key == W  jumping
            active_worm->addForce(QPair<double, double>(0, -5000*active_worm->getm()));
            active_worm->setstable(false);
            }

        if(k->key() == Qt::Key_0) {//0 to select weapons
            menu->active_worm = active_worm;
            menu->show();
        }

        //if(menu->isSelected()){// if you have clicked on a weapon then u can increase decrease angle
        if (k-> key() == Qt::Key_I){// key == I increases the angle 0- 90
            if (0<= active_worm->weapon_angle && active_worm->weapon_angle<= 80){
                active_worm->weapon_angle += 10;
            }
        }
        if (k-> key() == Qt::Key_K){// key == K decreases the angle }
            if (10<= active_worm->weapon_angle && active_worm->weapon_angle<=90){
                active_worm->weapon_angle -= 10;
            }
        }

        if (k-> key() == Qt::Key_Space){//key == Space shoots the projectile
            int power = 200;
            Projectile* current_projectile = active_worm->fireWeapon(power, weapons);
            physics_engine.add_RigidBody(current_projectile);
            projectiles.append(current_projectile);
            scene->addItem(current_projectile->sprite);
            this->turn_timer = this->max_turn_time - 5000;
        }
    }
    active_worm->setstable(false);
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
    for(int i=0; i < this->nb_teams; i++){
        if(worms_playing[i] != -1){
            teams_alive +=1;
        }
    }
    if(teams_alive < 2){return true;}
    return false;
}





