#include "help_menu.h"
#include "ui_help_menu.h"

#include <QMainWindow>


help_menu::help_menu(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::help_menu)
{
    ui->setupUi(this);
}

help_menu::~help_menu()
{
    delete ui;
}
