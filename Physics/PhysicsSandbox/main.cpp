#include "mainwindow.h"
#include <QApplication>
#include "ground.h"
#include "Collider.h"
#include "RigidBody.h"
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        //Initialize the window
        QGraphicsScene *scene = new QGraphicsScene();
        //Put a graphics view inside of the window
        QGraphicsView *view = new QGraphicsView(scene);
        //Create a Ground of size (500x500)
        Ground *ground = new Ground(500, 500);
        //Create a Rigidbody
        RigidBody* body = new RigidBody(1, 250, 0);


        //Delete everything in the ground in radius of 100px aroud (250,250)
        ground->circ_delete(250, 250, 100);

        //Add the ground image to the window so it gets displayed
        QGraphicsPixmapItem *tmp_ground = new QGraphicsPixmapItem(QPixmap::fromImage(ground->colliding_map));
        scene-> addItem(tmp_ground);

        QGraphicsPixmapItem *tmp = new QGraphicsPixmapItem(QPixmap::fromImage(body->colliding_map)); //?

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
                body->addForce(QPair<double, double>(0, 9.81));
                body->simulate(timeSinceLastUpdate);

                //if (body->check_collision.first() == true){
                // body-> addForce(check_collision.second());
                //
                //}
                body->check_collision(tmp_ground);


                tmp->setPos(body->getX(), body->getY());
                lastUpdate = QTime::currentTime();
            }

            view->show();
        }
        return a.exec();
}
