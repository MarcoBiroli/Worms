#include "Game.h"
#include <QPixmap>
#include <QSound>
#include <QMediaPlayer>
#include "../GUI/music.h"

//Initialize all weapons
void Game::weapon_list()
{
    //Bazooka weapon_id = 0
    QPixmap img = QPixmap::fromImage(QImage("://Images/bazooka_projectile.png").scaled(20,20));
    Projectile* bazooka = new Projectile("Bazooka", 0, 20, 0, false, 0, 100, 100, 5, 0, 0, img);
    bazooka->set_map(QImage("://Images/collider_bazooka_projectile.png").scaled(20,20));
    weapons.append(bazooka);
    //Grenade weapon id = 1
    QPixmap img1 = QPixmap::fromImage(QImage(":/Images/Grenade.png").scaled(20,20));
    Projectile* grenade = new Projectile("Grenade", 1, 50, 0.6, true, 3000, 100, 100, 5, 0, 0, img1);
    grenade->set_map(QImage("://Images/grenade_collider.png").scaled(20,20));
    weapons.append(grenade);

    /*
    Projectile shot = Projectile("Shot", 1, 1000, 0.1, false, 0, 1, 35, 0.001, 0, 0, pixmap_images );
    shot.set_map(QImage("").scaled(2,2));
    weapons.append(shot);

    Projectile dynamite = Projectile("Dynamite", 7, 7000, 0.1, true, 3000, 120, 70, 5, 0, 0, pixmap_images[7]["left"]);
    dynamite.set_map(QImage("://Images/Clipart_weapon_7_left.png").scaled(20,20));
    weapons.append(dynamite);

    Projectile rocket = Projectile("Rocket", 13, 3000, 0, false, 0, 60, 50, 1, 0, 0, pixmap_images[13]["left"]);
    rocket.set_map(QImage("://Images/Clipart_weapon_13_left.png").scaled(20,20));
    weapons.append(rocket);
    */
}

Game::Game(QGraphicsScene* iscene, QGraphicsView* iview, int nb_worms, double max_turn_time, int nb_teams, int ground_size_x, int ground_size_y){
    //QImage bw_ground("://Images/bw_ground_map_(3).jpg");
    scene = iscene;
    view = iview;
    physics_engine = new PhysicsEngine();
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/background2.jpg").scaled(ground_size_x,ground_size_y)));
    scene -> addItem(background);
    //ground = new Ground(bw_ground);

    //backgroundmusic("qrc:/Music/ES_Sophisticated Gentlemen 2 - Magnus Ringblom.wav");

    scene = iscene;
    ground = new Ground(ground_size_x, ground_size_y);
    //ground->randomize();
    scene->addItem(ground->getPixmap());
    physics_engine->add_Collider(ground);
    view->centerOn(ground->getPixmap());
    this->weapon_list();
    this->menu = new weapon_menu();
    QGraphicsProxyWidget *item = scene->addWidget(menu);
    item->setPos(0,0);
    item->setZValue(100);
    item->hide();

    /*this->menu->setFlag(QGraphicsItem::ItemIsSelectable);
    this->menu->hide();
    scene->addItem(menu);*/

    this->nb_teams = nb_teams;
    this->max_turn_time = max_turn_time;
    paused = false;

    for(int team=0; team<nb_teams; team++){
        worms_playing.append(team*nb_worms);
        for(int i=0; i<nb_worms; i++){
            Worm* newWorm = new Worm(team, "Roger", 0, 100, 50, ground_size_x/2 + 500*team, 100, pixmap_images[-1]["right"]);//positions are arbitrary
            physics_engine->add_RigidBody(newWorm);
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

Game::~Game()
{
    //qDeleteAll(pixmap_items);
    delete ground;
    qDeleteAll(projectiles);
    qDeleteAll(barrels);
}




bool Game::gameIteration(double dt){
    if(paused){return false;}
    physics_update(dt); //updates the turn timer as well as the physics engine

    if(turn_timer > max_turn_time){ //if shoot -> turn_timer = max_turn_time-5000, if take dmg ->  turn_timer = max_turn_time
        nextWorm();
        turn_timer = 0;
    }

    for (int i=0; i<projectiles.size(); i++) {
        if(projectiles[i]->change_delay(dt) || projectiles[i]->should_explode){
            projectiles[i]->explode(*ground, *physics_engine, projectiles, worms, barrels);
            physics_engine->delete_rigidbody(projectiles[i]->getId());
            delete projectiles[i];
            projectiles.remove(i);
            nextWorm();
            turn_timer = 0;
        }
    }

    return isFinished();
}

void Game::nextWorm(){
    team_playing = (team_playing +1)%nb_teams;
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

    //QGraphicsPixmapItem* pause_image = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/circled-pause.png").scaled(500,500)));

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
            active_worm->sprite->setPixmap(pixmap_images[-1]["left"]);
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
                  active_worm->sprite->setPixmap(pixmap_images[-1]["left"]);
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
                 active_worm->sprite->setPixmap(pixmap_images[-1]["right"]);
                 active_worm->change_direction(true);
        }

        if (k->key()== 0x01000012){ //left arrow == change facing to left
            if(active_worm->getstable()){
            active_worm->change_direction(false);
            active_worm->sprite->setPixmap(pixmap_images[-1]["left"]);
            }
        }

        if (k->key()== 0x01000014){ //right arrow === change facing to right
            if(active_worm->getstable()){
            active_worm->change_direction(true);
            active_worm->sprite->setPixmap(pixmap_images[-1]["right"]);
            }
        }


        if(k->key() == Qt::Key_D){ //key == D move right
            vx = M2[0]*ve + M2[1]*vu;
            vy = M2[2]*ve + M2[3]*vu;
            active_worm->setvx(vx);
            active_worm->setvy(vy);
            active_worm->set_direction();
            active_worm->sprite->setPixmap(pixmap_images[-1]["right"]);
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
            Projectile* current_projectile(active_worm->fireWeapon(power, weapons));
            physics_engine->add_RigidBody(current_projectile);
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
        physics_engine->update(dt);
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
    int seen_team = -1;
    for(int i=0; i < this->worms.length(); i++){
        if(worms[i]->getTeam() != seen_team && worms[i]->isAlive()){
            if(seen_team == -1){
                seen_team = worms[i]->getTeam();
            }
            else{
                return false;
            }
        }
    }
    return true;
}

void Game::add_to_scene(int class_id, RigidBody new_rigid_body)
{
    QPixmap initial_image(pixmap_images[class_id]["right"]);
    QGraphicsPixmapItem *new_pixmap_body = new QGraphicsPixmapItem(initial_image);
    scene->addItem(new_pixmap_body);
    new_pixmap_body->setPos(new_rigid_body.getX(), new_rigid_body.getY());
    pixmap_items.append(new_pixmap_body);
}




