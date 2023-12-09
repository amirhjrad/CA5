#include "enemy.h"
#include "constants.h"

Enemy::Enemy()
{
    shape.setSize(sf::Vector2f(ENEMY_SIZE, ENEMY_SIZE));
    loadTexture();
    int randomStartDirChance = 1;
    float random = static_cast<float>(rand()) / static_cast<float>(randomStartDirChance);
    if (isVertical){
        if (random <= ENEMY_PROBABILITY) {upOrRight = true;}
        else {shape.move(0.0f, ENEMY_SIZE);}}
    else {
        if (random <= ENEMY_PROBABILITY) {upOrRight = false;}
        else {shape.move(ENEMY_SIZE, 0.0f);}}
    recentlyHitPlayer = false;
}

void Enemy::loadTexture()
{
    texture.loadFromFile(ENEMY_TEXTURE);
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
    float PlayerXPos = (playerPos.x + ENEMY_SIZE/2);
    float PlayerYPos = (playerPos.y + ENEMY_SIZE/2);
    if(playerPos == bombPos || 
        (PlayerXPos > bombPos.x && PlayerXPos <= (bombPos.x + 2*ENEMY_SIZE) && PlayerYPos <= bombPos.y + ENEMY_SIZE/2 && PlayerYPos >= bombPos.y - ENEMY_SIZE/2) ||
        (PlayerXPos < bombPos.x && playerPos.x >= bombPos.x - 2*ENEMY_SIZE && PlayerYPos <= bombPos.y + ENEMY_SIZE/2 && PlayerYPos >= bombPos.y - ENEMY_SIZE/2) ||
        (PlayerYPos <= bombPos.y + ENEMY_SIZE && PlayerYPos >= bombPos.y - ENEMY_SIZE && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + ENEMY_SIZE/2) ||
        (PlayerYPos >= bombPos.y && PlayerYPos <= bombPos.y + 2*ENEMY_SIZE && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + ENEMY_SIZE/2)
        )
        return true;
    else return false;
}

sf::FloatRect Enemy::getBounds() { return shape.getGlobalBounds(); }