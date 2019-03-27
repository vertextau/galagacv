#include "spaceship.h"

Spaceship::Spaceship(int x, int y) : Sprite (x, y)
{
    load_sprite("resources/sprites/spaceship.png");

    shape = sprite.rect();
    reset_position(x, y);

    sprite_width = shape.width();
    sprite_height = shape.height();

    reset_lives();
}

Spaceship::~Spaceship() {}

void Spaceship::move()
{
    int x_shift = this->get_x() + dx;

    if (x_shift > 0 && x_shift < GameSettings::GAME_WINDOW_WIDTH-this->sprite_width)
    {
        shape.translate(dx, 0);
    }
}

int Spaceship::get_lives()
{
    return lives;
}

void Spaceship::reset_lives()
{
    lives = GameSettings::SPACESHIP_LIVES;
}

void Spaceship::decrease_lives()
{
    --lives;
}

void Spaceship::increase_lives()
{
    ++lives;
}

Spaceship::Bullet::Bullet(int x, int y) : Sprite (x, y)
{
    load_sprite("resources/sprites/bullet.png");
    shape = sprite.rect();

    reset_position(x, y);

    sprite_width = shape.width();
    sprite_height = shape.height();

    dy = - GameSettings::SPACESHIP_BULLET_SPEED;
}

Spaceship::Bullet::~Bullet() {}

void Spaceship::Bullet::move()
{
    shape.translate(0, dy);

    if (get_y() < 0)
    {
        set_visible(false);
    }
}
