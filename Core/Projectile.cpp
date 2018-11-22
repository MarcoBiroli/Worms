#include <iostream>
#include <string>
using namespace std;

#include "Projectile.hpp"

Projectile::Projectile(bool is_bouncy, int delay, double radius, double explosion_radius, int damage, double mass, std::string weapon_name) {
    this->is_bouncy = is_bouncy;
    this->delay = delay;
    this->radius = radius;
    this->explosion_radius = explosion_radius;
    this->damage = damage;
    this->mass = mass;
    this->weapon_name = weapon_name;
}

Projectile::print() {
    cout << "This projectile was shot from the weapon " << weapon_name << " of specs: " << endl; 
    cout << "   is_bouncy: " << is_bouncy << endl;
    cout << "   delay: " << delay << endl;
    cout << "   radius: " << radius << endl;
    cout << "   explosion_radius: " << explosion_radius << endl;
    cout << "   damage: " << damage << endl;
    cout << "   mass: " << mass << endl << endl;
}