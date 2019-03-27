#ifndef SPACEBUG_H
#define SPACEBUG_H

#include "sprite.h"

class Spacebug : public Sprite
{
public:

    class Rocket : public Sprite
    {
    public:
        Rocket(int, int, int);
        virtual ~Rocket();

        virtual void move();
    };

private:
    bool is_spawn;

public:
    Spacebug(int, int);
    virtual ~Spacebug();

    virtual void move();
};

#endif // SPACEBUG_H
