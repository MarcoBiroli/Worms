#ifndef HELP_MENU_H
#define HELP_MENU_H

#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QMainWindow>

namespace Ui {
class help_menu;
}


class help_menu : public QDialog
{
    Q_OBJECT

public:
    explicit help_menu(QDialog *parent = nullptr);
    ~help_menu();

private:
    Ui::help_menu *ui;

};

#endif // HELP_MENU_H
