#ifndef CONSTANST_H
#define CONSTANST_H
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float ENEMY_SPEED = 5.0f;
const float BOMB_TIMER_DURATION = 2.0f;
const float EXPLOSION_TIMER_DURATION = 0.5f; 
const std::string BOMB_TEXTURE = "assets/bomb.png";
const std::string EXP_TEXTURE = "assets/explosion.png";
const int BOMB_SIZE = 50;
const int INIT_TIMER = 0;
const std::string DOOR_TEXTURE = "assets/door.png";
const int DOOR_SIZE = 50;
const std::string ENEMY_TEXTURE = "assets/enemy.png";
const int ENEMY_SIZE = 50;
const float ENEMY_PROBABILITY = 0.5;
const std::string GRASS_TEXTURE = "assets/grass.png";
const int GRASS_SIZE = 50;
const std::string HARD_OBS_TEXTURE = "assets/wall-2.png";
const int HARD_OBS_SIZE = 50;
const std::string KEYS_TEXTURE = "assets/key.png";
const int KEYS_SIZE = 50;
const std::string RIGHT = "Right";
const std::string LEFT = "Left";
const std::string UP = "Up";
const std::string DOWN = "Down";
const std::string RIGHT_TEXTURE = "assets/boy/right.png";
const std::string LEFT_TEXTURE = "assets/boy/left.png";
const std::string UP_TEXTURE = "assets/boy/up.png";
const std::string DOWN_TEXTURE = "assets/boy/down.png";
const int PLAYER_SIZE = 50;
const int INIT_BOMBS = 0;
const int INIT_KEYS = 0;
const int INIT_LIVES = 2;
const int TOLERANCE = 30;
const std::string PULife_TEXTURE = "assets/life.png";
const std::string PUSPEED_TEXTURE = "assets/speed2.png";
const int PU_SIZE = 50;
const std::string SOFT_OBS_TEXTURE = "assets/wall-1.png";
const int SOFT_OBS_SIZE = 50;
const int NUM_OF_KEY = 3;
const int NUM_OF_PU = 2;
const char NOTHING = ' ';
const char REAL_DOOR = 'd';
const char IM_DOOR = 'D';
const char SOFT_OBS = 'B';
const char HARD_OBS = 'P';
const char VERTICAL_ENEMY = 'V';
const char HORIZONTAL_ENEMY = 'H';
const std::string FONT_DIR = "assets/fonts/arial.ttf";
const int TIME_FINISHED = -1;
const std::string TIME_FINISHED_LABEL = "Time is finished";
const std::string LIFE_FINISHED_LABEL = "Life is finished";
const std::string WIN_LABEL = "You Won!";
const int FONT_SIZE = 24;
const int MAX_BOMB = 3;
const std::string MAP_DIR = "map.txt";
const std::string TIMER_LABEL = "Timer: ";
const std::string LIVES_LABEL = "Lives: ";
const std::string KEYS_LABEL = "Keys: ";


#endif