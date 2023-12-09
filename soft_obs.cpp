#include "soft_obs.h"

SoftObstacle::SoftObstacle()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    loadTexture();
}

void SoftObstacle::loadTexture()
{
    texture.loadFromFile("assets/wall-1.png");
    shape.setTexture(&texture);
}

void SoftObstacle::draw(sf::RenderWindow& window) { window.draw(shape); }

void SoftObstacle::setPosition(sf::Vector2f position) { shape.setPosition(position); }