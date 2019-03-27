#include "base.h"

Base::Base(int x, int y) : Sprite (x, y)
{
    load_sprite("resources/sprites/base.png");

    shape = sprite.rect();
    reset_position(x, y);
}

Base::~Base() {}

void Base::move() {}
