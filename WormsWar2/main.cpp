#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../GUI/ground.h"
#include "../GUI/customview.h"
#include "../Physics/PhysicsEngine.h"

int main(int argc, char *argv[])
{
    //This is the main function of the main file, this is what is run as soon as the program is launched.
    QApplication a(argc, argv);

    //Initialize the window
    QGraphicsScene *scene = new QGraphicsScene();

    //Put a graphics view inside of the window
    CustomView *view = new CustomView(scene);

    PhysicsEngine Engine(QPair<double, double>(0, 9.81));

    //Create a Ground of size (500x500)
    Ground *ground = new Ground(5000, 3000);
    Engine.add_Collider(ground);
    //Create a Rigidbody
    RigidBody* body = Engine.create_rigidbody(1, 2500, 0);
    body->setbounciness(0.8);

    QGraphicsPixmapItem *tmp = new QGraphicsPixmapItem(QPixmap::fromImage(body->get_map())); //

    //Delete everything in the ground in radius of 100px aroud (250,250)
    ground->circ_delete(2500, 600, 200);

    //Add the ground image to the window so it gets displayed
    scene->addItem(ground->getPixmap());

    scene->addItem(tmp);
    tmp->setPos(body->getX(), body->getY());

    view->active_worm = body;

    QTime lastUpdate= QTime::currentTime();
    int timeSinceLastUpdate = QTime::currentTime().msecsTo(lastUpdate);
    double update_time = 10;

    bool quitGame = false; 
    while(!quitGame){
        a.processEvents();

        timeSinceLastUpdate = lastUpdate.msecsTo(QTime::currentTime());
        if(timeSinceLastUpdate>update_time){
            for(int i = 0; i < 5; i++){
                Engine.update(timeSinceLastUpdate);
            }
            tmp->setPos(body->getX(), body->getY());
            lastUpdate = QTime::currentTime();
        }
        view->showNormal();
    }

    return a.exec();
}
