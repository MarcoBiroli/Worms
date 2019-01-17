#ifndef HANDTOHAND_H
#define HANDTOHAND_H

#include <../Core/Projectile.h>

/*Hand-to-hand class inherits Projectile class. They are fired in the same way as normal Projectiles however
as they create damage only when in contact with another worm, the explode function changes.*/

class HandToHand: public Projectile
{
public:
    //Constructor
    HandToHand(std::string name, int weapon_id, double ipower, double explosion_radius, double damage, double x, double y);
    virtual HandToHand* clone();
    HandToHand(const HandToHand &other);

    //Exploding function
    virtual void explode(Ground &ground, PhysicsEngine &engine, QVector<Projectile*> &projectiles, QVector<Worm*> &worms, QVector<Barrel*> &barrels);

private:
    //Parameter
    double max_dist = 0;
};

#endif // HANDTOHAND_H
