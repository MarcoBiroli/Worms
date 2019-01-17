#include "music.h"


void Music::backgroundmusic(QString path){
    QUrl url = QUrl(path);
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(url);
    music->setVolume(25);
    music->play();

}

void Music::playsound(QString path){
    QUrl url = QUrl(path);
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(url);
    music->setVolume(100);
    music->play();
}

void Music::randomsound(){
    int val;

    val = rand() % 4 + 1;

    if (val == 1){playsound("qrc:/SoundEffect/Pain-SoundBible.com-1883168362.wav");}
    if (val == 2){playsound("qrc:/SoundEffect/Cry+2.wav");}
    if (val == 3){playsound("qrc:/SoundEffect/Yawn+1.wav");}
    if (val == 4){playsound("qrc:/SoundEffect/Cough2.wav");}
}

void Music::stopmus(){
    music->stop();
}


void Music::pausemusic(){
    music->pause();
}

void Music::playmusic(){
    music->play();
}

void Music::infinitemusic(QList<QString> list){
    playlist = new QMediaPlaylist();



    for (int i = 0; i < list.size(); ++i) {
        QUrl url = QUrl(list.at(i));
        playlist->addMedia(url);
    }
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    musicinf = new QMediaPlayer();
    musicinf->setPlaylist(playlist);
    musicinf->play();
}

void randomshuffle(QList<QString> list){
    int size = list.length();
    int i;
    int j;
    for (int x = 0; x < size; ++x){
        i = rand() % size + 1;
        j = rand() % size + 1;
        while (i == j){
            i = rand() % size + 1;
            j = rand() % size + 1;
        }
        list.swap(i,j);
    }
}
