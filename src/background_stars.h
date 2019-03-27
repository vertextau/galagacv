#ifndef BACKGROUND_STARS_H
#define BACKGROUND_STARS_H

#include "sprite.h"

class BackgroundStars : public Sprite
{
    int speed;

public:
    BackgroundStars(int, int, int, int);
    virtual ~BackgroundStars();

    virtual void move();
};

#endif // BACKGROUND_STARS_H
