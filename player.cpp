#include "player.h"
#include "constants.h"

Player::Player()
{
    shape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    shape.setPosition(0.0f, 50.0f);
    loadTexture();
    setTexture(RIGHT);
    numOfBombs = INIT_BOMBS;
    numOfCollectedKeys = INIT_KEYS;
    lives = INIT_LIVES;
}

void Player::loadTexture()
{
    textureUp.loadFromFile(UP_TEXTURE);
    textureDown.loadFromFile(DOWN_TEXTURE);
    textureLeft.loadFromFile(LEFT_TEXTURE);
    textureRight.loadFromFile(RIGHT_TEXTURE);
}

bool Player::playerOnDoor(Door door)
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f doorPos = door.getPosition();
    float PlayerXPos = (playerPos.x + PLAYER_SIZE/2);
    float PlayerYPos = (playerPos.y + PLAYER_SIZE/2);;   
    float tolerance = TOLERANCE;  
    if (abs(PlayerXPos - doorPos.x) <= tolerance && abs(PlayerYPos - doorPos.y) <= tolerance && numOfCollectedKeys == 3)
        return true;
    else 
        return false;
}

bool Player::playerOnBomb(Bomb tmpBomb)
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f bombPos = tmpBomb.getPosition();
    float PlayerXPos = (playerPos.x + PLAYER_SIZE/2);
    float PlayerYPos = (playerPos.y + PLAYER_SIZE/2);
    if(playerPos == bombPos || 
        (PlayerXPos > bombPos.x && PlayerXPos <= (bombPos.x + 2*PLAYER_SIZE) && PlayerYPos <= bombPos.y + PLAYER_SIZE/2 && PlayerYPos >= bombPos.y - PLAYER_SIZE/2) ||
        (PlayerXPos < bombPos.x && playerPos.x >= bombPos.x - 2*PLAYER_SIZE && PlayerYPos <= bombPos.y + PLAYER_SIZE/2 && PlayerYPos >= bombPos.y - PLAYER_SIZE/2) ||
        (PlayerYPos <= bombPos.y + PLAYER_SIZE && PlayerYPos >= bombPos.y - PLAYER_SIZE && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + PLAYER_SIZE/2) ||
        (PlayerYPos >= bombPos.y && PlayerYPos <= bombPos.y + 2*PLAYER_SIZE && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + PLAYER_SIZE/2)
        )
        return true;
    else return false;
}

bool Player::playerOnKey(Key tmpKey)
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f keyPos = tmpKey.getPosition();
    float PlayerXPos = (playerPos.x + PLAYER_SIZE/2);
    float PlayerYPos = (playerPos.y + PLAYER_SIZE/2);
    float tolerance = TOLERANCE;
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
    float tolerance = TOLERANCE;
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
    float tolerance = TOLERANCE;       
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
    if (direction == UP)
        shape.setTexture(&textureUp);
    else if (direction == DOWN)
        shape.setTexture(&textureDown);
    else if (direction == RIGHT)
        shape.setTexture(&textureRight);
    else if (direction == LEFT)
        shape.setTexture(&textureLeft);
}