#ifndef BOMB_H
#define BOMB_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Bomb {
public:
    Bomb();
    
    void loadTexture();
    void update(sf::Time deltaTime);
    sf::Vector2f getPosition();
    bool remove();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);

private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Texture explosionTexture;
    bool isExploded;
    bool shouldRemove;
    float bombTimer;
    float explosionTimer;
};


#endif