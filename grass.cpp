#include "grass.h"
#include "constants.h"

Grass::Grass()
{
    shape.setSize(sf::Vector2f(GRASS_SIZE, GRASS_SIZE));
    loadTexture();
}

void Grass::loadTexture()
{
    texture.loadFromFile(GRASS_TEXTURE);
    shape.setTexture(&texture);
}

void Grass::draw(sf::RenderWindow& window) { window.draw(shape); }

void Grass::setPosition(sf::Vector2f position) { shape.setPosition(position); }