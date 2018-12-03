#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(){

}

PhysicsEngine::PhysicsEngine(QPair<double, double> gf){
    this->general_force = gf;
}

void PhysicsEngine::add_RigidBody(RigidBody* other)
{
    int max_key = this->rigidbodies.end().key();
    other->setId(max_key + 1);
    this->rigidbodies.insert(max_key + 1, other);
}

void PhysicsEngine::add_Collider(Collider* other)
{
    int max_key = this->colliders.end().key();
    other->setId(max_key + 1);
    this->colliders.insert(max_key + 1, other);
}

void PhysicsEngine::update(double dt)
{
    QMap<int, RigidBody*>::iterator i = this->rigidbodies.begin();
    QMap<int, Collider*>::iterator j;
    QPair<bool, QPair<double, double>> collision_result;
    for(i; i != this->rigidbodies.end(); i++)
    {
        i.value()->addForce(this->general_force);
        for(j = this->colliders.begin(); j != this->colliders.end(); j++){
            collision_result = i.value()->check_collision(*j.value());
            if(collision_result.first){
                i.value()->bounce(collision_result.second,dt);
            }
        }
        i.value()->simulate(dt);
    }
}

RigidBody* PhysicsEngine::create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QImage map)
{
    RigidBody* newBody = new RigidBody( imass,  ix,  iy,  vx0,  vy0,  ax0,  ay0,  iid,  map);
    this->add_RigidBody(newBody);
    return newBody;
}

RigidBody* PhysicsEngine::create_rigidbody(double imass, double ix, double iy)
{
    RigidBody* newBody = new RigidBody( imass,  ix,  iy);
    this->add_RigidBody(newBody);
    return newBody;
}
