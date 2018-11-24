#include "PhysicsEngine.h"

void PhysicsEngine::add_RigidBody(RigidBody other)
{
    int max_key = this->rigidbodies.end().key();
    other.setId(max_key + 1);
    this->rigidbodies.insert(max_key + 1, other);
}

void PhysicsEngine::add_Collider(Collider other)
{
    int max_key = this->colliders.end().key();
    other.setId(max_key + 1);
    this->colliders.insert(max_key + 1, other);
}

void PhysicsEngine::update(double dt)
{

}
