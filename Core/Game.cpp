#include "Game.h"
#include <QPixmap>
#include <QSound>
#include <QMediaPlayer>
#include "../GUI/music.h"
#include "settings.h"
#include "pause.h"

//Initialize all weapons
void Game::weapon_list()
{
    //Bazooka weapon_id = 0
    QPixmap img = QPixmap::fromImage(QImage("://Images/weapons/Bazooka_projectile_left.png").scaled(20,20));
    Projectile * bazooka = new Projectile("Bazooka", 0, 100, 0, false, 0, 100, 100, 5, 0, 0, img);
    bazooka->set_map(QImage("://Images/weapons/Bazooka_projectile_collider_left.png").scaled(20,20));
    weapons.append(bazooka);
    //BlueGrenade weapon id = 1
    QPixmap img1 = QPixmap::fromImage(QImage("://Images/weapons/BlueGrenade_left.png").scaled(20,20));
    Projectile * bluegrenade = new Projectile("BlueGrenade", 1, 90, 0.6, true, 3000, 100, 100, 5, 0, 0, img1);
    bluegrenade->set_map(QImage("://Images/weapons/Grenades_collider_left.png").scaled(20,20));
    weapons.append(bluegrenade);
    //green Grenade weapon id = 2
    QPixmap img2 = QPixmap::fromImage(QImage("://Images/weapons/Grenade_left.png").scaled(20,20));
    Projectile * grenade = new Projectile("Grenade", 1, 1000, 0.6, true, 3000, 100, 100, 5, 0, 0, img2);
    grenade->set_map(QImage("://Images/weapons/Grenades_collider_left.png").scaled(20,20));
    weapons.append(grenade);
    //Dynamite weapon id = 3
    QPixmap img3 = QPixmap::fromImage(QImage("://Images/weapons/Dynamite_left.png").scaled(20,20));
    Projectile * dynamite = new Projectile("Dynamite", 1, 50, 0.6, true, 3000, 100, 100, 5, 0, 0, img3);
    dynamite->set_map(QImage("://Images/weapons/Grenades_collider_left.png").scaled(20,20));
    weapons.append(dynamite);
    //Gun weapon id = 4
    QPixmap img4 = QPixmap::fromImage(QImage("://Images/weapons/Gun_projectile_left.png").scaled(30,30));
    Projectile *gun = new Projectile("Gun", 1, 50, 0, false, 0, 100, 100, 5, 0, 0, img4);
    gun->set_map(QImage("://Images/weapons/Gun_projectile_collider_left.png").scaled(30,30));
    weapons.append(gun);
    //Holy grenade weapon id = 5
    QPixmap img5 = QPixmap::fromImage(QImage("://Images/weapons/Holy_Grenade.png").scaled(30,30));
    Projectile *holy = new Projectile("Holy", 1, 90, 0.6, true, 2000, 100, 100, 5, 0, 0, img5);
    holy->set_map(QImage("://Images/weapons/Grenades_collider_right.png").scaled(30,30));
    weapons.append(holy);
    //Banana weapon id = 5
    QPixmap img6 = QPixmap::fromImage(QImage("://Images/weapons/Banana_right.png").scaled(30,30));
    Projectile *banana = new Projectile("Banana", 1, 90, 0.6, true, 2000, 100, 100, 5, 0, 0, img6);
    banana->set_map(QImage("://Images/weapons/Grenades_collider_right.png").scaled(30,30));
    weapons.append(banana);

}

