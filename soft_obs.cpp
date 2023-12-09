#include "soft_obs.h"
#include "constants.h"

SoftObstacle::SoftObstacle()
{
    shape.setSize(sf::Vector2f(SOFT_OBS_SIZE, SOFT_OBS_SIZE));
    loadTexture();
}

void SoftObstacle::loadTexture()
{
    texture.loadFromFile(SOFT_OBS_TEXTURE);
    shape.setTexture(&texture);
}

void SoftObstacle::draw(sf::RenderWindow& window) { window.draw(shape); }

void SoftObstacle::setPosition(sf::Vector2f position) { shape.setPosition(position); }