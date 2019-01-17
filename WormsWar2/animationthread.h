#ifndef ANIMATIONTHREAD_H
#define ANIMATIONTHREAD_H

#include "QObject"
#include "../GUI/water.h"
#include "QGraphicsPixmapItem"
#include "QTimer"

/*This class is the thread that will contain the water animation*/

class AnimationThread : public QObject
{
    Q_OBJECT
public:
    AnimationThread();
    ~AnimationThread();
    int width;
    int height;
    double water_height;
    QImage *getMap();
    void update(double dt){
        T += dt;
    }
    void rise(int amount);
    double  getWaveSize(){
        return water->wave_size;
    }
    QColor color =  qRgb(17, 62, 228);

public slots:
    void process();
    void emit_finished();

signals:
    void built_water();
    void finished();
    void error(QString error);
    void animated();

private:
    double T = 0;
    Water* water = NULL;
    bool is_rising = false;
};

#endif // ANIMATIONTHREAD_H
