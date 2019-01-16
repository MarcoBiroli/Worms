#include "worms.h"
#include "../GUI/music.h"

#define update_time 0.01

Worm::Worm(): RigidBody (), team_number(0), personal_name("")
{

}

Worm::Worm(int team_number, QString personal_name, double bounciness, int health, double mass, double x, double y, QPixmap isprite): RigidBody(mass, x, y), team_number(team_number), personal_name(personal_name) {
    this->health = health;
    this->setbounciness(bounciness);
    this->sprite->setPixmap(isprite);
    this->label = new QGraphicsTextItem(this->sprite);
    QString msg = personal_name;
    msg.append("\n");
    msg.append("Health: ");
    msg.append(QString::number(this->health));
    this->label->setPos(-6*std::max(personal_name.length(), 10)/2, -48);
    this->label->setPlainText(msg);
    this->label->setFont(QFont("Comic Sans MS", 12, QFont::Bold, true));
    if(team_number == 0){
        this->label->setDefaultTextColor(Qt::red);
    }
    else if (team_number == 1){
        this->label->setDefaultTextColor(Qt::blue);
    }
    else if (team_number == 2){
        this->label->setDefaultTextColor(Qt::green);
    }
    else if (team_number == 3){
        this->label->setDefaultTextColor(Qt::yellow);
    }
    this->reticle->setPixmap(QPixmap("://Images/Aim.png").scaled(32,32));
    this->reticle->hide();
}

Worm::~Worm() {
    //delete []ammo; // why do we need to delete?
    delete label;
    //delete this->sprite;
}

bool Worm::isAlive(){
    if(this->health <= 0){
        this->health = 0;
        return false;
    }
    return true;
}

int Worm::getTeam() const{
    return this->team_number;
}

bool Worm::damage_taken(){
    if (this->damagetaken){
        damagetaken=false;
        return true;
    }
    else{
        return false;
    }
}

void Worm::fall_damage(){
    double bckp_V_magnitude= std::sqrt(this->bckp_vx*this->bckp_vx+this->bckp_vy*this->bckp_vy);
    if (this->is_grounded.first){
        this->changeHealth(bckp_V_magnitude/10);
        this->damagetaken=true;
    }
}


void Worm::pickUpWeapon(int weapon_ID, int iammo) {
    this->ammo[weapon_ID] += iammo;
}

void Worm::weaponSelect(int weapon_ID) {
    this->current_weapon = weapon_ID;
    this->update_weapon();
} 

void Worm::changeHealth(int dmg) {
    this->health -= dmg;
    if(!this->isAlive()){
        this->set_map(QImage("://Images/rigidbodies/grave_collider.png").scaled(25,25));
        this->sprite->setPixmap(QPixmap::fromImage(QImage("://Images/rigidbodies/grave.png").scaled(25,25)));
    }
    QString msg = this->personal_name;
    msg.append("\n");
    msg.append("Health: ");
    msg.append(QString::number(this->health));
    this->label->setPlainText(msg);
}


