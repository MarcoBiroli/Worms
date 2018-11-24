#pragma once
#include "math.h"
#include "QMap"
#include "QVector"
#include "RigidBody.h"
#include "Collider.h"

using namespace std;

class PhysicsEngine{
    private:
        QMap<int, RigidBody*> rigidbodies = QMap<int, RigidBody*>();
        QMap<int, Collider*> colliders = QMap<int, Collider*>();
        QPair<double, double> general_force = QPair<double, double>(0, 0);
    public:
        PhysicsEngine();
        PhysicsEngine(QPair<double, double> gf);
        void add_RigidBody(RigidBody* other);
        void add_Collider(Collider* other);
        void update(double dt);
        RigidBody* create_rigidbody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QImage map);
        RigidBody* create_rigidbody(double imass, double ix, double iy);
};
