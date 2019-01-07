#include "PhysicsEngine.h"

//Constructors
PhysicsEngine::PhysicsEngine(){

}

PhysicsEngine::PhysicsEngine(QPair<double, double> gf){
    this->general_force = gf;
}

PhysicsEngine::~PhysicsEngine()
{
    qDeleteAll(rigidbodies);
    qDeleteAll(colliders);
}

//Methods

void PhysicsEngine::add_RigidBody(RigidBody* other)
{
    int max_key;
    if(this->rigidbodies.isEmpty()){
        max_key = 0;
    }
    else{
        max_key = (this->rigidbodies.end()-1).key(); //find whats the biggest key in the map of rigidbodies
    }
    other->setId(max_key + 1); //setting the id to the rigidbody (+1 is to make sure that the key is unique)
    this->rigidbodies.insert(max_key + 1, other); //inserting the rigidbody into the map of rigidbodies
}

void PhysicsEngine::add_Collider(Collider* other)
{
    //Same as above but for colliders
    int max_key;
    if(this->colliders.isEmpty()){
        max_key = 0;
    }
    else{
        max_key = (this->colliders.end()-1).key(); //find whats the biggest key in the map of rigidbodies
    }
    other->setId(max_key + 1);
    this->colliders.insert(max_key + 1, other);
}

void PhysicsEngine::update(double dt)
{
    //initializing the iterators and parameters
    QMap<int, RigidBody*>::iterator i;
    QMap<int, Collider*>::iterator j;
    QMap<int, RigidBody*>::iterator k;
    QPair<bool, QPair<double, double>> collision_result;
    //for all rigidbodies
    bool deletion_flag = false;
    for(i = this->rigidbodies.begin(); i != this->rigidbodies.end(); i++)
    {
        deletion_flag = false;
        //Reset collision flag
        i.value()->is_colliding = false;
        //Reset is_grounded flag
        i.value()->is_grounded.first = false;
        //add the general force to the rigidbody
        i.value()->addForce(this->general_force);
        i.value()->addForce(QPair<double,double> (0,9.81*i.value()->getm()));
        //for all colliders
        for(k = this->rigidbodies.begin(); k != this->rigidbodies.end(); k++){
            if(k == i){
                continue;
            }
            collision_result = i.value()->check_collision(*k.value());
            if(collision_result.first){
                //Set Collision flag to true
                if(i.value()->on_collision_do(*k.value())){
                    i.value()->sprite->hide();
                    this->delete_rigidbody(i.key());
                    deletion_flag = true;
                    break;
                }
                i.value()->is_colliding = true;
                i.value()->bounce(collision_result.second,dt);
            }
        }
        for(j = this->colliders.begin(); j != this->colliders.end(); j++){
            //check the collision of the rigidbody with the collider
            collision_result = i.value()->check_collision(*j.value());
            if(collision_result.first){
                //Set Collision flag to true
                if(i.value()->on_collision_do(*j.value())){
                    i.value()->sprite->hide();
                    this->delete_rigidbody(i.key());
                    deletion_flag = true;
                    break;
                }
                i.value()->is_colliding = true;
                //if there is ground collision then set is_grounded to true
                if(j.value()->is_ground == true){
                    i.value()->is_grounded = collision_result;
                }
                //if it is colliding react accordingly to the bounce method
                i.value()->bounce(collision_result.second,dt);
            }
        }
        if(!deletion_flag){
            //simulate the rigidbody's physics
            i.value()->simulate(dt);
            i.value()->sprite->setPos(i.value()->getX(), i.value()->getY());
        }
    }
}

//Creating a rigidbody
RigidBody* PhysicsEngine::create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, QImage map)
{
    RigidBody* newBody = new RigidBody( imass,  ix,  iy,  vx0,  vy0,  ax0,  ay0,  map);
    this->add_RigidBody(newBody);
    return newBody;
}

RigidBody *PhysicsEngine::create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, QImage map, QPixmap sprite)
{
    RigidBody* newBody = new RigidBody( imass,  ix,  iy,  vx0,  vy0,  ax0,  ay0,  map, sprite);
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
RigidBody *PhysicsEngine::get_rigidbody (int id) const
{
    return this->rigidbodies.value(id);
}

void PhysicsEngine::delete_rigidbody(int id)
{
    //delete rigidbodies.value(id); //freeeee memooooory
    rigidbodies.remove(id);
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
Collider *PhysicsEngine::get_collider (int id) const
{
    return this->colliders.value(id);
}
