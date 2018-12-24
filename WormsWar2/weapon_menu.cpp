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

void weapon_menu::on_BazookaButton_clicked()
{
    this->active_worm->weaponSelect(0);
}

void weapon_menu::on_BlueGrenadeButton_clicked()
{
    this->active_worm->weaponSelect(1);
}

void weapon_menu::on_GrenadeBotton_clicked()
{
    this->active_worm->weaponSelect(2);
}

void weapon_menu::on_DynamiteBotton_clicked()
{
    this->active_worm->weaponSelect(3);
}

void weapon_menu::on_GunBotton_clicked()
{
    this->active_worm->weaponSelect(4);
}

void weapon_menu::on_AirstrikeButton_clicked()
{

}

void weapon_menu::on_MeteorButton_clicked()
{

}

void weapon_menu::on_MagnetButton_clicked()
{

}

void weapon_menu::on_MineButton_clicked()
{

}

void weapon_menu::on_MissileButton_clicked()
{

}

void weapon_menu::on_BatButton_clicked()
{

}

void weapon_menu::on_MonsterbombButton_clicked()
{

}
