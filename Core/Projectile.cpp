#include "Projectile.h"

#define update_time 0.01 //????? WHAT IS THIS ?????

//Constructors
Projectile::Projectile() : RigidBody ()
{

}

Projectile::~Projectile()
{
    //delete this->sprite;
}


Projectile::Projectile(std::string name, int weapon_id, double ipower, double bounciness, bool explosion_by_delay, double delay, double explosion_r, double damage, double mass, double x, double y, QPixmap isprite): RigidBody (mass, x, y){

    this->repulsion_power = ipower;
    this->name = name;
    this->explosion_by_delay= explosion_by_delay;
    this->delay = delay;
    this->explosion_radius = explosion_r;
    this->damage = damage;
    this->weapon_id = weapon_id; //<- TO BE DELETED
    this->setbounciness(bounciness);
    this->sprite->setPixmap(isprite);
}

Projectile::Projectile(const Projectile &other):RigidBody (other.mass, other.x, other.y, other.vx, other.vy, other.ax, other.ay, other.get_map(), other.sprite->pixmap())
{
    this->repulsion_power = other.repulsion_power;
    this->name = other.name;
    this->explosion_by_delay= other.explosion_by_delay;
    this->delay = other.delay;
    this->explosion_radius = other.explosion_radius;
    this->damage = other.damage;
    this->weapon_id = other.weapon_id; //<- TO BE DELETED
    this->setbounciness(other.getbounciness());
    this->sprite->setPixmap(other.sprite->pixmap());
    this->is_airweapon = other.is_airweapon;
}

Projectile* Projectile::clone() {
    return new Projectile(*this);
}

//PRINTING FUNCTION ??? TO DELETE??
void Projectile::print() {
    cout << "This projectile was shot from the weapon " << weapon_id << " of specs: " << endl;
    cout << "   delay: " << delay << endl;
    cout << "   explosion_radius: " << explosion_radius << endl;
    cout << "   damage: " << damage << endl;
    cout << "   mass: " << mass << endl << endl;
}


//On collision, projectile explodes if it should explode on impact. Otherwise no
bool Projectile::on_collision_do(Collider &other)
{
    if(!this->explosion_by_delay) {
        this->should_explode = true;
    };
    return false;
}




// if explosion condition is met (collosion or delay timeout), call this function.
// the function does the following:
// generates damage in explosion_radius, with linear decrease of damage from
//
// destroys all terrain in radius explosion_radius of center of explosion
// trigger explosion of barrels in the explosion radius
// destroy the projectile
void Projectile::explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels) {
    //sets sound effects
    Music explosion;
    explosion.playsound("qrc:/SoundEffect/Explosion+7.mp3");

    //Deletes a circle as big as the explosion radius of the ground
    ground.circ_delete(this->x, this->y, explosion_radius);

    for (int i=0; i<worms.size(); i++) {
        Worm* worm = worms[i];
        //position of explosion to distance explosion_radius of the center of explosion.
        double dist = this->distance(*worm);
        if (dist <= 1.2*explosion_radius) {
            worm->tangent_bouncing = false;
            //calculates and gives damage to the worms inside the explosion radius
            int dmg_dealt = damage - (damage/(1.2*explosion_radius))*dist;
            worms[i]->changeHealth(dmg_dealt);
            //Repulsion force
            QPair<double, double> vect_dist =  QPair<double, double> (worm->getX() - this->x, worm->getY() - this->y);
            double Fx = this->repulsion_power*(vect_dist.first/dist)/update_time;
            double Fy = this->repulsion_power*(vect_dist.second/dist)/update_time;
            //Force applied depends on the damage dealt and the distance to the explosion
            QPair<double, double> explosion_force = QPair<double, double> (Fx, Fy);
            worm->addForce(explosion_force);
            //set sound effects of Hurted worms
            Music sound;
            sound.randomsound();
        }

        //?????? WHAT DOES IT DO????

        /*
        for (int i=0; i<projectiles.size(); i++) {
            Projectile* projectile = projectiles[i];
            double dist = this->distance(*projectile);
            if (dist <= explosion_radius) {
                int dmg_dealt = damage - (damage/explosion_radius)*dist;
                QPair<double, double> vect_dist =  QPair<double, double> (projectile->getX() - this->x, projectile->getY() - this->y);
                double Fx = this->repulsion_power*(vect_dist.first/dist)*dmg_dealt/update_time;
                double Fy = this->repulsion_power*(vect_dist.second/dist)*dmg_dealt/update_time;
                //Force applied depends on the damage dealt and the distance to the explosion
                QPair<double, double> explosion_force = QPair<double, double> (Fx, Fy);
                projectile->addForce(explosion_force);
            }
        }*/
    }

    //??????WHAT DOES IT DO???????
    for (int j=0; j<barrels.size(); j++) {

        Barrel* barrel = barrels[j];
        double dist = this->distance(*barrel);
        if (dist <= explosion_radius) {
            barrel->setExplode(true);
        }

    }
    //Hides the sprite of the projectile as it has "exploded"
    //this->sprite->setPixmap(QPixmap::fromImage(QImage("://Images/menu/worms2.png").scaled(20,20)));
    this->sprite->hide();

}

//Get/ Set methods

int Projectile::get_weapon_id() const
{
    return this->weapon_id;
}

void Projectile::set_inital_position(double x, double y) {
    this->x = x;
    this->y = y;
}

//reduce time left before explosion of delay projectiles. If no time left, return true.
bool Projectile::change_delay(double dt){
    if(explosion_by_delay){
        delay -= dt;
    }
    if(explosion_by_delay && delay < 0){
        return true;
    }
    return false;
}



