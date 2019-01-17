#include "handtohand.h"

HandToHand::HandToHand(std::string name, int weapon_id, double ipower, double explosion_radius,
                       double damage, double x, double y) : Projectile (name, weapon_id, ipower, 0, true, 0, 0, damage, 1, x, y, QPixmap())
{
    max_dist = explosion_radius;
    is_hand_to_hand = true;
}

HandToHand::HandToHand(const HandToHand& other) : Projectile (other){
    max_dist = other.max_dist;
    is_hand_to_hand = true;
}

void HandToHand::explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels){
    for (int i=0; i<worms.size(); i++) {
        Worm* worm = worms[i];
        if (worm == this->firing_worm){
            continue;
        }
        double dist = this->distance(*worm);
        if (dist <= this->max_dist) {
            worm->tangent_bouncing = false;
            worm->changeHealth(this->damage);
            QPair<double, double> vect_dist =  QPair<double, double> (worm->getX() - this->firing_worm->getX(), worm->getY() - this->firing_worm->getY() - 10);
            double Fx = this->repulsion_power*(vect_dist.first/dist)*damage/0.01;
            double Fy = this->repulsion_power*(vect_dist.second/dist)*damage/0.01;
            //Force applied depends on the damage dealt and the distance to the explosion
            QPair<double, double> explosion_force = QPair<double, double> (Fx, Fy);
            worm->setX(worm->getX()+worm->is_grounded.second.first);
            worm->setY(worm->getY() + worm->is_grounded.second.second);
            worm->addForce(explosion_force);
        }
    }
    this->sprite->hide();
}

HandToHand *HandToHand::clone()
{
    return new HandToHand(*this);
}
