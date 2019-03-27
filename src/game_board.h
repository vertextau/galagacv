#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QThread>

#include "background_stars.h"
#include "spaceship.h"
#include "spacebug.h"
#include "bomber.h"
#include "camera_controller.h"
#include "base.h"
#include "settings.h"

class GameBoard : public QWidget
{

public:
    GameBoard(QWidget *parent = nullptr);
    ~GameBoard();
    void set_camera_on(bool);
    void set_camera(CameraInitializer *);

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void draw_objects(QPainter *);
    void draw_message(QPainter *, QString);
    void game_info(QPainter *);
    void move_objects();
    void generate_objects();
    void collect_garbage();
    void new_bugs_wave();

    void start_same();
    void pause_game();
    void stop_game();
    void camera_init();
    void init_world();

private:
    QWidget *parent;
    int timer_id;
    int bugs_spawn_timer;

    BackgroundStars *stars[30];
    Spaceship *spaceship;
    Bomber *bombers[5];
    Base *base;

    std::vector<std::unique_ptr<Sprite>> bullets_pool, bugs_pool, rockets_pool, bombs_pool;

    std::array<std::vector<std::unique_ptr<Sprite>> *, 4> pools_manager = {&bullets_pool,
                                                                           &rockets_pool,
                                                                           &bugs_pool,
                                                                           &bombs_pool};

    bool game_over, game_started, paused, camera_on;

    CameraController *camera;
    QThread cam_ctrl_thread;
    CameraInitializer *camera_id;

    int current_score;
};

#endif // GAME_BOARD_H
