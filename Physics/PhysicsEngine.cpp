#include "PhysicsEngine.h"

void PhyscisEngine::add_RigidBodies(QMap<int, RigidBody> others)
{
    this->rigidbodies.append(others);
}

void PhyscisEngine::add_Colliders(QMap<int, Collider> others)
{
    this->colliders.append(others);
}

void PhyscisEngine::update(double dt)
{
    ground.collider.check_collision(this->colliders);
    QMap<int, Collider>::iterator i = this->colliders.begin();
    for(i != this->colliders.end(); i++)
    {
        i.value().check_collision(this->colliders);
    }
    QMap<int, RigidBody>::iterator j = this->rigidbodies.begin();
    for(j != this->rigidbodies.end(); j++)
    {
        j.simulate(dt);
    }
}