Game::Game(int number, MainWindow * mainwindow, QGraphicsScene* iscene, CustomView* iview, Settings *settings, int ground_size_x, int ground_size_y){
    scene = iscene;
    view = iview;

    physics_engine = new PhysicsEngine();
    backgroundmusic("qrc:/Music/ES_Sophisticated Gentlemen 2 - Magnus Ringblom.wav");
    scene = iscene;

    thread = new QThread;
    worker = new AnimationThread();
    worker->moveToThread(thread);
    worker->width = ground_size_x;
    worker->height = ground_size_y-600;
    worker->water_height = 500;

    if (number == 1) {
        QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/grounds/morning_mountains.png").scaled(ground_size_x,ground_size_y)));
        scene -> addItem(background);
        ground = new Ground(ground_size_x, ground_size_y, terrain_g, grass_green);
        worker->color = water_blue;
    }
    if (number == 2){
        QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/grounds/sunset_mountains.png").scaled(ground_size_x,ground_size_y)));
        scene -> addItem(background);
        ground = new Ground(ground_size_x, ground_size_y, terrain_brown, grass_green);
        ground->randomize2();
        worker->color = water_sun;
    }
    if (number == 3){
        QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/grounds/volcano.png").scaled(ground_size_x,ground_size_y)));
        scene -> addItem(background);
        ground = new Ground(ground_size_x, ground_size_y, terrain_grey, grass_fire);
        ground->randomize3();
        worker->color = water_fire;
    }

    //this->water = Water (qRgb(17, 62, 228), ground_size_x, 500);
    //water.sprite->setPos(0, ground_size_y-600);

    //ground->water = &this->water;
    //scene->addItem(water.sprite);
    scene->addItem(ground->getPixmap());
    physics_engine->add_Collider(ground);
    view->centerOn(ground->getPixmap());

    QObject::connect(thread, SIGNAL(started()), worker, SLOT(process()));
    QObject::connect(worker, SIGNAL(built_water()), this, SLOT(add_water_to_scene()));
    QObject::connect(worker, SIGNAL(animated()), this, SLOT(refresh_display()));
    QObject::connect(this, SIGNAL(refreshed()), worker, SLOT(process()));
    //QObject::connect(worker, SIGNAL(finished()), thread, SLOT(terminate()));
    //QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    //QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    this->weapon_list();
    this->menu = new weapon_menu();
    this->proxymenu = scene->addWidget(menu);

    proxymenu->setZValue(101);
    proxymenu->hide();


    Pause *pause = new Pause();
    pause->view = this->view;
    pause->MainWindow = mainwindow;
    this->proxypause = scene->addWidget(pause);
    proxypause->setPos(((scene->width()/2)-pause->width()/2),((scene->height()/2)-pause->width()/2));
    proxypause->setZValue(200);
    proxypause->hide();
    paused = false;

    this->nb_teams = settings->numberOfTeams;
    this->max_turn_time = settings->timeprturn * 1000;
    double nb_worms = settings->wormperteam;


    for(int team=0; team<nb_teams; team++){
        worms_playing.append(team*nb_worms);
        for(int i=0; i<nb_worms; i++){
            int j = 0;
            for( ; j < ground_size_y; j++){
                qInfo() << ground->get_color(ground_size_x/2 + 500*team, j);
                if(ground->get_color(ground_size_x/2 + 500*team, j) != Qt::white){
                    break;
                }
            }
            qDebug() << j;
            Worm* newWorm = new Worm(team, "Roger", 0, 100, 50, ground_size_x/2 + 500*team, j-50, worm_image["right"]);//positions are arbitrary
            //newWorm->set_map(QImage("://Images/rigidbodies/Worm_collider.png").scaled(32,32));
            physics_engine->add_RigidBody(newWorm);
            worms.append(newWorm);
            newWorm->weaponSelect(0);
            scene->addItem(newWorm->sprite);
            scene->addItem(newWorm->weapon_image);
            newWorm->addAmmo(0,settings->amobazooka);
            newWorm->addAmmo(1,settings->ammoclusterbomb);
            newWorm->addAmmo(2, settings->amogrenade);
            //qDebug() << settings->amogrenade;
            newWorm->addAmmo(3,settings->ammodynamite);
            newWorm->addAmmo(4,settings->amopistol);
            newWorm->addAmmo(5,settings->ammoholy);
            newWorm->addAmmo(6,settings->amobanana);

        }

        if(team != 0){
            worms_playing[team] -=1;
        }
    }

    //scene->addItem(new SpriteSheet(new QPixmap("://Images/Sprite_Walking.png")));
    number_of_turns = 0;
    team_playing=0;
    turn_timer=0;
    has_shot = false;
    next_turn = false;
}

