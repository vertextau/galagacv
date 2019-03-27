#ifndef SETTINGS_H
#define SETTINGS_H

namespace GameSettings
{
const static int GAME_WINDOW_WIDTH  = 500;
const static int GAME_WINDOW_HEIGHT = 600;

const static int GAME_FPS = 100;
const static int GAME_DELAY = 1000/GAME_FPS;
const static int BUGS_SPAWN_DELAY = 10000;

const static int SPACESHIP_LIVES = 3;

const static int SPACESHIP_POSITION = GAME_WINDOW_WIDTH/2;
const static int SPACESHIP_SPEED = 2;
const static int SPACESHIP_BULLET_SPEED = 2;
const static int SPACEBUG_SPEED = 1;
const static int SPACEBUG_ROCKET_SPEED_Y = 2;
const static int SPACEBUG_ROCKET_SPEED_X = 1;
const static int BOMBER_BOMB_SPEED = 1;
const static int BACKGROUND_STARS_SPEED = 4;

const static int BOMBER_BOMB_CHANCE = 1000;
const static int BUG_ROCKET_CHANCE = 700;

const static int CURRENT_SCORE = 100;
const static int SCORE_BUG_REWARD = 5;
const static int SCORE_BOMB_REWARD = 10;
const static int SCORE_BOMB_DAMAGE = -20;
};

#endif // SETTINGS_H
