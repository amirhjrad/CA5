#include "bomb.h"
#include "constants.h"

Bomb::Bomb()
{
    shape.setSize(sf::Vector2f(BOMB_SIZE, BOMB_SIZE));
    loadTexture();
    isExploded = false;
    bombTimer = INIT_TIMER;
    explosionTimer = INIT_TIMER;
    shouldRemove = false;
}

void Bomb::loadTexture()
{
    texture.loadFromFile(BOMB_TEXTURE);
    explosionTexture.loadFromFile(EXP_TEXTURE);
    shape.setTexture(&texture);
}

void Bomb::update(sf::Time deltaTime)
{
    if (!isExploded) {
        bombTimer += deltaTime.asSeconds();
        if (bombTimer >= BOMB_TIMER_DURATION) {
            shape.setTexture(&explosionTexture);
            isExploded = true;
            explosionTimer = INIT_TIMER;
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