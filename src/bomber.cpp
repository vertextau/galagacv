#include "bomber.h"

Bomber::Bomber(int x, int y) : Sprite (x, y)
{
    load_sprite("resources/sprites/bomber.png");
    shape = sprite.rect();

    reset_position(x, y);

    sprite_width = shape.width();
    sprite_height = shape.height();
}

Bomber::~Bomber() {}

void Bomber::move() {}

Bomber::Bomb::Bomb(int x, int y) : Sprite (x, y)
{
    load_sprite("resources/sprites/bomb.png");
    shape = sprite.rect();

    reset_position(x, y);

    dy = GameSettings::BOMBER_BOMB_SPEED;

    sprite_width = shape.width();
    sprite_height = shape.height();
}

Bomber::Bomb::~Bomb() {}

void Bomber::Bomb::move()
{
    shape.translate(0, dy);
}
