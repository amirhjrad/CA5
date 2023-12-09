#include "hard_obs.h"

HardObstacle::HardObstacle()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    loadTexture();
}

void HardObstacle::loadTexture()
{
    texture.loadFromFile("assets/wall-2.png");
    shape.setTexture(&texture);
}

void HardObstacle::draw(sf::RenderWindow& window) { window.draw(shape); }

void HardObstacle::setPosition(sf::Vector2f position) { shape.setPosition(position); }