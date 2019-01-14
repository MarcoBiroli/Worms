#ifndef HANDTOHAND_H
#define HANDTOHAND_H

#include <../Core/Projectile.h>

class HandToHand: public Projectile
{
public:
    HandToHand(std::string name, int weapon_id, double ipower, double explosion_radius, double damage, double x, double y);
    virtual void explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels);
};

#endif // HANDTOHAND_H
