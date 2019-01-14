#ifndef MUSIC_H
#define MUSIC_H

// MUSIC_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QSound>
#include <QMediaPlayer>

class Music{
public:
    QUrl url;
    QMediaPlayer * music;

void backgroundmusic(QString path);

void playsound(QString path);

void randomsound();

void stopmus();
};
#endif
