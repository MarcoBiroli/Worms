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
    music->play();
}

void playsound(QString path){
}
