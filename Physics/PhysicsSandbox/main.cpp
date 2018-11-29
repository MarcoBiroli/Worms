#include <QApplication>
#include "ground.h"
#include "Collider.h"
#include "RigidBody.h"
#include "PhysicsEngine.h"
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        //Initialize the window
        QGraphicsScene *scene = new QGraphicsScene();
        //Put a graphics view inside of the window
        QGraphicsView *view = new QGraphicsView(scene);
        //Initialize the physics engine with Gravity
        PhysicsEngine Engine(QPair<double, double>(0, 9.81));

        //Create a Ground of size (1440 x 900) - resolution of my Mac's screen

        Ground ground = Ground(1440, 900);
        Engine.add_Collider(&ground);
        //Create a Rigidbody
        RigidBody* body = Engine.create_rigidbody(1, 250, 0);
        body->setbounciness(0.8);

        //Delete everything in the ground in radius of 100px aroud (250,250)
        ground.circ_delete(250, 250, 100);

        //Add the ground image to the window so it gets displayed

        QGraphicsPixmapItem *tmp_ground = new QGraphicsPixmapItem(QPixmap::fromImage(ground.get_map()));
        scene-> addItem(tmp_ground);

        QGraphicsPixmapItem *tmp = new QGraphicsPixmapItem(QPixmap::fromImage(body->get_map())); //?

        tmp->setFlag(QGraphicsItem::ItemIsMovable);
        scene->addItem(tmp);
        tmp->setPos(body->getX(), body->getY());

        QTime lastUpdate= QTime::currentTime();
        int timeSinceLastUpdate = QTime::currentTime().msecsTo(lastUpdate);
        double update_time = 10;

        while(true){
            a.processEvents();

            timeSinceLastUpdate = lastUpdate.msecsTo(QTime::currentTime());
            if(timeSinceLastUpdate>update_time){
                for(int i = 0; i < 5; i++){
                    Engine.update(timeSinceLastUpdate);
                }
                tmp->setPos(body->getX(), body->getY());
                lastUpdate = QTime::currentTime();
            }
            view->show();
        }
        return a.exec();
}

