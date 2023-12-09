#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "bomb.h"
#include "door.h"
#include "enemy.h"
#include "grass.h"
#include "hard_obs.h"
#include "soft_obs.h"
#include "key.h"
#include "pu.h"
#include "constants.h"
class Player
{
private:
    sf::RectangleShape shape;
    sf::Texture textureUp;
    sf::Texture textureDown;
    sf::Texture textureLeft;
    sf::Texture textureRight;
    int numOfBombs;
    int numOfCollectedKeys;
    int lives;
public:
    Player();
    void loadTexture();
    bool playerOnDoor(Door door);
    bool playerOnBomb(Bomb tmpBomb);
    bool playerOnKey(Key tmpKey);
    bool playerOnPU(PowerUp tmpPU);
    bool playerOnEnemy(Enemy tmpEnemy);
    void move(sf::Vector2f& movement);
    void setPosition(sf::Vector2f& position);
    int getNumOfBombs();
    int getLives();
    void incLive();
    void incNumOfBombs();
    void collectKey();
    int getNumOfCollectedKeys();
    void decNumOfBombs();
    void decLives();
    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
    void draw(sf::RenderWindow& window);
    void setTexture(std::string direction);
};





#endif