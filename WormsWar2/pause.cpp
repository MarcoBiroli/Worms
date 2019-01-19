#include "pause.h"
#include "ui_pause.h"

Pause::Pause(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pause)
{
    ui->setupUi(this);
}

Pause::~Pause()
{
    delete ui;
}

//Methods
void Pause::on_mainButton_clicked()
{
    this->hide();
    this->view->has_quitted = true;

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
    //Parameter will be used in the main.cpp to say that u have exited the game loop through ESCAPE
    Mainwindow->through_esc = true;
}

void Pause::on_exitButton_clicked()
{
    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");

    Mainwindow->quit_button = true;
    this->view->has_quitted = true;
}
