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

//shows the mainwindow and hides the setting menu
void Settings::on_mainmenu_clicked()
{
    this->hide();
    mainwindow->show();
}

//Methods for changing the scroller value, displaying it and storing it as amo
void Settings::on_scrlnbteams_valueChanged(int value)
{
    ui->lcdNumberteam->display(value);
    numberOfTeams = value;
}

void Settings::on_scrlwormhp_valueChanged(int value)
{
    ui->lcdNumberwormhp->display(value);
    wormsLife = value;
}

void Settings::on_scrlwrmprteam_valueChanged(int value)
{
    ui->lcdNumberwormteam->display(value);
    wormperteam = value;
}


void Settings::on_scrlhealthcrates_valueChanged(int value)
{
    ui->lcdNumberhealthc->display(value);
    healthcrates = value;
}

void Settings::on_scrltimeprturn_valueChanged(int value)
{
    ui->lcdNumbertpt->display(value);
    timeprturn = value;
}

void Settings::on_scrlbazooka_valueChanged(int value)
{
    ui->lcdNumberbazooka->display(value);
    amobazooka = value;
}

void Settings::on_scrlgrenade_valueChanged(int value)
{
    ui->lcdNumbergrenade->display(value);
    amogrenade = value;
}

void Settings::on_scrlpistol_valueChanged(int value)
{
    ui->lcdNumberpistol->display(value);
    amopistol = value;
}


void Settings::on_scrairstrike_valueChanged(int value)
{
    ui->lcdNumberairstrike->display(value);
    amoairstrike = value;
}

void Settings::on_scrlbananabomb_valueChanged(int value)
{
    ui->lcdNumberbanana->display(value);
    amobanana = value;
}

void Settings::on_scrlmonster_valueChanged(int value)
{
    ui->lcdNumbermonster->display(value);
    amomonster = value;
}


void Settings::on_scrclustebomb_valueChanged(int value)
{
    ui->lcdNumbercluster->display(value);
    ammoclusterbomb = value;
}


void Settings::on_scrlholy_valueChanged(int value)
{
    ui->lcdNumberholy->display(value);
    ammoholy = value;
}

void Settings::on_scrlfirepunch_valueChanged(int value)
{
    ui->lcdNumberfirep->display(value);
    ammofirepunch = value;
}


void Settings::on_scrlarma_valueChanged(int value)
{
    ui->lcdNumberarma->display(value);
    ammoarma = value;
}

void Settings::on_scrlbat_valueChanged(int value)
{
    ui->lcdNumberbat->display(value);
    amobat = value;
}


void Settings::on_scrldynamite_valueChanged(int value)
{
    ui->lcdNumberdyn->display(value);
    ammodynamite = value;
}


void Settings::on_infinitegrenade_stateChanged(int arg1)
{
    if (ui->infinitegrenade->isChecked()){
        ui->scrlgrenade->hide();
        ui->lcdNumbergrenade->display("oo");
        amogrenade = -1;
    }
    else{
        ui->lcdNumbergrenade->display(ui->scrlgrenade->value());
        ui->scrlgrenade->show();
    }
}


void Settings::on_infinitebazooka_stateChanged(int arg1)
{
    if (ui->infinitebazooka->isChecked()){
        ui->scrlbazooka->hide();
        ui->lcdNumberbazooka->display("oo");
        amobazooka = -1;
    }
    else{
        ui->lcdNumberbazooka->display(ui->scrlbazooka->value());
        ui->scrlbazooka->show();
    }

}
