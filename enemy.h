#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "bomb.h"
class Bomb;
class Enemy
{
public:
    Enemy();

    void loadTexture();
    void move(sf::Vector2f& movement);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    bool isRemovable();
    void shouldRemove();
    bool enemyOnBomb(Bomb tmpBomb);
    sf::FloatRect getBounds();
    bool isVertical;
    bool upOrRight;
    bool recentlyHitPlayer;
    int direction;
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    bool remove;
};

#endif