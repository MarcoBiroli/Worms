#ifndef WEAPON_MENU_H
#define WEAPON_MENU_H

#include <QWidget>
#include "../Core/worms.h"
#include "../GUI/music.h"

/*Weapons menu contains the weapons of the game. There are 12 weapons which are of type:
   1. Hand-to-Hand (firepunch or bat)
   2. Airweapons (Airstrikes or MonsterBomb)
   3. Normal Projectiles (Bombs or Bullets) */

namespace Ui {
class weapon_menu;
}

class weapon_menu : public QWidget
{
    Q_OBJECT

public:
    explicit weapon_menu(QWidget *parent = nullptr);
    ~weapon_menu();
    Worm *active_worm;

private slots:
    void on_BazookaButton_clicked();

    void on_BlueGrenadeButton_clicked();

    void on_GrenadeBotton_clicked();

    void on_DynamiteBotton_clicked();

    void on_GunBotton_clicked();

    void on_AirstrikeButton_clicked();

    void on_MeteorButton_clicked();

    void on_BatButton_clicked();

    void on_MonsterbombButton_clicked();

    void on_firepunchButton_clicked();

    void on_holyButton_clicked();

    void on_BananaButton_clicked();

private:
    Ui::weapon_menu *ui;
};

#endif // WEAPON_MENU_H
