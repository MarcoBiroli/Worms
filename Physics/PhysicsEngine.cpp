#include "PhysicsEngine.h"

//Constructors
PhysicsEngine::PhysicsEngine(){

}

PhysicsEngine::PhysicsEngine(QPair<double, double> gf){
    this->general_force = gf;
}

//Methods

void PhysicsEngine::add_RigidBody(RigidBody* other)
{
    int max_key = this->rigidbodies.end().key(); //find whats the biggest key in the map of rigidbodies
    other->setId(max_key + 1); //setting the id to the rigidbody (+1 is to make sure that the key is unique)
    this->rigidbodies.insert(max_key + 1, other); //inserting the rigidbody into the map of rigidbodies
}

void PhysicsEngine::add_Collider(Collider* other)
{
    //Same as above but for colliders
    int max_key = this->colliders.end().key();
    other->setId(max_key + 1);
    this->colliders.insert(max_key + 1, other);
}

void PhysicsEngine::update(double dt)
{
    //initializing the iterators and parameters
    QMap<int, RigidBody*>::iterator i = this->rigidbodies.begin();
    QMap<int, Collider*>::iterator j;
    QPair<bool, QPair<double, double>> collision_result;
    //for all rigidbodies
    for(i; i != this->rigidbodies.end(); i++)
    {
        //Reset collision flag
        i.value()->is_colliding = false;
        //Reset is_grounded flag
        i.value()->is_grounded = false;
        //add the general force to the rigidbody
        i.value()->addForce(this->general_force);
        //for all colliders
        for(j = this->colliders.begin(); j != this->colliders.end(); j++){
            //check the collision of the rigidbody with the collider
            collision_result = i.value()->check_collision(*j.value());
            if(collision_result.first){
                //Set Collision flag to true
                i.value()->is_colliding = true;
                //if there is ground collision then set is_grounded to true
                if(j.value()->is_ground == true){
                    i.value()->is_grounded = true;
                }
                //if it is colliding react accordingly to the bounce method
                i.value()->bounce(collision_result.second,dt);
            }
        }
        //simulate the rigidbody's physics
        i.value()->simulate(dt);
    }
}

//Creating a rigidbody
RigidBody* PhysicsEngine::create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, QImage map)
{
    RigidBody* newBody = new RigidBody( imass,  ix,  iy,  vx0,  vy0,  ax0,  ay0,  map);
    this->add_RigidBody(newBody);
    return newBody;
}

RigidBody* PhysicsEngine::create_rigidbody(double imass, double ix, double iy)
{
    RigidBody* newBody = new RigidBody( imass,  ix,  iy);
    this->add_RigidBody(newBody);
    return newBody;
}

//Getting the rigidbody through the id
RigidBody *PhysicsEngine::get_rigidbody(int id)
{
    return this->rigidbodies.value(id);
}

//Create a collider
Collider *PhysicsEngine::create_collider(double ix, double iy, QImage map)
{
    Collider* newCollider = new Collider(ix, iy, map);
    this->add_Collider(newCollider);
    return newCollider;
}

Collider *PhysicsEngine::create_collider(double ix, double iy)
{
    Collider* newCollider = new Collider(ix, iy);
    this->add_Collider(newCollider);
    return newCollider;
}

//Getting the rigidbody through id
Collider *PhysicsEngine::get_collider(int id)
{
    return this->colliders.value(id);
}
