#ifndef SPRITE_H
#define SPRITE_H

#include <QImage>
#include <QRect>

#include "settings.h"

class Sprite
{
    int x, y;

protected:
    int dx, dy;
    QImage sprite;
    QRect shape;
    bool visible;
    int sprite_width, sprite_height;

protected:
    void load_sprite(QString);

public:
    Sprite(int, int);
    virtual ~Sprite();

    void reset_position(int, int);
    void set_dx(int);
    void set_dy(int);
    void set_visible(bool);

    bool is_collide(const Sprite *object) const;
    bool is_visible() const;
    int get_dx() const;
    int get_dy() const;
    int get_x() const;
    int get_y() const;

    const QImage &get_sprite() const;
    QRect get_shape() const;

    virtual void move() = 0;
};

#endif // SPRITE_H
