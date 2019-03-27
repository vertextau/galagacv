#include "sprite.h"

Sprite::Sprite(int x, int y) : x(x), y(y)
{
    visible = true;
    dx = 0;
    dy = 0;
}

void Sprite::load_sprite(QString path)
{
    sprite.load(path);
}

const QImage& Sprite::get_sprite() const
{
    return sprite;
}

QRect Sprite::get_shape() const
{
    return shape;
}

void Sprite::set_dx(int x_speed)
{
    dx = x_speed;
}

void Sprite::set_dy(int y_speed)
{
    dy = y_speed;
}

int Sprite::get_dx() const
{
    return dx;
}

int Sprite::get_dy() const
{
    return dy;
}

int Sprite::get_x() const
{
    return shape.x();
}

int Sprite::get_y() const
{
    return shape.y();
}

bool Sprite::is_collide(const Sprite *object) const
{
    return shape.intersects(object->get_shape());
}

bool Sprite::is_visible() const
{
    return this->visible;
}

void Sprite::set_visible(bool visible)
{
    this->visible = visible;
}

void Sprite::reset_position(int x, int y)
{
    shape.moveTo(x, y);
}

Sprite::~Sprite() {}
