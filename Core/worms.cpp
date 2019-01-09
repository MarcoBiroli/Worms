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
    this->label = new QGraphicsSimpleTextItem(this->sprite);
    QString msg = personal_name;
    msg.append(QString::number(this->team_number));
    msg.append("\n");
    msg.append("Health: ");
    msg.append(QString::number(this->health));
    this->label->setPos(0, -25);
    this->label->setText(msg);
}

Worm::~Worm() {
    //delete []ammo; // why do we need to delete?
    delete label;
    //delete this->sprite;
}

bool Worm::isAlive() const{
  return this->health > 0;
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
} 

void Worm::changeHealth(int dmg) {
    this->health -= dmg;
    if(!this->isAlive()){
        this->set_map(QImage("://Images/rigidbodies/grave_collider.png").scaled(25,25));
        this->sprite->setPixmap(QPixmap::fromImage(QImage("://Images/rigidbodies/grave.png").scaled(25,25)));
    }
    QString msg = this->personal_name;
    msg.append(QString::number(this->team_number));
    msg.append("\n");
    msg.append("Health: ");
    msg.append(QString::number(this->health));
    this->label->setText(msg);
}


Projectile* Worm::fireWeapon(double power, QVector<Projectile*> &weapons) {
    Projectile* current_projectile = weapons[current_weapon]->clone(); //currently shot projectile is just a clone of a previously initialized one.
    // We sets its initial parameters:
    current_projectile->set_inital_position(this->x, this->y-25); //might need to offset initial position to avoid worm shooting himself
    double x_force =  power*cos(weapon_angle*(M_PI/180))/update_time;
    double y_force = -power*sin(weapon_angle*(M_PI/180))/update_time;
    if (this->get_direction()) {
        current_projectile->addForce(QPair<double, double>(x_force, y_force)); //apply force generate by shot
    }
    else{
        current_projectile->addForce(QPair<double, double>(-x_force, y_force)); //apply force generate by shot
    }
    return current_projectile;
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

bool Worm::isWorm(){
    return true;
}

void Worm::addAmmo(int weaponID, int amountAmmo){
    if (weaponID == 0){
        this->health += amountAmmo;
    }
    else {
        this->ammo[weaponID] += amountAmmo;
    }
}

  
