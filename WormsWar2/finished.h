#ifndef FINISHED_H
#define FINISHED_H

#include <QMainWindow>
#include "mainwindow.h"
#include "../GUI/music.h"
#include "../GUI/customview.h"

/*Game Over class is displayed when the game loop is done. It displayes the winning team*/

class MainWindow;

namespace Ui {
class Finished;
}

class Finished : public QMainWindow
{
    Q_OBJECT

public:
    explicit Finished(QWidget *parent = nullptr);
    ~Finished();
    CustomView *view;
    MainWindow *mainwindow;

    void update_label(QString label);//used in the main.cpp

private slots:
    //Methods
    void on_mainmenuButton_clicked();
    void on_ExitButton_clicked();



private:
    Ui::Finished *ui;
};

#endif // FINISHED_H
