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

//Methods
void Finished::on_mainmenuButton_clicked()
{
    this->hide();
    mainwindow->show();

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}

void Finished::on_ExitButton_clicked()
{
    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");

    mainwindow->quit_button = true;
}

//Update the label which will display the winning team of "Tie"
void Finished::update_label(QString label){
    ui->teamlabel->setTextFormat(Qt::AutoText);
    ui->teamlabel->setText(QString("<font color='white', font size = '30'>") + label + QString("</font>"));
    ui->teamlabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
}
