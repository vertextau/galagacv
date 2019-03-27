#include <iostream>
#include <algorithm>

#include <QFontDatabase>
#include <QPainter>
#include <QApplication>

#include "game_board.h"
#include "settings.h"

GameBoard::GameBoard(QWidget *parent) : QWidget(parent)
{
    game_over = false;
    paused = false;
    game_started = false;
    camera_on = false;

    this->parent = parent;

    current_score = GameSettings::CURRENT_SCORE;

    // Init base
    base = new Base(0, GameSettings::GAME_WINDOW_HEIGHT-20);

    // Init spaceship
    spaceship = new Spaceship(GameSettings::SPACESHIP_POSITION, GameSettings::GAME_WINDOW_HEIGHT-60);

    // Init bombers
    for (int j_x = 0; j_x < 5; ++j_x)
    {
        bombers[j_x] = new Bomber(30 + 70*(j_x+1), 40);
    }

    // Init spacebugs
    for (int j_y = 0; j_y < 2; ++j_y)
    {
        for (int j_x = 0; j_x < 8; ++j_x)
        {
            bugs_pool.emplace_back(new Spacebug(-30 - j_x*45, 85 + j_y*45));
        }
    }

    // Create background stars
    for (int i = 0; i < 30; ++i)
    {
        stars[i] = new BackgroundStars(rand()%480,rand()%480,rand()%40,rand()%40);
    }
}

GameBoard::~GameBoard()
{
    delete spaceship;

    delete camera;

    for (int i = 0; i < 30; ++i)
    {
        delete stars[i];
    }

    for (int i = 0; i < 5; ++i)
    {
        delete bombers[i];
    }
}

void GameBoard::start_same()
{
    if (!game_started)
    {
        if (camera_on)
        {
            camera = new CameraController(camera_id);
            connect(&cam_ctrl_thread, &QThread::started, camera, &CameraController::run);
            connect(camera, SIGNAL(finished()), &cam_ctrl_thread, SLOT(quit()));
            camera->moveToThread(&cam_ctrl_thread);
            cam_ctrl_thread.start();
        }

        spaceship->reset_position(GameSettings::SPACESHIP_POSITION, GameSettings::GAME_WINDOW_HEIGHT-60);

        game_over = false;
        game_started = true;
        timer_id = startTimer(GameSettings::GAME_DELAY);
        bugs_spawn_timer = startTimer(GameSettings::BUGS_SPAWN_DELAY);
    }
}

void GameBoard::pause_game()
{
    if (paused)
    {
        timer_id = startTimer(GameSettings::GAME_DELAY);
        bugs_spawn_timer = startTimer(GameSettings::BUGS_SPAWN_DELAY);
        paused = false;
    }
    else
    {
        if (game_started)
        {
            killTimer(timer_id);
            killTimer(bugs_spawn_timer);
            paused = true;
        }
    }
}

void GameBoard::stop_game()
{
    killTimer(timer_id);
    killTimer(bugs_spawn_timer);
    cam_ctrl_thread.terminate();

    game_over = true;
    game_started = false;
}

void GameBoard::draw_message(QPainter *painter, QString message)
{
    QFont font("Helvetica", 9);

    painter->setFont(font);
    painter->setPen(QPen(Qt::white));

    painter->drawText(GameSettings::GAME_WINDOW_WIDTH/2, GameSettings::GAME_WINDOW_HEIGHT/2, message);
}

void GameBoard::game_info(QPainter *painter)
{
    QFont game_font("Helvetica", 9);
    painter->setFont(game_font);
    painter->setPen(QPen(Qt::white));

    painter->drawText(GameSettings::GAME_WINDOW_WIDTH/6, 15, "Score: " + QString::number(current_score));
    painter->drawText(GameSettings::GAME_WINDOW_WIDTH*3/4, 15, "Lives: " + QString::number(spaceship->get_lives()));
}

void GameBoard::draw_objects(QPainter *painter)
{
    game_info(painter);

    // Draw space base
    painter->drawImage(base->get_shape(), base->get_sprite());

    // Draw spaceship
    painter->drawImage(spaceship->get_shape(), spaceship->get_sprite());

    /*
     * Draw bullets, bugs, rockets, bombs
     */
    for (auto &el : pools_manager)
    {
        for (auto &it : *el)
        {
            if (it->is_visible())
            {
                painter->drawImage(it->get_shape(), it->get_sprite());
            }
        }
    }

    // Draw background starts
    for (auto &el : stars)
    {
        painter->drawImage(el->get_shape(), el->get_sprite());
    }

    // Draw bombers
    for (auto &el : bombers)
    {
        painter->drawImage(el->get_shape(), el->get_sprite());
    }
}

void GameBoard::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);

    if (game_over)
    {
        draw_message(&painter, "Game over");
        pause_game();
    }
    else
    {
        draw_objects(&painter);
    }
}

void GameBoard::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == timer_id)
    {
        generate_objects();
        move_objects();
        collect_garbage();

        if (spaceship->get_lives() <= 0 || current_score < 0)
        {
            game_over = true;
        }

        repaint();
    }

    // Generate new row of bugs
    if (e->timerId() == bugs_spawn_timer)
    {
        new_bugs_wave();
    }
}

