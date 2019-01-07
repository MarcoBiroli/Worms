#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../Core/Game.h"
#include "../GUI/ground.h"
#include "../GUI/customview.h"
#include "../Physics/PhysicsEngine.h"
#include "../Core/worms.h"

int main(int argc, char *argv[])
{
    //This is the main function of the main file, this is what is run as soon as the program is launched.
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(res);


    MainWindow * MainMenu = new MainWindow();
    MainMenu->show();

    while(true){
        a.processEvents();
        if (MainMenu->start_game == true){
            //Initialize the window
            MainMenu->start_game = false;
            QGraphicsScene *scene = new QGraphicsScene();

            //Put a graphics view inside of the window
            CustomView *view = new CustomView(scene);
            //view->setSceneRect(0, 0, 20000, 20000);

            //Initialize a game

            Game *game = new Game(scene, view, 2, 10000, 2, 5000, 3000);

            view->game = game;
            view->currentScale = 1;

            QTime lastUpdate= QTime::currentTime();
            int timeSinceLastUpdate = QTime::currentTime().msecsTo(lastUpdate);
            double update_time = 10;
            bool is_done = false;
            //QTime starttime = QTime::currentTime();
            while(!view->has_quitted && !is_done){
                a.processEvents();
                timeSinceLastUpdate = lastUpdate.msecsTo(QTime::currentTime());
                if(timeSinceLastUpdate>update_time){
                    is_done = game->gameIteration(timeSinceLastUpdate);
                    //lastUpdate = QTime::currentTime();
                    //double turn_timer = starttime.msecsTo(QTime::currentTime());
                    //double water_height = ground -> WaterHeight(ground_size_y,turn_timer);
                    //ground -> Water(ground_size_x,ground_size_y,water_height);
                }
                view->showMaximized();
            }
            delete view;
            delete scene;
            delete game;
            MainMenu->show();
        }
    }
    return 0;
}
