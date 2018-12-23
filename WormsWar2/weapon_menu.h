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
    void on_GrenadeButton_clicked();

    void on_BazookaButton_clicked();

private:
    Ui::weapon_menu *ui;
};

#endif // WEAPON_MENU_H
