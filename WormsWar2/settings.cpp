#include "settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_mainmenu_clicked()
{
    this->hide();
    mainwindow->show();
}


void Settings::on_scrlnbteams_valueChanged(int value)
{
    ui->showNumber->display(value);
    numberOfTeams = value;
}

void Settings::on_scrlwormhp_valueChanged(int value)
{
    ui->lcdNumberHp->display(value);
    wormsLife = value;
}

void Settings::on_scrlwrmprteam_valueChanged(int value)
{
    ui->lcdNumber->display(value);
    wormperteam = value;
}


void Settings::on_scrlhealthcrates_valueChanged(int value)
{
    ui->lcdNumber_2->display(value);
    healthcrates = value;
}

void Settings::on_scrltimeprturn_valueChanged(int value)
{
    ui->lcdNumber_3->display(value);
    timeprturn = value;
}

void Settings::on_scrlbazooka_valueChanged(int value)
{
    ui->lcdNumber_4->display(value);
    amobazooka = value;
}

void Settings::on_scrlgrenade_valueChanged(int value)
{
    ui->lcdNumber_5->display(value);
    amogrenade = value;
}

void Settings::on_scrlpistol_valueChanged(int value)
{
    ui->lcdNumber_6->display(value);
    amopistol = value;
}

void Settings::on_scrllandmine_valueChanged(int value)
{
    ui->lcdNumber_7->display(value);
    amolandmine = value;
}

void Settings::on_scrairstrike_valueChanged(int value)
{
    ui->lcdNumber_8->display(value);
    amoairstrike = value;
}

void Settings::on_scrlbananabomb_valueChanged(int value)
{
    ui->lcdNumber_9->display(value);
    amobanana = value;
}

void Settings::on_scrlmonster_valueChanged(int value)
{
    ui->lcdNumber_10->display(value);
    amomonster = value;
}


void Settings::on_scrclustebomb_valueChanged(int value)
{
    ui->lcdNumber_12->display(value);
    ammoclusterbomb = value;
}


void Settings::on_scrlholy_valueChanged(int value)
{
    ui->lcdNumber_14->display(value);
    ammoholy = value;
}

void Settings::on_scrldynamite_valueChanged(int value)
{
    ui->lcdNumber_15->display(value);
    ammodynamite = value;
}



void Settings::on_scrlfire_valueChanged(int value)
{
    ui->lcdNumber_16->display(value);
    ammofirepunch = value;
}


void Settings::on_scrlarma_valueChanged(int value)
{
    ui->lcdNumber_19->display(value);
    ammoarma = value;
}

void Settings::on_infinitegrenade_stateChanged(int arg1)
{
    if (ui->infinitegrenade->isChecked()){
        ui->scrlgrenade->hide();
        ui->lcdNumber_5->display("oo");
        amogrenade = -1;
    }
    else{
        ui->lcdNumber_5->display(ui->scrlgrenade->value());
        ui->scrlgrenade->show();
    }
}


void Settings::on_infinitebazooka_stateChanged(int arg1)
{
    if (ui->infinitebazooka->isChecked()){
        ui->scrlbazooka->hide();
        ui->lcdNumber_4->display("oo");
        amobazooka = -1;
    }
    else{
        ui->lcdNumber_4->display(ui->scrlbazooka->value());
        ui->scrlbazooka->show();
    }

}



