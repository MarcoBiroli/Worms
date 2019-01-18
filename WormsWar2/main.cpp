#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSound>
#include <QMediaPlayer>

#include "../Core/Game.h"
#include "../GUI/ground.h"
#include "../GUI/customview.h"
#include "../Physics/PhysicsEngine.h"
#include "../Core/worms.h"

#include "settings.h"
#include "help.h"
#include "finished.h"

/*Main class executes the Game*/

int main(int argc, char *argv[])
{
    //This is the main function of the main file, this is what is run as soon as the program is launched.
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(res);

    //Initializing MainMenu, Settings, Help, GameOver(finished) menu
    MainWindow * MainMenu = new MainWindow();
    MainMenu->show();
    Settings * setting = new Settings();
    MainMenu->settingmenu = setting;
    setting->mainwindow = MainMenu;
    Help * helpmenu = new Help();
    MainMenu->helpmenu = helpmenu;
    helpmenu->mainwindow = MainMenu;
    Finished *finishmenu = new Finished();
    finishmenu->mainwindow = MainMenu;
    //Sound effects
    Music musicplaylist;
    QList<QString> ListSongs = {"qrc:/Music/ES_Sophisticated Gentlemen 2 - Magnus Ringblom.wav"};
    musicplaylist.infinitemusic(ListSongs);

    //game loop
    while(MainMenu->quit_button!=true){
        a.processEvents();

        //LEVEL = EASY
        if (MainMenu->start_easy == true){
            //Initialize the window
            MainMenu->start_easy= false;
            QGraphicsScene *scene = new QGraphicsScene();
            //Put a graphics view inside of the window
            CustomView *view = new CustomView(scene);
            //view->setSceneRect(0, 0, 5000, 3000);
            //Initialize Game
            Game *game = new Game(&a, 1, MainMenu, scene, view, setting, 5000, 3000);
            MainMenu->hide();
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
            //Game over. The below code is determine and display who is the winning team/ tie.
            if(MainMenu->through_esc){
                MainMenu->through_esc = false;
                QString string = "";
                if (game->get_team().length() != 1){
                    for (int i=0; i<game->get_team().length(); i++){
                        string.append(QString::number(i+1));
                        string.append(",");
                    }
                }
                else{
                    string = QString::number(game->get_team()[0]+1);
                }
                finishmenu->update_label(string);
            }
            else{
                finishmenu->update_label(QString::number(game->getwinner() + 1));
            }
            //Delete game
            delete view;
            delete scene;
            delete game;
            finishmenu->show();
        }

        //LEVEL = MEDIUM
        if (MainMenu->start_medium == true){
            //Initialize the window
            MainMenu->start_medium = false;
            QGraphicsScene *scene = new QGraphicsScene();

            //Put a graphics view inside of the window
            CustomView *view = new CustomView(scene);
            //view->setSceneRect(0, 0, 20000, 20000);

            //Initialize a game
            Game *game = new Game(&a, 2, MainMenu, scene, view, setting, 5000, 3000);
            MainMenu->hide();
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
            //Game over. The below code is determine and display who is the winning team/ tie.
            if(MainMenu->through_esc){
                QString string;
                if (game->get_team().length() != 1){
                    for (int i=0; i<game->get_team().length(); i++){
                        string.append(QString::number(i+1));
                        string.append(",");
                    }
                    string.remove(",");
                }
                else{
                    string = QString::number(game->get_team()[0]+1);
                }
                finishmenu->update_label(string);
            }
            else{
                finishmenu->update_label(QString::number(game->getwinner() + 1));
            }
            //Delete game
            delete view;
            delete scene;
            delete game;
            finishmenu->show();
        }
        if (MainMenu->start_hard == true){
            //Initialize the window
            MainMenu->start_hard = false;
            QGraphicsScene *scene = new QGraphicsScene();

            //Put a graphics view inside of the window
            CustomView *view = new CustomView(scene);
            //view->setSceneRect(0, 0, 20000, 20000);

            //Initialize a game
            Game *game = new Game(&a, 3, MainMenu, scene, view, setting, 5000, 3000);
            MainMenu->hide();
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
            //Game over. The below code is determine and display who is the winning team/ tie.
            if(MainMenu->through_esc){
                QString string;
                if (game->get_team().length() != 1){
                    for (int i=0; i<game->get_team().length(); i++){
                        string.append(QString::number(i+1));
                        string.append(",");
                    }
                    string.remove(",");
                }
                else{
                    string = QString::number(game->get_team()[0]+1);
                }
                finishmenu->update_label(string);
            }
            else{
                finishmenu->update_label(QString::number(game->getwinner() + 1));
            }
            //Delete game
            delete view;
            delete scene;
            delete game;
            finishmenu->show();
        }
    }
    return 0;
}
