#include "enemy.h"

Enemy::Enemy()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    loadTexture();
    int randomStartDirChance = 1;
    float random = static_cast<float>(rand()) / static_cast<float>(randomStartDirChance);
    if (isVertical){
        if (random <= 0.5f) {upOrRight = true;}
        else {shape.move(0.0f, 50.0f);}}
    else {
        if (random <= 0.5f) {upOrRight = false;}
        else {shape.move(50.0f, 0.0f);}}
    recentlyHitPlayer = false;
}

void Enemy::loadTexture()
{
    texture.loadFromFile("assets/enemy.png");
    shape.setTexture(&texture);
    remove = false;
}

void Enemy::move(sf::Vector2f& movement) { shape.move(movement); }

void Enemy::draw(sf::RenderWindow& window) { window.draw(shape); }

void Enemy::setPosition(sf::Vector2f position) { shape.setPosition(position); }

sf::Vector2f Enemy::getPosition() { return shape.getPosition(); }

bool Enemy::isRemovable() { return remove; }

void Enemy::shouldRemove() { remove = true; }

bool Enemy::enemyOnBomb(Bomb tmpBomb) 
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f bombPos = tmpBomb.getPosition();
    float PlayerXPos = (playerPos.x + 50/2);
    float PlayerYPos = (playerPos.y + 50/2);
    if(playerPos == bombPos || 
        (PlayerXPos > bombPos.x && PlayerXPos <= (bombPos.x + 2*50.0) && PlayerYPos <= bombPos.y + 50/2 && PlayerYPos >= bombPos.y - 50/2) ||
        (PlayerXPos < bombPos.x && playerPos.x >= bombPos.x - 2*50.0 && PlayerYPos <= bombPos.y + 50/2 && PlayerYPos >= bombPos.y - 50/2) ||
        (PlayerYPos <= bombPos.y + 50 && PlayerYPos >= bombPos.y - 50.0 && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + 50.0/2) ||
        (PlayerYPos >= bombPos.y && PlayerYPos <= bombPos.y + 2*50.0 && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + 50.0/2)
        )
        return true;
    else return false;
}

sf::FloatRect Enemy::getBounds() { return shape.getGlobalBounds(); }