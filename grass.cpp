#include "grass.h"

Grass::Grass()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    loadTexture();
}

void Grass::loadTexture()
{
    texture.loadFromFile("assets/grass.png");
    shape.setTexture(&texture);
}

void Grass::draw(sf::RenderWindow& window) { window.draw(shape); }

void Grass::setPosition(sf::Vector2f position) { shape.setPosition(position); }