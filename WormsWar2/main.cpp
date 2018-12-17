#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../Core/Game.h"
#include "../GUI/ground.h"
#include "../GUI/customview.h"
#include "../GUI/music.h"
#include "../Physics/PhysicsEngine.h"
#include "../Core/worms.h"

int main(int argc, char *argv[])
{
    //This is the main function of the main file, this is what is run as soon as the program is launched.
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(res);

    //Initialize the window
    QGraphicsScene *scene = new QGraphicsScene();

    //Put a graphics view inside of the window
    CustomView *view = new CustomView(scene);
    //view->setSceneRect(-10000, -10000, 20000, 20000);

    //Initialize a game
    Game game = Game(scene, view, 2, 5000, 2, 5000, 3000);

    view->game = &game;
    //game.ground->circ_delete(200, 500, 150);

    QTime lastUpdate= QTime::currentTime();
        int timeSinceLastUpdate = QTime::currentTime().msecsTo(lastUpdate);
        double update_time = 10;

        while(!view->has_quitted){
            a.processEvents();
            timeSinceLastUpdate = lastUpdate.msecsTo(QTime::currentTime());
            if(timeSinceLastUpdate>update_time){
                game.gameIteration(timeSinceLastUpdate);
                lastUpdate = QTime::currentTime();
            }
            view->showMaximized();
        }
        //delete view;  // //press alt key to stop the loop + F4 (cmd + 'Q' on mac) to close the window
        //delete scene;
        return a.exec();


    //PhysicsEngine Engine(QPair<double, double>(0, 9.81));
    //view->Engine = &Engine;
    //view->scene = scene;

    //Create a Ground of size (500x500)
    //Ground *ground = new Ground(5000, 3000);
    //Engine.add_Collider(ground);

    //QImage worm_right("://Images/Clipart_worm_right.png");
    //worm_right = worm_right.scaled(QSize(32,32));

    //Create a Rigidbody
    //Worm* Gerard = new Worm(0, "Gerard", 100, 1, 2200, 0, QPixmap::fromImage(worm_right));

    //Gerard->setbounciness(0);
    //Engine.add_RigidBody(Gerard);


    //RigidBody* body = Engine.create_rigidbody(1, 250, 0);
    //body->setbounciness(0.6);

    //Gerard->sprite->setPixmap(QPixmap::fromImage(worm_right));

    //Delete everything in the ground in radius of 100px aroud (250,250)
    //ground->circ_delete(2500, 600, 200);
    //ground->circ_delete(2900,600, 400);

    //Add the ground image to the window so it gets displayed
    //scene->addItem(ground->getPixmap());

    //scene->addItem(Gerard->sprite);

    //view->active_worm = Gerard;

    /*QTime lastUpdate= QTime::currentTime();
    int timeSinceLastUpdate = QTime::currentTime().msecsTo(lastUpdate);
    double update_time = 10;

    while(!view->has_quitted){
        a.processEvents();
        timeSinceLastUpdate = lastUpdate.msecsTo(QTime::currentTime());
        if(timeSinceLastUpdate>update_time){
            for(int i = 0; i < 10; i++){
                Engine.update(update_time);
            }
            double theta = qAtan2(-Gerard->is_grounded.second.first, Gerard->is_grounded.second.second);
            double M[4] = {qCos(theta), qSin(theta), -qSin(theta), qCos(theta)};
            double ve = M[0]*Gerard->getvx() + M[1]*Gerard->getvy();
            if(ve > 0){
                Gerard->sprite->setPixmap(QPixmap::fromImage(worm_left));
            }
            else{
                Gerard->sprite->setPixmap(QPixmap::fromImage(worm_right));
            }
            lastUpdate = QTime::currentTime();
        }
        view->showMaximized();
    }
    //delete view;  // //press alt key to stop the loop + F4 (cmd + 'Q' on mac) to close the window
    //delete scene;*/

    return a.exec();



    /* Using Game class (Not finished)

    //This is the main function of the main file, this is what is run as soon as the program is launched.
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(res);

    //Initialize the window
    QGraphicsScene *scene = new QGraphicsScene();

    //Put a graphics view inside of the window
    CustomView *view = new CustomView(scene);

    Game *game = new Game(1);

    //RigidBody* body = Engine.create_rigidbody(1, 250, 0);
    //body->setbounciness(0.6);

    QImage worm_right("://Images/Clipart_worm_right.png");
    worm_right = worm_right.scaled(QSize(32,32));
    QImage worm_left("://Images/Clipart_worm_left.png");
    worm_left = worm_left.scaled(QSize(32,32));
    QMovie moving_worm_right("://Images/Clipart_worm_right.gif");
    moving_worm_right.setScaledSize(QSize(32,32));
    QMovie moving_worm_left("://Images/Clipart_worm_left.gif");
    moving_worm_left.setScaledSize(QSize(32,32));

    QGraphicsPixmapItem *tmp = new QGraphicsPixmapItem(QPixmap::fromImage(worm_right));

    //Delete everything in the ground in radius of 100px aroud (250,250)
    game->ground.circ_delete(2500, 600, 200);

    //Add the ground image to the window so it gets displayed
    scene->addItem(game->ground.getPixmap());

    scene->addItem(tmp);
    tmp->setPos(Gerard->getX(), Gerard->getY());

    view->active_worm = Gerard;

    QTime lastUpdate= QTime::currentTime();
    int timeSinceLastUpdate = QTime::currentTime().msecsTo(lastUpdate);
    double update_time = 10;

    while(!view->has_quitted){
        a.processEvents();
        timeSinceLastUpdate = lastUpdate.msecsTo(QTime::currentTime());
        if(timeSinceLastUpdate>update_time){
            for(int i = 0; i < 10; i++){
                Engine.update(update_time);
            }
            if(Gerard->getvx() < 0){
                tmp->setPixmap(QPixmap::fromImage(worm_left));
            }
            else{
                tmp->setPixmap(QPixmap::fromImage(worm_right));
            }
            tmp->setPos(Gerard->getX(), Gerard->getY());
            lastUpdate = QTime::currentTime();
        }
        view->showMaximized();
    }
    //delete view;  // //press alt key to stop the loop + F4 to close the window
    //delete scene;
    return a.exec();

    */
}
