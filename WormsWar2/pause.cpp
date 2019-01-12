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


void Pause::on_mainButton_clicked()
{
    this->hide();
    this->view->has_quitted = true;
    playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}

void Pause::on_exitButton_clicked()
{
    playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
    MainWindow->quit_button = true;
    this->view->has_quitted = true;
}