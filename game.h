#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <chrono> 
#include <random>
#include <fstream>
#include "constants.h"
#include "player.h"
#include "door.h"
#include "bomb.h"
#include "grass.h"
#include "key.h"
#include "pu.h"
#include "enemy.h"

class Game
{
private:
    void initial();
    void processEvents(sf::Time deltaTime);
    void update(sf::Time deltaTime);
    void render();
    Door door;
    std::chrono::time_point<std::chrono::system_clock> startTime;
    int gameTimer;
    int revealedKeys;
    Bomb tmpBomb;
    sf::RenderWindow window;
    Player player;
    std::vector<Bomb> bombs;
    Grass grass;
    std::vector<std::vector<char>> map;
    Key tmpKey;
    std::vector<Key> keys;
    PowerUp tmpPU;
    std::vector<PowerUp> PUs;
    std::vector<std::vector<char>> keysMap;
    int finished = false;
    Enemy tmpEnemy;
    std::vector<Enemy> enemies;
    sf::Time timer;
    bool obstacleCollision;
    sf::Clock clock;
    sf::Time timePassed;
    std::vector<std::vector<int>> tookenPositions;
    int revealedPUs;
public:
    Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game"){revealedKeys = 0; revealedPUs = 0;};
    void removeCollectedKeys();
    void removePU();
    void removeEnemy();
    void doublePlayerSpeed();
    void handleKeyreveal();
    void handlePUReveal();
    void removeSoftObstaclesAroundBomb(const sf::Vector2f& bombPosition);
    void placeKey();
    void placePU();
    void removeExpiredBombs();
    void drawTexture();
    void EndGame();
    void Win();
    void run();
    void handleEnemyMovement(Enemy& enemy);
    void handlePlayerMovement(sf::Time deltaTime);
    void handleBombPlacement();
    void readMapFile(const std::string& filename);
    void drawInfoBoard();
    float PLAYER_SPEED;
};

#endif