#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class SpriteSheet: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit SpriteSheet(QPixmap* sprites, QObject *parent = 0);
    QPixmap* spriteImage;

signals:

public slots:

private slots:
    void nextFrame();   // Slot for turning images into QPixmap

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QTimer *timer;      // Timer for turning images into QPixmap
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite
};

#endif // SPRITESHEET_H
