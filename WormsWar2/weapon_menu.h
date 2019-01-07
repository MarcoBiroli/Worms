#ifndef WEAPON_MENU_H
#define WEAPON_MENU_H

#include <QWidget>
#include "../Core/worms.h"

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

    void on_MagnetButton_clicked();

    void on_MineButton_clicked();

    void on_MissileButton_clicked();

    void on_BatButton_clicked();

    void on_MonsterbombButton_clicked();

private:
    Ui::weapon_menu *ui;
};

#endif // WEAPON_MENU_H
