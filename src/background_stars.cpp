#include "background_stars.h"

BackgroundStars::BackgroundStars(int x, int y, int dx, int dy) : Sprite (x, y)
{
    load_sprite("resources/sprites/star.png");
    shape = sprite.rect();
    reset_position(x, y);

    this->dx = dx;
    this->dy = dy;

    speed = GameSettings::BACKGROUND_STARS_SPEED;
}

BackgroundStars::~BackgroundStars() {}

void BackgroundStars::move()
{
    shape.translate(0, speed);

    if (shape.y() >= GameSettings::GAME_WINDOW_HEIGHT)
    {
        shape.moveTo(shape.x(), 15);
    }
}
