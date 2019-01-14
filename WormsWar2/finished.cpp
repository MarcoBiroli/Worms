#include "finished.h"
#include "ui_finished.h"

Finished::Finished(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Finished)
{
    ui->setupUi(this);
}

Finished::~Finished()
{
    delete ui;
}

void Finished::on_mainmenuButton_clicked()
{
    this->hide();
    //this->view->has_quitted = true;
    mainwindow->show();
    playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}

void Finished::on_ExitButton_clicked()
{
    playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
    mainwindow->quit_button = true;
    //this->view->has_quitted = true;
}

void Finished::update_label(QString label){
    ui->teamlabel->setTextFormat(Qt::AutoText);
    ui->teamlabel->setText(QString("<font color='white', font size = '30'>") + label + QString("</font>"));
    ui->teamlabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
}
