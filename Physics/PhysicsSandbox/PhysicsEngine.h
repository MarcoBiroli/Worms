#pragma once
#include "math.h"
#include "QMap"
#include "QVector"
#include "RigidBody.h"
#include "Collider.h"

class PhysicsEngine{
    private:
        QMap<int, RigidBody*> rigidbodies = QMap<int, RigidBody*>(); //List of all rigidbodies that are part of the world
        QMap<int, Collider*> colliders = QMap<int, Collider*>();    //List of all colliders (that are not rigidbodies) of the world
        QPair<double, double> general_force = QPair<double, double>(0, 0); //General Forces (like gravity/wind) that have to be applied constantly.
    public:
        PhysicsEngine(); //Dummy Constructor
        PhysicsEngine(QPair<double, double> gf); //Constructor, which initializes the general force parameter
        void add_RigidBody(RigidBody* other); //Add an existing RigidBody to the simulation
        void add_Collider(Collider* other); //Add an exisisting Collider to the simulation
        void update(double dt); //Update the simulation forward by dt (milliseconds)
        RigidBody* create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QImage map);
        RigidBody* create_rigidbody(double imass, double ix, double iy); //Create a new Rigidbody add it to the simulation and return it.
};
