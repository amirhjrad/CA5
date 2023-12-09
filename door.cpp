#include "door.h"
#include "constants.h"

Door::Door()
{
    shape.setSize(sf::Vector2f(DOOR_SIZE, DOOR_SIZE));
    loadTexture();
}

void Door::loadTexture()
{
    texture.loadFromFile(DOOR_TEXTURE);
    shape.setTexture(&texture);
}

void Door::draw(sf::RenderWindow& window) { window.draw(shape); }

void Door::setPosition(sf::Vector2f position) { shape.setPosition(position); }

sf::Vector2f Door::getPosition() { return shape.getPosition(); }