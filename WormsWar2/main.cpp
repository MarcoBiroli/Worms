#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../Core/Game.h"
#include "../GUI/ground.h"
#include "../GUI/customview.h"
#include "../Physics/PhysicsEngine.h"
#include "../Core/worms.h"
#include "settings.h"
#include "help.h"
#include <QSound>
#include <QMediaPlayer>


int main(int argc, char *argv[])
{
    //This is the main function of the main file, this is what is run as soon as the program is launched.
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(res);


    MainWindow * MainMenu = new MainWindow();
    MainMenu->show();
    Settings * setting = new Settings();
    MainMenu->settingmenu = setting;
    setting->mainwindow = MainMenu;
    Help * helpmenu = new Help();
    MainMenu->helpmenu = helpmenu;
    helpmenu->mainwindow = MainMenu;

    while(MainMenu->quit_button!=true){
        a.processEvents();
        if (MainMenu->start_easy == true){
            //Initialize the window
            MainMenu->start_easy= false;
            QGraphicsScene *scene = new QGraphicsScene();

            //Put a graphics view inside of the window
            CustomView *view = new CustomView(scene);
            //view->setSceneRect(0, 0, 20000, 20000);

            //Initialize a game Game(int number,QGraphicsScene *iscene, QGraphicsView *iview, int ground_size_x=5000, int ground_size_y=3000, Settings *settings);


            Game *game = new Game(1, MainMenu, scene, view, setting, 5000, 3000);

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
                    lastUpdate = QTime::currentTime();
                }
                view->showFullScreen();
            }
            delete view;
            delete scene;
            delete game;
            MainMenu->show();
        }
        if (MainMenu->start_medium == true){
            //Initialize the window
            MainMenu->start_medium = false;
            QGraphicsScene *scene = new QGraphicsScene();

            //Put a graphics view inside of the window
            CustomView *view = new CustomView(scene);
            //view->setSceneRect(0, 0, 20000, 20000);

            //Initialize a game

            Game *game = new Game(2, MainMenu, scene, view, setting, 5000, 3000);

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
                    lastUpdate = QTime::currentTime();
                }
                view->showFullScreen();
            }
            delete view;
            delete scene;
            delete game;
            MainMenu->show();
        }
        if (MainMenu->start_hard == true){
            //Initialize the window
            MainMenu->start_hard = false;
            QGraphicsScene *scene = new QGraphicsScene();

            //Put a graphics view inside of the window
            CustomView *view = new CustomView(scene);
            //view->setSceneRect(0, 0, 20000, 20000);

            //Initialize a game

            Game *game = new Game(3, MainMenu, scene, view, setting, 5000, 3000);

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
                    lastUpdate = QTime::currentTime();
                }
                view->showFullScreen();
            }
            delete view;
            delete scene;
            delete game;
            MainMenu->show();
        }
    }
    return 0;
}