Game::~Game()
{
    //qDeleteAll(pixmap_items);
    delete ground;
    qDeleteAll(projectiles);
    qDeleteAll(barrels);
    //what about worms:
    // qDelete(worms);
}

bool Game::gameIteration(double dt){
    if(paused){
        proxypause->show();
        return false;}
    physics_update(dt); //updates the turn timer as well as the physics engine
    worker->update(dt);
    if(!worms[worms_playing[team_playing]]->isAlive()){
        turn_timer = max_turn_time + 1;
    }
    for(int i = 0; i < worms.length(); i++){
        //worms[i]->fall_damage();
        worms[i]->update_weapon();
        if(worms[i]->getY() > ground->getHeight() - worker->water_height + worker->getWaveSize()/2){
            worms[i]->changeHealth(1000);
            worms[i]->sprite->hide();
            physics_engine->delete_rigidbody(worms[i]->getId());
        }
    }
    if(turn_timer > max_turn_time){ //if shoot -> turn_timer = max_turn_time-5000, if take dmg ->  turn_timer = max_turn_time
        number_of_turns +=1;
        nextWorm();
        turn_timer = 0;
        has_shot = false;
        next_turn = false;


        Crate* newCrate = new Crate(800,  2500, 100, -1, 50,  crate_image);//positions are arbitrary and should depend on size of window

        physics_engine->add_RigidBody(newCrate);
        crates.append(newCrate);
        scene->addItem(newCrate->sprite);
    }

    for (int i=0; i<projectiles.size(); i++) {
        if(projectiles[i]->change_delay(dt) || projectiles[i]->should_explode){
            projectiles[i]->explode(*ground, *physics_engine, projectiles, worms, barrels);
            physics_engine->delete_rigidbody(projectiles[i]->getId());
            delete projectiles[i];
            projectiles.remove(i);

            //QGraphicsPixmapItem* explosion_image = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/weapons/Explosion.png").scaled(32,32)));
            //explosion_image->setX(projectiles[i]->getX());
            //explosion_image->setY(projectiles[i]->getY());
            //scene->addItem(explosion_image);
        }
    }

    return isFinished();
}

void Game::nextWorm(){
    has_shot = false;
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

    //QGraphicsPixmapItem* pause_image = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("://Images/menu/circled_pause.png").scaled(500,500)));

    if(k->key() == Qt::Key_Escape){ // key = Escape for pausing
       if(not paused){
           this->paused = true;
           this->proxypause->show();
       }
       else {
           this->paused = false;
           this->proxypause->hide();
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

        if(k->key() == Qt::Key_Shift) {//Shift left to show menu
            if(menu->isHidden()){
                menu->active_worm = active_worm;
                menu->show();
            }
            else{
                menu->hide();
            }
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

        if (k-> key() == Qt::Key_Space && !has_shot){//key == Space shoots the projectile
            int power = 200;
            Projectile* current_projectile(active_worm->fireWeapon(power, weapons));
            if (current_projectile != NULL){
                physics_engine->add_RigidBody(current_projectile);
                projectiles.append(current_projectile);
                scene->addItem(current_projectile->sprite);

                this->turn_timer = this->max_turn_time - 5000;
                has_shot = true;
             }
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

void Game::changemenupos(QPoint point){
    proxymenu->setPos(point);
}

void Game::changemenusize(double dx,double dy){
    heightmenu *= dx;
    widthmenu *= dy;
    proxymenu->resize(heightmenu,widthmenu);
    //qInfo() << heightmenu;
    //qInfo() << widthmenu;
    //qInfo() << " ";
}