void GameBoard::collect_garbage()
{
    // Collect invisible objects
    for (auto el : pools_manager)
    {
        el->erase(std::remove_if(el->begin(),
                                el->end(),
                                [](std::unique_ptr<Sprite> &item){ return !item->is_visible(); }),
                el->end());
    }
}

void GameBoard::generate_objects()
{
    // For each bug generate randomly rocket object
    for (auto &el : bugs_pool)
    {
        if (rand() % GameSettings::BUG_ROCKET_CHANCE == 3)
        {
            int dx;
            int diff = spaceship->get_x() - el->get_x();

            if (diff > 0)
            {
                dx = GameSettings::SPACEBUG_ROCKET_SPEED_X;
            }
            else if (diff < 0)
            {
                dx = - GameSettings::SPACEBUG_ROCKET_SPEED_X;
            }
            else
            {
                dx = 0;
            }

            rockets_pool.emplace_back(new Spacebug::Rocket(el->get_shape().x()+15, el->get_shape().y()+30, dx));
        }
    }

    // Generate randomly bomb object for each bomber
    for (auto &el : bombers)
    {
        if (rand() % GameSettings::BOMBER_BOMB_CHANCE == 3)
        {
            bombs_pool.emplace_back(new Bomber::Bomb(el->get_x()+15, el->get_y()+30));
        }
    }
}

void GameBoard::move_objects()
{
    /*
     * Background stars
     */
    for (int i = 0; i < 30; ++i)
    {
        stars[i]->move();
    }

    /*
     * Spaceship
     */
    if (camera_on)
    {
        int x = camera->get_position();

        if (x > 0 && x < GameSettings::GAME_WINDOW_WIDTH - 30)
        {
            spaceship->reset_position(x, spaceship->get_y());
        }
    }
    else
    {
        spaceship->move();
    }

    /*
     * Bugs
     */
    for (auto &el : bugs_pool)
    {
        int bug_x = el->get_x() + el->get_dx();

        if (bug_x <= 0)
        {
            el->set_dx(GameSettings::SPACEBUG_SPEED);
        }
        else if (bug_x >= GameSettings::GAME_WINDOW_WIDTH - 30)
        {
            el->set_dx(-GameSettings::SPACEBUG_SPEED);
        }

        el->move();
    }

    /*
     * Bullets
     */
    for (auto &el: bullets_pool)
    {
        el->move();

        for (auto &bug : bugs_pool)
        {
            if (el->is_collide(bug.get()) && bug->is_visible())
            {
                el->set_visible(false);
                bug->set_visible(false);
                current_score += GameSettings::SCORE_BUG_REWARD;
            }
        }

        for (auto &bomb : bombs_pool)
        {
            if (el->is_collide(bomb.get()) && bomb->is_visible())
            {
                el->set_visible(false);
                bomb->set_visible(false);
                current_score += GameSettings::SCORE_BOMB_REWARD;
            }
        }

        for (auto &bomber : bombers)
        {
            if (el->is_collide(bomber))
            {
                el->set_visible(false);
            }
        }
    }

    /*
     * Bug's rockets
     */
    for (auto &el: rockets_pool)
    {
        el->move();

        if (el->is_collide(spaceship))
        {
            el->set_visible(false);
            spaceship->decrease_lives();
        }
    }

    /*
     * Bomber's bombs
     */
    for (auto &el: bombs_pool)
    {
        el->move();

        if (el->is_collide(spaceship))
        {
            el->set_visible(false);
            spaceship->decrease_lives();
        }

        if (el->is_collide(base))
        {
            el->set_visible(false);
            current_score += GameSettings::SCORE_BOMB_DAMAGE;
        }
    }
}

void GameBoard::new_bugs_wave()
{
    // Shift old rows down
    for (auto &el : bugs_pool)
    {
        el->reset_position(el->get_x(), el->get_y() + el->get_shape().height()+15);

    }

    // Generate new row and place it beyond screen
    for (int j_x = 0; j_x < 8; ++j_x)
    {
        bugs_pool.emplace_back(new Spacebug(-15 - 45*j_x, 85));
    }
}

void GameBoard::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Right:
        spaceship->set_dx(0);
        break;

    case Qt::Key_Left:
        spaceship->set_dx(0);
        break;

    case Qt::Key_P:
        pause_game();
        break;
    }
}

void GameBoard::keyPressEvent(QKeyEvent *e)
{
    int dx;

    switch (e->key())
    {
    case Qt::Key_Right:
        dx = GameSettings::SPACESHIP_SPEED;
        spaceship->set_dx(dx);
        break;

    case Qt::Key_Left:
        dx = -GameSettings::SPACESHIP_SPEED;
        spaceship->set_dx(dx);
        break;

    case Qt::Key_F:
        bullets_pool.emplace_back(new Spaceship::Bullet(spaceship->get_x()+15, spaceship->get_y()));
        break;

    case Qt::Key_Space:
        start_same();
        break;

    case Qt::Key_Escape:
        stop_game();
        std::exit(0);

    default:
        QWidget::keyPressEvent(e);
    }
}

void GameBoard::set_camera_on(bool flag)
{
    camera_on = flag;
}

void GameBoard::set_camera(CameraInitializer *camera_id)
{
    this->camera_id = camera_id;
}
