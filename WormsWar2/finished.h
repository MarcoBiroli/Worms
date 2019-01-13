#ifndef FINISHED_H
#define FINISHED_H

#include <QMainWindow>
#include "mainwindow.h"
#include "../GUI/music.h"
#include "../GUI/customview.h"

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
    void update_label(QString label);

private slots:
    void on_mainmenuButton_clicked();
    void on_ExitButton_clicked();



private:
    Ui::Finished *ui;
};

#endif // FINISHED_H
