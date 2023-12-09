#include "key.h"
#include "constants.h"

Key::Key()
{
    shape.setSize(sf::Vector2f(KEYS_SIZE, KEYS_SIZE));
    loadTexture();
    remove = false;
    Revealed = false;
}

void Key::loadTexture()
{
    texture.loadFromFile(KEYS_TEXTURE);
    shape.setTexture(&texture);
}

void Key::draw(sf::RenderWindow& window) { window.draw(shape); }

void Key::setPosition(sf::Vector2f position) { shape.setPosition(position); }

sf::Vector2f Key::getPosition() { return shape.getPosition(); }

bool Key::isRemovable() { return remove; }

void Key::shouldRemove() { remove = true; }

bool Key::isRevealed() { return Revealed; }

void Key::shouldReveal() { Revealed = true; }

