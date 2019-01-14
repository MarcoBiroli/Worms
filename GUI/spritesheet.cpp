#include "spritesheet.h"

SpriteSheet::SpriteSheet(QPixmap* sprites, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    currentFrame = 0;   // Sets the coordinates of the current frame of the sprite
    spriteImage = sprites;
    timer = new QTimer();   // Create a timer for sprite animation
    connect(timer, &QTimer::timeout, this, &SpriteSheet::nextFrame);
    timer->start(500);   // Run the sprite on the signal generation with a frequency of 25 ms
}

QRectF SpriteSheet::boundingRect() const
{
    return QRectF(500,500,300,300);
}

void SpriteSheet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    painter->drawPixmap(500,500, *spriteImage, currentFrame, 0, 300, 300);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void SpriteSheet::nextFrame()
{
    /* At a signal from the timer 20 to move the point of rendering pixels
     * If currentFrame = 300 then zero out it as sprite sheet size of 300 pixels by 20
     * */
    currentFrame += 300;
    if (currentFrame >= this->spriteImage->width() ) currentFrame = 0;
    this->update(500,500,300,300);
}
