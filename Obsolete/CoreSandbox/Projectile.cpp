#include "Projectile.h"

Projectile::Projectile(bool is_bouncy, int delay, double radius, double explosion_radius, int damage, double mass, QString weapon_name, double x, double y, double fire_time)
    : RigidBody(mass, x, y) {
    this->is_bouncy = is_bouncy;
    this->delay = delay;
    this->radius = radius;
    this->explosion_radius = explosion_radius;
    this->damage = damage;
    this->mass = mass;
    this->weapon_name = weapon_name;
    this->fire_time = fire_time;
}

/* Uncomment once RigidBody is included
void Projectile::set_inital_position(double x, double y) {
    this->x = x;
    this->y = y;
}
*/



Projectile* Projectile::clone() {
    return new Projectile(*this);
}

int main() {
    Projectile gre = weapons[0];
    Projectile* gre_copy = gre.clone();
    gre_copy->print();
}
