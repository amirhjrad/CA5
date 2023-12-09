#include "key.h"

Key::Key()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    loadTexture();
    remove = false;
    Revealed = false;
}

void Key::loadTexture()
{
    texture.loadFromFile("assets/key.png");
    shape.setTexture(&texture);
}

void Key::draw(sf::RenderWindow& window) { window.draw(shape); }

void Key::setPosition(sf::Vector2f position) { shape.setPosition(position); }

sf::Vector2f Key::getPosition() { return shape.getPosition(); }

bool Key::isRemovable() { return remove; }

void Key::shouldRemove() { remove = true; }

bool Key::isRevealed() { return Revealed; }

void Key::shouldReveal() { Revealed = true; }

