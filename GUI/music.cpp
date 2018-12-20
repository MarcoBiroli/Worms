#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>



void backgroundmusic(QString path){
    QUrl url = QUrl(path);
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(url);
    music->setVolume(25);
    music->play();

    /*
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/backgroundmusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
    */
}

void playsound(QString path){
    QUrl url = QUrl(path);
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(url);
    music->setVolume(100);
    music->play();
}
