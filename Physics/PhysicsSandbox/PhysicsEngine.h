#pragma once
#include "math.h"
#include "QMap"
#include "QVector"
#include "RigidBody.h"
#include "Collider.h"

using namespace std;

class PhysicsEngine{
    private:
        QMap<int, RigidBody> rigidbodies = QMap<int, RigidBody>();
        QMap<int, Collider> colliders = QMap<int, Collider>();
        //Ground ground;
    public:
        void add_RigidBody(RigidBody other);
        void add_Collider(Collider other);
        void update(double dt);
    
};