Projectile* Worm::fireWeapon(double power, QVector<Projectile*> &weapons) {
    Projectile* current_projectile = weapons[current_weapon]->clone(); //currently shot projectile is just a clone of a previously initialized one.
    // We sets its initial parameters:
    //current_projectile->set_firing_worm(this);
    current_projectile->firing_worm = this;
    if(ammo[current_weapon] == -1 ||  ammo[current_weapon] != 0){
        ammo[current_weapon] -= 1;
        if (ammo[current_weapon] == -2) {
            ammo[current_weapon] = -1;
        }
        else if (ammo[current_weapon] == -1){
            ammo[current_weapon] = 0;
        }

    if(current_projectile->is_airweapon){
        return NULL;

    }
        //current_projectile->set_inital_position(this->x, this->y-32); //might need to offset initial position to avoid worm shooting himself
        double x_dir = cos(weapon_angle*(M_PI/180));
        double y_dir = -sin(weapon_angle*(M_PI/180));
        double worm_margin = std::max(this->getHeight(), this->getWidth());
        double proj_margin = std::max(current_projectile->getHeight(), current_projectile->getWidth());
        double margin = worm_margin/2 + proj_margin/2 + 5;
        double x_force =  power*x_dir/update_time;
        double y_force = power*y_dir/update_time;
        if (this->get_direction()) {
            current_projectile->addForce(QPair<double, double>(x_force, y_force)); //apply force generate by shot
            current_projectile->set_inital_position(this->x+this->getWidth()/2 - current_projectile->getWidth()/2 + x_dir*margin, this->y+ + this->getHeight()/2 - current_projectile->getHeight()/2 + y_dir*margin);
        }
        else{
            current_projectile->addForce(QPair<double, double>(-x_force, y_force)); //apply force generate by shot
            current_projectile->set_inital_position(this->x+this->getWidth()/2 - current_projectile->getWidth()/2 -x_dir*margin, this->y - current_projectile->getHeight()/2 + this->getHeight()/2 +y_dir*margin);
        }
        return current_projectile;
    }
    else{return NULL;}
}

QVector<Projectile*> Worm::fireAirWeapon(double power, QVector<Projectile *> &weapons)
{
    //double x_dir = cos(weapon_angle*(M_PI/180));
    //double y_dir = -sin(weapon_angle*(M_PI/180));
    //double x_force =  power*x_dir/update_time;
    //double y_force = power*y_dir/update_time;
    //weapon->addForce(QPair<double, double>(x_force, y_force)); //apply force generate by shot
    QVector<Projectile*> airweapon;
    for (int i=0; i< this->amount_airweapon; i++)
    {
        Projectile* weapon = weapons[current_weapon]->clone();
        weapon->set_inital_position(this->target.first-100*i - weapon->getWidth()/2, 0);
        weapon->setvx(100*this->amount_airweapon/(qSqrt(2*this->target.second/9.81)));
        airweapon.append(weapon);
    }
    return airweapon;
}

void Worm::update_weapon(){
    if(!this->isAlive()){
        this->weapon_image->hide();
        return;
    }
    this->weapon_image->setPixmap(QPixmap::fromImage(this->weapons[this->current_weapon].mirrored(this->get_direction(), false)));
    double reticle_dist = 150;
    if(this->get_direction()){
        this->weapon_image->setPos(this->getWidth()+5, this->getHeight()/2 - 11);
        this->reticle->setPos(this->getWidth()/2 + reticle_dist*qCos(weapon_angle*(M_PI/180)) - 16, this->getHeight()/2 - reticle_dist*qSin(weapon_angle*(M_PI/180)) - 16);
    }
    else{
        this->weapon_image->setPos(-16, this->getHeight()/2 - 11);
        this->reticle->setPos(this->getWidth()/2 - reticle_dist*qCos(weapon_angle*(M_PI/180)) - 16, this->getHeight()/2 - reticle_dist*qSin(weapon_angle*(M_PI/180)) - 16);
    }
}

int Worm::get_weapon()
{
    return this->current_weapon;
}

bool Worm::get_direction(){
    return wormdirection;
}

void Worm::set_direction(){
        if (this->vx>0){
            wormdirection=true;
        }
        else{
            if (this->vx<0){
            wormdirection=false;
        }
    }
}

void Worm::change_direction(bool t){
    wormdirection=t;
    }

void Worm::wormDeath() {
    //call animation
}

bool Worm::isWormAlive(){
    return isAlive();
}

void Worm::addAmmo(int weaponID, int amountAmmo){
    if (weaponID == -1){ //careful it is not supposed to be bigger or equal to 0 coz that is for real weapons
        this->changeHealth(-amountAmmo);
    }
    else {
        this->ammo[weaponID] += amountAmmo;
    }
}

  
