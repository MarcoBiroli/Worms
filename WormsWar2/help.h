#pragma once

#ifndef HELP_H
#define HELP_H

#include <QMainWindow>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class Help;
}

class Help : public QMainWindow
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    ~Help();
    MainWindow *mainwindow;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Help *ui;
};

#endif // HELP_H
