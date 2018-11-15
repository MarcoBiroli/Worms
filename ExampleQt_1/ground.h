#ifndef GROUND_H
#define GROUND_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QCursor>
#include <QGraphicsPixmapItem>

class Ground
{
public:
    Ground(){
        this->map = new QImage();
        item = new QGraphicsPixmapItem();
    }
    Ground(const int width, const int height){
        this->map = new QImage(width, height, QImage::Format_RGB32);
        item = new QGraphicsPixmapItem(QPixmap::fromImage(*this->map));
        this->map->fill(white);
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                if(j > 250){
                    this->map->setPixel(i, j, black);
                }
            }
        }
    }
    QGraphicsPixmapItem* getPixmap() const{
        item->setPixmap(QPixmap::fromImage(*this->map));
        return item;
    }
    QImage* getMap() const{
        return this->map;
    }
    void delete_ground(int x, int y){
        this->map->setPixel(x, y, this->white);
    }
    void circ_delete(int x, int y, double radius){
        double distance;
        for(int i = (int)(x-radius); i < (int)(x + radius); ++i){
            for(int j = (int)(y - radius); j < (int)(y + radius); ++j){
                distance = (double)(i - x)*(double)(i - x) + (double)(j - y)*(double)(j - y);
                if(distance <= radius*radius){
                    this->delete_ground(i, j);
                }
            }
        }
    }
private:
    QImage* map;
    QRgb white = qRgb(255, 255, 255);
    QRgb black = qRgb(0, 0, 0);
    QGraphicsPixmapItem *item;
};

#endif // GROUND_H
