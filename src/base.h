#ifndef BASE_H
#define BASE_H

#include "sprite.h"

class Base : public Sprite
{
public:
    Base(int, int);
    virtual ~Base();

    virtual void move();
};

#endif // BASE_H
