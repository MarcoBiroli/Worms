#include <iostream>
#include <string>
using namespace std;

#include "Projectile.h"

#define update_time 10

Projectile::Projectile() : RigidBody ()
{

}

Projectile::Projectile(bool is_bouncy, double delay, double r, double explosion_r, double damage, double m, std::string weapon_name, double x, double y): RigidBody(m, x, y) {
    this->is_bouncy = is_bouncy;
    this->delay = delay;
    this->radius = r;
    this->explosion_radius = explosion_r;
    this->damage = damage;
    this->mass = m;
    this->weapon_name = weapon_name;
}

void Projectile::print() {
    cout << "This projectile was shot from the weapon " << weapon_name << " of specs: " << endl; 
    cout << "   is_bouncy: " << is_bouncy << endl;
    cout << "   delay: " << delay << endl;
    cout << "   radius: " << radius << endl;
    cout << "   explosion_radius: " << explosion_radius << endl;
    cout << "   damage: " << damage << endl;
    cout << "   mass: " << mass << endl << endl;
}

void Projectile::set_inital_position(double x, double y) {
    this->x = x;
    this->y = y;
}

void Projectile::explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels) {
    ground.circ_delete(this->x, this->y, explosion_radius);
    for (int i=0; i<worms.size(); i++) {
        Worm* worm = worms[i];
        double dist = this->distance(*worm);
        if (dist <= explosion_radius) {
            int dmg_dealt = damage - (damage/explosion_radius)*dist;
            worm->changeHealth(dmg_dealt);
            //run explosion animation
            QPair<double, double> vect_dist =  QPair<double, double> (worm->getX() - this->x, worm->getY() - this->y);
            double Fx = (vect_dist.first/dist)*dmg_dealt/update_time;
            double Fy = (vect_dist.second/dist)*dmg_dealt/update_time;
            //Force applied depends on the damage dealt and the distance to the explosion
            QPair<double, double> explosion_force = QPair<double, double> (Fx, Fy);
            worm->addForce(explosion_force);
        }
    }
    for (int j=0; j<barrels.size(); j++) {
        Barrel* barrel = barrels[j];
        double dist = this->distance(*barrel);
        if (dist <= explosion_radius) {
            barrel->explode();
        }

    }
    //destroy projectile
    engine.delete_rigidbody(this->getId());
    projectiles.removeOne(this);
}


Projectile* Projectile::clone() {
    return new Projectile(*this);
} 

