#include "bomb.h"

Bomb::Bomb()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    loadTexture();
    isExploded = false;
    bombTimer = 0.0f;
    explosionTimer = 0.0f;
    shouldRemove = false;
}

void Bomb::loadTexture()
{
    texture.loadFromFile("assets/bomb.png");
    explosionTexture.loadFromFile("assets/explosion.png");
    shape.setTexture(&texture);
}

void Bomb::update(sf::Time deltaTime)
{
    if (!isExploded) {
        bombTimer += deltaTime.asSeconds();
        if (bombTimer >= BOMB_TIMER_DURATION) {
            shape.setTexture(&explosionTexture);
            isExploded = true;
            explosionTimer = 0.0f;
        }
    } else {
        explosionTimer += deltaTime.asSeconds();
        if (explosionTimer >= EXPLOSION_TIMER_DURATION) {
            shouldRemove = true;
        }
    }
}

sf::Vector2f Bomb::getPosition() { return shape.getPosition(); }

bool Bomb::remove() {return shouldRemove; }

void Bomb::draw(sf::RenderWindow& window) { window.draw(shape); }

void Bomb::setPosition(sf::Vector2f position) { shape.setPosition(position); }