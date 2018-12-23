#include "weapon_menu.h"
#include "ui_weapon_menu.h"

weapon_menu::weapon_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::weapon_menu)
{
    ui->setupUi(this);
}

weapon_menu::~weapon_menu()
{
    delete ui;
}

void weapon_menu::on_GrenadeButton_clicked()
{
    this->active_worm->weaponSelect(1);
}

void weapon_menu::on_BazookaButton_clicked()
{
    this->active_worm->weaponSelect(0);
}
