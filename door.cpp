#include "door.h"


Door::Door()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    loadTexture();
}

void Door::loadTexture()
{
    texture.loadFromFile("assets/door.png");
    shape.setTexture(&texture);
}

void Door::draw(sf::RenderWindow& window) { window.draw(shape); }

void Door::setPosition(sf::Vector2f position) { shape.setPosition(position); }

sf::Vector2f Door::getPosition() { return shape.getPosition(); }