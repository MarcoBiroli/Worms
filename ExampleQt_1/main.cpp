#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "ground.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    MainWindow w;
    w.show();
    */

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene);
    Ground *ground = new Ground(500, 500);

    ground->circ_delete(250, 250, 100);
    scene->addItem(ground->getPixmap());

    view->show();
    return a.exec();
}
