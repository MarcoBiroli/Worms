#include "animationthread.h"

AnimationThread::AnimationThread()
{
}


AnimationThread::~AnimationThread(){

}

void AnimationThread::process(){
    if(this->water == NULL){
        this->water = new Water(color, width, water_height);
        emit built_water();
    }
    this->water->rise(5*0.01);
    water_height += 5*0.01;
    water->animate(T);
    emit animated();

}

void AnimationThread::emit_finished(){
    emit finished();

}

QImage* AnimationThread::getMap(){
    return this->water->image;
}

void AnimationThread::rise(int amount){
    if(this->water == NULL){
        return;
    }
    is_rising = true;
    this->water->rise(amount);
    water_height += amount;
    is_rising = false;
    this->water->animate(T);
}
