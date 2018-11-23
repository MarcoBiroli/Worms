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
        void add_RigidBodies(QMap<int, RigidBody> others);
        void add_indices(QVector<RigidBody> others);
        void add_Colliders(QMap<int, Collider> others);
        void update(double dt);
    
};
