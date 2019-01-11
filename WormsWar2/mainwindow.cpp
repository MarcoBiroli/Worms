#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "help_menu.h"

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

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    this->start_game = true;
}

void MainWindow::on_Help_clicked()
{
   helpmenu->show();
}
