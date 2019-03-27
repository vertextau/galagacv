#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "sprite.h"

class Spaceship : public Sprite
{
public:

    class Bullet : public Sprite
    {
    public:
        Bullet(int, int);
        virtual ~Bullet();

        virtual void move();
    };

private:
    int lives;

public:
    Spaceship(int, int);
    virtual ~Spaceship();

    virtual void move();

    int get_lives();
    void reset_lives();
    void decrease_lives();
    void increase_lives();
};

#endif // SPACESHIP_H
