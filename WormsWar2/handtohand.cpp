#include "handtohand.h"

HandToHand::HandToHand(std::string name, int weapon_id, double ipower, double explosion_radius,
                       double damage, double x, double y) : Projectile (name, weapon_id, ipower, 0, false, 0, explosion_radius, damage, 1, x, y, QPixmap())
{

}

void HandToHand::explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels){
    for (int i=0; i<worms.size(); i++) {
        Worm* worm = worms[i];
        double dist = this->distance(*worm);
        if (dist <= this->explosion_radius) {
            worm->changeHealth(this->damage);
            QPair<double, double> vect_dist =  QPair<double, double> (worm->getX() - this->x, worm->getY() - this->y);
            double Fx = this->repulsion_power*(vect_dist.first/dist)*damage/10;
            double Fy = this->repulsion_power*(vect_dist.second/dist)*damage/10;
            //Force applied depends on the damage dealt and the distance to the explosion
            QPair<double, double> explosion_force = QPair<double, double> (Fx, Fy);
            worm->addForce(explosion_force);
        }
    }
    this->sprite->hide();

}
