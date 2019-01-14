#include "water.h"

Water::Water()
{
    image = new QImage();
}

Water::Water(QColor color, int width, int base_level){
    this->color = color;
    this->width = width;
    this->base_level = base_level;
    image = new QImage(width, base_level + 100, QImage::Format_ARGB32);
    image->fill(color);
    generator.SetNoiseType(FastNoise::SimplexFractal);
    for(int i = 0; i < width; i++){
        double x = (double)i*freq;
        double delta = (1 + generator.GetNoise(x,0))*wave_size/2;
        for(int j = 0; j < delta; j++){
            image->setPixel(i, j, qRgba(0, 0, 0, 0));
        }
    }
}

void Water::rise(double amount){
    if((int)(base_level + amount) - (int)base_level >= 1){
        this->base_level += amount;
        delete image;
        image = new QImage(width, base_level + 100, QImage::Format_ARGB32);
        image->fill(color);
    }
    else{
        this->base_level += amount;
    }
}

void Water::animate(double T){
    image->fill(color);
    for(int i = 0; i < width; i++){
        double x = (double)i*freq;
        double delta = (1 + generator.GetNoise(x,T/50))*wave_size;
        for(int j = 0; j < delta; j++){
            image->setPixel(i, j, qRgba(0, 0, 0, 0));
        }
    }
}
