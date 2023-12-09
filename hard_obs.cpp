#include "hard_obs.h"
#include "constants.h"

HardObstacle::HardObstacle()
{
    shape.setSize(sf::Vector2f(HARD_OBS_SIZE, HARD_OBS_SIZE));
    loadTexture();
}

void HardObstacle::loadTexture()
{
    texture.loadFromFile(HARD_OBS_TEXTURE);
    shape.setTexture(&texture);
}

void HardObstacle::draw(sf::RenderWindow& window) { window.draw(shape); }

void HardObstacle::setPosition(sf::Vector2f position) { shape.setPosition(position); }