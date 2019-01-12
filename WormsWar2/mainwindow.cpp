#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Easy_clicked()
{
    this->hide();
    this->start_easy = true;

}
void MainWindow::on_Medium_clicked()
{
    this->hide();
    this->start_medium = true;
}

void MainWindow::on_Hard_clicked()
{
    this->hide();
    this->start_hard = true;
}

void MainWindow::on_Help_clicked()
{
    this->hide();
    helpmenu->show();
}

void MainWindow::on_Settings_clicked()
{
    this->hide();
    settingmenu->show();
}


void MainWindow::on_quitButton_clicked()
{
    this->quit_button = true;
}
