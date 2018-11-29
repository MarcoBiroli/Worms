#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(){
    //Empty Constructor
}

PhysicsEngine::PhysicsEngine(QPair<double, double> gf){
    //Initializes the general force
    this->general_force = gf;
}

void PhysicsEngine::add_RigidBody(RigidBody* other)
{
    int max_key;
    if(this->rigidbodies.size() > 0){ //If we are already storing some rigidbodies
        //Find the biggest used key (QMap) is sorted lowest to highest.
        max_key = this->rigidbodies.end().key();
        //Set the ID of the new object to be the next ID
        other->setId(max_key + 1);
    }
    else{
        max_key = -1; //If the map is empty we have no max_key
        other->setId(0);
    }
    this->rigidbodies.insert(max_key + 1, other); //Insert the rigidbody with the new key
}

void PhysicsEngine::add_Collider(Collider* other) //Same principle as above but for a collider.
{
    int max_key;
    if(this->rigidbodies.size() > 0){
        max_key = this->colliders.end().key();
        other->setId(max_key + 1);
    }
    else{
        max_key = -1;
        other->setId(0);
    }
    this->colliders.insert(max_key + 1, other);
}

void PhysicsEngine::update(double dt) //Update the simulation, dt is in milliseconds.
{
    QMap<int, RigidBody*>::iterator i = this->rigidbodies.begin();
    QMap<int, Collider*>::iterator j;
    QPair<bool, QPair<double, double>> collision_result;
    for(i; i != this->rigidbodies.end(); i++) //Iterate over all the rigidbodies
    {
        i.value()->addForce(this->general_force); //Add the general forces
        i.value()->is_grounded = false;
        for(j = this->colliders.begin(); j != this->colliders.end(); j++){ //Check for every collider if it is colliding.
            collision_result = i.value()->check_collision(*j.value());
            if(collision_result.first){ //If it is colliding then act accordingly.
                if(j.value()->is_ground()){
                    i.value()->is_grounded = true;
                }
                i.value()->bounce(collision_result.second, dt);
            }
        }
        i.value()->simulate(dt); //Update the rigidbody
    }
}

RigidBody* PhysicsEngine::create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QImage map)
{
    RigidBody* newBody = new RigidBody( imass,  ix,  iy,  vx0,  vy0,  ax0,  ay0,  iid,  map); //Create a new RigidBody
    this->add_RigidBody(newBody); //Add the RigidBody to the simulation
    return newBody; //Give the handle to the caller of the function.
}

RigidBody* PhysicsEngine::create_rigidbody(double imass, double ix, double iy)
{
    RigidBody* newBody = new RigidBody( imass,  ix,  iy); //Create a new Collider
    this->add_RigidBody(newBody); //Add the collider to the simulation
    return newBody; //Give back the handle to the caller of the function.
}
