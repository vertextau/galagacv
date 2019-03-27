#include "spacebug.h"
#include <iostream>

Spacebug::Spacebug(int x, int y) : Sprite (x, y)
{
    load_sprite("resources/sprites/bug.png");

    shape = sprite.rect();
    reset_position(x, y);

    sprite_width = shape.width();
    sprite_height = shape.height();

    is_spawn = true;

    dx = GameSettings::SPACEBUG_SPEED;
}

Spacebug::~Spacebug() {}

void Spacebug::move()
{
    if (is_spawn)
    {
        if (get_x() >= GameSettings::GAME_WINDOW_WIDTH - sprite_width)
        {
            is_spawn = false;
        }

        shape.translate(1, 0);
    }
    else
    {
        shape.translate(dx, 0);
    }

}

Spacebug::Rocket::Rocket(int x, int y, int dx) : Sprite (x, y)
{
    if (dx < 0)
    {
        load_sprite("resources/sprites/rocket_left.png");
    }
    else if (dx > 0)
    {
        load_sprite("resources/sprites/rocket_right.png");
    }
    else
    {
        load_sprite("resources/sprites/rocket.png");
    }

    shape = sprite.rect();
    reset_position(x, y);

    sprite_width = shape.width();
    sprite_height = shape.height();

    dy = GameSettings::SPACEBUG_ROCKET_SPEED_Y;
    this->dx = dx;
}

Spacebug::Rocket::~Rocket() {}

void Spacebug::Rocket::move()
{
    shape.translate(dx, dy);

    if (get_y() > GameSettings::GAME_WINDOW_HEIGHT || get_x() <= 0 || get_x() > GameSettings::GAME_WINDOW_WIDTH)
    {
        set_visible(false);
    }
}
