#include "player.h"

Player::Player()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setPosition(0.0f, 50.0f);
    loadTexture();
    setTexture("Right");
    numOfBombs = 0;
    numOfCollectedKeys = 0;
    lives = 2;
}

void Player::loadTexture()
{
    textureUp.loadFromFile("assets/boy/up.png");
    textureDown.loadFromFile("assets/boy/down.png");
    textureLeft.loadFromFile("assets/boy/left.png");
    textureRight.loadFromFile("assets/boy/right.png");
}

bool Player::playerOnDoor(Door door)
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f doorPos = door.getPosition();
    float PlayerXPos = (playerPos.x + 50/2);
    float PlayerYPos = (playerPos.y + 50/2);;   
    float tolerance = 15;  
    if (abs(PlayerXPos - doorPos.x) <= tolerance && abs(PlayerYPos - doorPos.y) <= tolerance && numOfCollectedKeys == 3)
        return true;
    else 
        return false;
}

bool Player::playerOnBomb(Bomb tmpBomb)
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

bool Player::playerOnKey(Key tmpKey)
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f keyPos = tmpKey.getPosition();
    float PlayerXPos = (playerPos.x + 50/2);
    float PlayerYPos = (playerPos.y + 50/2);
    float tolerance = 30;
    if (abs(PlayerXPos - keyPos.x) <= tolerance && abs(PlayerYPos - keyPos.y) <= tolerance)
        return true;
    else 
        return false;
}

bool Player::playerOnPU(PowerUp tmpPU)
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f PUPos = tmpPU.getPosition();
    float PlayerXPos = (playerPos.x + 50/2);
    float PlayerYPos = (playerPos.y + 50/2);
    float tolerance = 30;
    if (abs(PlayerXPos - PUPos.x) <= tolerance && abs(PlayerYPos - PUPos.y) <= tolerance)
        return true;
    else 
        return false;  
}

bool Player::playerOnEnemy(Enemy tmpEnemy)
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f enemyPos = tmpEnemy.getPosition();
    float PlayerXPos = playerPos.x; 
    float PlayerYPos = playerPos.y; 
    float tolerance = 30;       
    if (abs(PlayerXPos - enemyPos.x) <= tolerance && abs(PlayerYPos - enemyPos.y) <= tolerance)
        return true;
    else 
        return false; 
}

void Player::move(sf::Vector2f& movement) { shape.move(movement); }

void Player::setPosition(sf::Vector2f& position) { shape.setPosition(position); }

int Player::getNumOfBombs() { return numOfBombs; }

int Player::getLives() { return lives; }

void Player::incLive() { lives += 1; }

void Player::incNumOfBombs() { numOfBombs += 1 ; }

void Player::collectKey() { numOfCollectedKeys += 1; }

int Player::getNumOfCollectedKeys() { return numOfCollectedKeys; }

void Player::decNumOfBombs() { numOfBombs -= 1 ; }
    
void Player::decLives() { lives -= 1 ; }

sf::Vector2f Player::getPosition() { return shape.getPosition(); }

sf::FloatRect Player::getBounds() { return shape.getGlobalBounds(); }

void Player::draw(sf::RenderWindow& window) { window.draw(shape); }

void Player::setTexture(std::string direction)
{
    if (direction == "Up")
        shape.setTexture(&textureUp);
    else if (direction == "Down")
        shape.setTexture(&textureDown);
    else if (direction == "Right")
        shape.setTexture(&textureRight);
    else if (direction == "Left")
        shape.setTexture(&textureLeft);
}