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

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}

void weapon_menu::on_BlueGrenadeButton_clicked()
{
    this->active_worm->weaponSelect(1);

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}

void weapon_menu::on_GrenadeBotton_clicked()
{
    this->active_worm->weaponSelect(2);

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}

void weapon_menu::on_DynamiteBotton_clicked()
{
    this->active_worm->weaponSelect(3);

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}

void weapon_menu::on_GunBotton_clicked()
{
    this->active_worm->weaponSelect(4);

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}

void weapon_menu::on_holyButton_clicked()
{
    this->active_worm->weaponSelect(5);

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
}


void weapon_menu::on_BananaButton_clicked()
{
    this->active_worm->weaponSelect(6);

    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");

}

void weapon_menu::on_AirstrikeButton_clicked()
{
    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
    QCursor c = cursor();
    c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
    c.setShape(Qt::ArrowCursor);
    setCursor(c);
    this->active_worm->weaponSelect(9);
    this->active_worm->amount_airweapon = 4;
}

void weapon_menu::on_MeteorButton_clicked()
{
    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
    this->active_worm->weaponSelect(11);
    this->active_worm->amount_airweapon = 50;

}


void weapon_menu::on_BatButton_clicked()
{
    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
    this->active_worm->weaponSelect(7);
}

void weapon_menu::on_MonsterbombButton_clicked()
{
    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
    this->active_worm->weaponSelect(10);
    this->active_worm->amount_airweapon = 1;
}

void weapon_menu::on_firepunchButton_clicked()
{
    Music click;
    click.playsound("qrc:/SoundEffect/Button_Push-Mike_Koenig-1659525069.wav");
    this->active_worm->weaponSelect(8);
}



