#include "pu.h"
#include "constants.h"

PowerUp::PowerUp()
{
    shape.setSize(sf::Vector2f(PU_SIZE, PU_SIZE));
    loadTexture();
    remove = 0;
    Revealed = 0;
    tmp = 0;
}

void PowerUp::loadTexture()
{
    texture.loadFromFile(PULife_TEXTURE);
    texture2.loadFromFile(PUSPEED_TEXTURE);
    shape.setTexture(&texture);
}

void PowerUp::draw(sf::RenderWindow& window) { window.draw(shape); }

void PowerUp::setPosition(sf::Vector2f position) { shape.setPosition(position); }

sf::Vector2f PowerUp::getPosition() { return shape.getPosition(); }

bool PowerUp::isRemovable() { return remove; }

void PowerUp::shouldRemove() { remove = true; }

bool PowerUp::isRevealed() { return Revealed; }

void PowerUp::shouldReveal() { Revealed = true; }

void PowerUp::setTexture(int flag)
{
    if (flag == 0)
        shape.setTexture(&texture);
    else if (flag == 1)
        shape.setTexture(&texture2);
}