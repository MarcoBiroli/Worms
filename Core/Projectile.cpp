#include <iostream>
#include <string>
using namespace std;

#include "Projectile.hpp"

Projectile::Projectile(bool is_bouncy, int delay, double radius, double explosion_radius, int damage, double mass, std::string weapon_name, double x, double y) {
    : RigidBody(mass, x, y) {
    this->is_bouncy = is_bouncy;
    this->delay = delay;
    this->radius = radius;
    this->explosion_radius = explosion_radius;
    this->damage = damage;
    this->mass = mass;
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
/* Uncomment once RigidBody is included
void Projectile::set_inital_position(double x, double y) {
    this->x = x;
    this->y = y;
}
*/

void explode(Ground &ground, QMap &rigidbodies, int* wormsIDs) {
    ground.circ_delete(x, y, explosion_radius);
    for (int i=0; i<wormsIDs.length; i++) {
        Worm worm = rigidbodies[wormsIDs[i]];
        double dist = this->distance(worm)
        if (dist <= explosion_radius) {
            worm.health -= damage - (damage/explosion_radius)*dist;
            //run explosion animation
            QPair<double, double> explosion_force = (1/dist) * (worm.x - this->x, worm.y - this->y);
            worm.addForce(explosion_force);
        }
    }    
}

Projectile* Projectile::clone() {
    return new Projectile(*this);
} 

int main() {
    Projectile gre = weapons[0];
    Projectile* gre_copy = gre.clone();
    gre_copy->print();
}