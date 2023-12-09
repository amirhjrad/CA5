#ifndef GRASS_H
#define GRASS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Grass
{
public:
    Grass();
    void loadTexture();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
private:
    sf::RectangleShape shape;
    sf::Texture texture;
};

#endif