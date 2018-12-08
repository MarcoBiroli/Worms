#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T13:59:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WormsWar2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        ../Physics/Collider.cpp \
        ../Physics/PhysicsEngine.cpp \
        ../Physics/RigidBody.cpp \
        #../Core/Game.cpp \
       # ../Core/Projectile.cpp \
        #../Core/worms.cpp \
        ../GUI/ground.cpp \
    ../GUI/customview.cpp \
    ../GUI/dummy.cpp

HEADERS += \
        ../Physics/Collider.h \
        ../Physics/PhysicsEngine.h \
        ../Physics/RigidBody.h \
        ../GUI/customview.h \
        ../GUI/ground.h \
        ../Core/Game.h \
        ../Core/Projectile.h \
        ../Core/worms.h

FORMS += \
        mainwindow.ui
