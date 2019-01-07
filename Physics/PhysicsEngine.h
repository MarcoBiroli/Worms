#pragma once
#include "math.h"
#include "QMap"
#include "QVector"
#include "RigidBody.h"
#include "Collider.h"

class PhysicsEngine{
    private:

        QMap<int, RigidBody*> rigidbodies = QMap<int, RigidBody*>(); //map of rigidbodies
        QMap<int, Collider*> colliders = QMap<int, Collider*>(); //map of colliders that are not rigidbodies
        QPair<double, double> general_force = QPair<double, double>(0, 0); //force (Fx, Fy)
    public:
        //Constructors
        PhysicsEngine();
        PhysicsEngine(QPair<double, double> gf);
        ~PhysicsEngine();

        //Methods

        void add_RigidBody(RigidBody* other);
        void add_Collider(Collider* other);
        void update(double dt); //updates the physics simulation by dt (milliseconds)

        //Creating rigidbodies/ colliders and adding them to the engine with an id and returning them
        RigidBody* create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, QImage map);
        RigidBody* create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, QImage map, QPixmap sprite);
        RigidBody* create_rigidbody(double imass, double ix, double iy);
        RigidBody* get_rigidbody(int id) const; //access a rigidbody through id

        void delete_rigidbody(int id);

        Collider* create_collider(double ix, double iy, QImage map);
        Collider* create_collider(double ix, double iy);
        Collider* get_collider(int id) const; //access a collider through id
};
