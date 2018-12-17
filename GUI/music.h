#ifndef MUSIC_H
#define MUSIC_H

#endif // MUSIC_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QSoundEffect>



void backgroundmusic(QString path){
    QSoundEffect music;
    music.setSource(path);
    music.setLoopCount(QSoundEffect::Infinite);
    music.play();
}

void playsound(QString path){
    QSoundEffect effect;
    effect.setSource(path);
    effect.setLoopCount(1);
    effect.play();
}
