#ifndef BOMBER_H
#define BOMBER_H

#include "sprite.h"

class Bomber : public Sprite
{
public:

    class Bomb : public Sprite
    {
    public:
        Bomb(int, int);
        virtual ~Bomb();

        virtual void move();
    };

public:
    Bomber(int, int);
    virtual ~Bomber();

    virtual void move();
};

#endif // BOMBER_H
