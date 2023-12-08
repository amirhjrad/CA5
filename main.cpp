#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <random>
#include <algorithm>
#include <SFML/System.hpp>
#include<chrono>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
float PLAYER_SPEED = 200.0f;
const float ENEMY_SPEED = 100.0f;
const float BOMB_TIMER_DURATION = 2.0f;
const float EXPLOSION_TIMER_DURATION = 0.5f; 
// class Door
// {
// public:
//     Door()
//     {
//         shape.setSize(sf::Vector2f(50.0f, 50.0f));
//         loadTexture();   
         
//     }
//     void loadTexture()
//     {
//         texture.loadFromFile("assets/life.png");
//         //texture2.loadFromFile("");
//         shape.setTexture(&texture);
//     }
// private:

// };
class PowerUp
{
public:
    PowerUp()
    {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        loadTexture();
        remove = 0;
        Revealed = 0;
        tmp = 0;
    }
    void loadTexture()
    {
        texture.loadFromFile("assets/life.png");
        //texture2.loadFromFile("");
        shape.setTexture(&texture);
    }
    void draw(sf::RenderWindow& window) {window.draw(shape);}
    void setPosition(sf::Vector2f position) { shape.setPosition(position); }
    sf::Vector2f getPosition() { return shape.getPosition(); }
    bool isRemovable() { return remove; }
    void shouldRemove() { remove = true; }
    bool isRevealed() {return Revealed;}
    void shouldReveal() {Revealed = true;}
    int tmp;

private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf:: Texture texture2;
    bool remove;
    bool Revealed;

};
class Bomb {
public:
    Bomb()
    {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        loadTexture();
        isExploded = false;
        bombTimer = 0.0f;
        explosionTimer = 0.0f;
        shouldRemove = false;
    }
    
    void loadTexture()
    {
        texture.loadFromFile("assets/bomb.png");
        explosionTexture.loadFromFile("assets/explosion.png");
        shape.setTexture(&texture);
    }
    void update(sf::Time deltaTime)
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
    sf::Vector2f getPosition() { return shape.getPosition(); }
    bool remove() {return shouldRemove; }
    void draw(sf::RenderWindow& window) { window.draw(shape); }
    void setPosition(sf::Vector2f position) { shape.setPosition(position); }

private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Texture explosionTexture;
    bool isExploded;
    bool shouldRemove;
    float bombTimer;
    float explosionTimer;
};

class Key {
public:
    Key() 
    {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        loadTexture();
        remove = false;
        Revealed = false;
    };
    void loadTexture()
    {
        texture.loadFromFile("assets/key.png");
        shape.setTexture(&texture);
    }
    void draw(sf::RenderWindow& window) {window.draw(shape);}
    void setPosition(sf::Vector2f position) { shape.setPosition(position); }
    sf::Vector2f getPosition() { return shape.getPosition(); }
    bool isRemovable() { return remove; }
    void shouldRemove() { remove = true; }
    bool isRevealed() {return Revealed;}
    void shouldReveal() {Revealed = true;}
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    bool remove;
    bool Revealed;
};
class Enemy
{
public:
    Enemy()
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
    };

    void loadTexture()
    {
        texture.loadFromFile("assets/enemy.png");
        shape.setTexture(&texture);
        remove = false;
    }
    int direction;
    void move(sf::Vector2f& movement) { shape.move(movement); }
    void draw(sf::RenderWindow& window) { window.draw(shape); }
    void setPosition(sf::Vector2f position) { shape.setPosition(position); }
    sf::Vector2f getPosition() {return shape.getPosition();}
    bool isRemovable() { return remove; }
    void shouldRemove() { remove = true; }
    bool enemyOnBomb(Bomb tmpBomb) 
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
    sf::FloatRect getBounds() { return shape.getGlobalBounds(); }
    bool isVertical;
    bool upOrRight;
    bool recentlyHitPlayer;
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    bool remove;

};

class Player {
public:
    Player(){
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        shape.setPosition(0.0f, 50.0f);
        loadTexture();
        setTexture("Right");
        numOfBombs = 0;
        numOfCollectedKeys = 0;
        lives = 2;
    }

    void loadTexture(){
        textureUp.loadFromFile("assets/boy/up.png");
        textureDown.loadFromFile("assets/boy/down.png");
        textureLeft.loadFromFile("assets/boy/left.png");
        textureRight.loadFromFile("assets/boy/right.png");
    }

    bool playerOnBomb(Bomb tmpBomb) {
        sf::Vector2f playerPos = shape.getPosition();
        sf::Vector2f bombPos = tmpBomb.getPosition();
        float PlayerXPos = (playerPos.x + 50/2);
        float PlayerYPos = (playerPos.y + 50/2);
        //cout << "player(" << PlayerXPos << "," << PlayerYPos<< ")" << endl;
        //cout << "bomb(" << bombPos.x << "," << bombPos.y << ")" << endl;
        if(playerPos == bombPos || 
          (PlayerXPos > bombPos.x && PlayerXPos <= (bombPos.x + 2*50.0) && PlayerYPos <= bombPos.y + 50/2 && PlayerYPos >= bombPos.y - 50/2) ||
          (PlayerXPos < bombPos.x && playerPos.x >= bombPos.x - 2*50.0 && PlayerYPos <= bombPos.y + 50/2 && PlayerYPos >= bombPos.y - 50/2) ||
          (PlayerYPos <= bombPos.y + 50 && PlayerYPos >= bombPos.y - 50.0 && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + 50.0/2) ||
          (PlayerYPos >= bombPos.y && PlayerYPos <= bombPos.y + 2*50.0 && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + 50.0/2)
          )
            return true;
        else return false;
    }
    bool playerOnKey(Key tmpKey) 
    {
        sf::Vector2f playerPos = shape.getPosition();
        sf::Vector2f keyPos = tmpKey.getPosition();
        float PlayerXPos = (playerPos.x + 50/2);
        float PlayerYPos = (playerPos.y + 50/2);
        //cout << "player(" << PlayerXPos << "," << PlayerYPos<< ")" << endl;
        //cout << "key(" << keyPos.x << "," << keyPos.y << ")" << endl;
        
        float tolerance = 30;
        
        if (abs(PlayerXPos - keyPos.x) <= tolerance && abs(PlayerYPos - keyPos.y) <= tolerance)
            return true;
        else 
            return false;
    }
    bool playerOnPU(PowerUp tmpPU)
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

    bool playerOnEnemy(Enemy tmpEnemy)
    {
        sf::Vector2f playerPos = shape.getPosition();
        sf::Vector2f enemyPos = tmpEnemy.getPosition();
        float PlayerXPos = playerPos.x; 
        float PlayerYPos = playerPos.y; 
        //cout << "player(" << PlayerXPos << "," << PlayerYPos<< ")" << endl;
        //cout << "enemy(" << enemyPos.x  << "," << enemyPos.y  << ")" << endl;
        
        float tolerance = 30;
        
        if (abs(PlayerXPos - enemyPos.x) <= tolerance && abs(PlayerYPos - enemyPos.y) <= tolerance)
            return true;
        else 
            return false;        
    }


    void move(sf::Vector2f& movement) { shape.move(movement); }

    void setPosition(sf::Vector2f& position) { shape.setPosition(position); }

    int getNumOfBombs() { return numOfBombs; }

    int getLives() { return lives; }
    void incLive() {lives += 1;}
    void incNumOfBombs() { numOfBombs += 1 ; }
    void collectKey() {numOfCollectedKeys += 1;}
    int getNumOfCollectedKeys() {return numOfCollectedKeys;}
    void decNumOfBombs() { numOfBombs -= 1 ; }
    
    void decLives() { lives -= 1 ; }

    sf::Vector2f getPosition() { return shape.getPosition(); }

    sf::FloatRect getBounds() { return shape.getGlobalBounds(); }

    void draw(sf::RenderWindow& window) { window.draw(shape); }

    void setTexture(string direction)
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

private:
    sf::RectangleShape shape;
    sf::Texture textureUp;
    sf::Texture textureDown;
    sf::Texture textureLeft;
    sf::Texture textureRight;
    int numOfBombs;
    int numOfCollectedKeys;
    int lives;
};

class HardObstacle {
public:
    HardObstacle()
    {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        loadTexture();
    }

    void loadTexture()
    {
        texture.loadFromFile("assets/wall-2.png");
        shape.setTexture(&texture);
    }

    void draw(sf::RenderWindow& window) { window.draw(shape); }
    void setPosition(sf::Vector2f position) { shape.setPosition(position); }

private:
    sf::RectangleShape shape;
    sf::Texture texture;
};

class SoftObstacle {
public:
    SoftObstacle()
    {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        loadTexture();
    }

    void loadTexture()
    {
        texture.loadFromFile("assets/wall-1.png");
        shape.setTexture(&texture);
    }

    void draw(sf::RenderWindow& window) { window.draw(shape); }
    void setPosition(sf::Vector2f position) { shape.setPosition(position); }
    //vector2f getposition() {return }

private:
    sf::RectangleShape shape;
    sf::Texture texture;
};

class Grass
{
public:
    Grass()
    {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        loadTexture();
    };

    void loadTexture()
    {
        texture.loadFromFile("assets/grass.png");
        shape.setTexture(&texture);
    }

    void draw(sf::RenderWindow& window) { window.draw(shape); }
    void setPosition(sf::Vector2f position) { shape.setPosition(position); }

private:
    sf::RectangleShape shape;
    sf::Texture texture;
};

class Game
{
public:
    Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game") { revealedKeys = 0; revealedPUs = 0;}
    void removeCollectedKeys()
    {
        keys.erase(remove_if(keys.begin(), keys.end(), []( Key& key) 
        {
            return key.isRemovable();
        }), keys.end());    
    }
    void removePU()
    {
        PUs.erase(std::remove_if(PUs.begin(), PUs.end(), [](PowerUp& PU) {
            return PU.isRemovable();
        }), PUs.end());
    }

    void removeEnemy()
    {
        enemies.erase(remove_if(enemies.begin(), enemies.end(), []( Enemy& enemy) 
        {
            return enemy.isRemovable();
        }), enemies.end());    
    }
    void doublePlayerSpeed()
    {
        PLAYER_SPEED *= 2;
    }
    void handleKeyreveal()
    {
        int numOfKeys = 3;
        for(int i = 0; i < numOfKeys; i++)
        {
            int x = keys[i].getPosition().x / 50;
            int y = keys[i].getPosition().y / 50;
            cout << "k " << x << " " << y << endl;
            if(x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
            {
                if(map[y][x] == ' ')
                {
                    revealedKeys += 1;
                    keys[i].shouldReveal();
                }
            }
            
        }
    }
    void handlePUReveal()
    {
        int numOfPU = 2;
        for(int i = 0; i < numOfPU; i++)
        {
            int x = PUs[i].getPosition().x / 50;
            int y = PUs[i].getPosition().y / 50;
            cout << x << " " << y << endl;
            if(x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
            {
                if(map[y][x] == ' ')
                {
                    revealedPUs += 1;
                
                    PUs[i].shouldReveal();
                }
            }  
        }        
    }
    void removeSoftObstaclesAroundBomb(const sf::Vector2f& bombPosition)
    {
        int bombGridX = static_cast<int>(bombPosition.x) / 50;
        int bombGridY = static_cast<int>(bombPosition.y) / 50;
        int radius = 1; 
        
       if (bombGridY - radius >= 0 && map[bombGridY - radius][bombGridX] == 'B')
        {   
                map[bombGridY - radius][bombGridX] = ' ';
        }

        if (bombGridY + radius < map.size() && map[bombGridY + radius][bombGridX] == 'B')
        {
                map[bombGridY + radius][bombGridX] = ' ';
        }

        if (bombGridX - radius >= 0 && map[bombGridY][bombGridX - radius] == 'B')
        {
                map[bombGridY][bombGridX - radius] = ' ';
        }

        if (bombGridX + radius < map[bombGridY].size() && map[bombGridY][bombGridX + radius] == 'B')
        {
                map[bombGridY][bombGridX + radius] = ' ';
        }
    }
    
    // sf::Vector2f placeRandomPosition()
    // {
    //     vector<pair<int, int>> wallPositions;
    //     for (int i = 0; i < map.size(); ++i) 
    //     {
    //         for (int j = 0; j < map[i].size(); ++j) 
    //         {
    //             if (map[i][j] == 'B') 
    //             {
    //                 wallPositions.push_back(make_pair(i, j));
    //             }
    //         }
    //     }
    //     random_device rd;
    //     mt19937 gen(rd());
    //     shuffle(wallPositions.begin(), wallPositions.end(), gen);
    //     uniform_int_distribution<int> dist(0, wallPositions.size() - 1);
    //     int randomIndex = dist(gen);
    //     pair<int, int> availablePosition = wallPositions[randomIndex];
    //     sf::Vector2f playerPosition = player.getPosition();
    //     sf::Vector2f positionSF(availablePosition.second * 50, availablePosition.first * 50);
    //     if (tookenPositions.size() == 0)
    //     {
    //         tookenPositions[positionSF.x][positionSF.y] = 1;
    //         return positionSF;
    //     }
    //     else
    //     {
    //         for(int i = 0; i < tookenPositions.size(); i++)
    //         {
    //             for(int j = 0; j < tookenPositions[i].size(); i++)
    //             {
    //                 if(tookenPositions[i][j] == 1)
    //                     placeRandomPosition();
    //             }
    //         }
    //         tookenPositions[positionSF.x][positionSF.y] = 1;
    //         return positionSF;
    //     }
    // }
    void placeKey(vector<vector<char>>& mapData)
    {
        vector<pair<int, int>> wallPositions;

        for (int i = 0; i < mapData.size(); ++i) 
        {
            for (int j = 0; j < mapData[i].size(); ++j) 
            {
                if (mapData[i][j] == 'B') 
                {
                    wallPositions.push_back(make_pair(i, j));
                }
            }
        }
        random_device rd;
        mt19937 gen(rd());
        shuffle(wallPositions.begin(), wallPositions.end(), gen);
        uniform_int_distribution<int> dist(0, wallPositions.size() - 1);
        int randomIndex = dist(gen);
        pair<int, int> keyPosition = wallPositions[randomIndex];
        sf::Vector2f keyPositionSF(keyPosition.second * 50, keyPosition.first * 50);
        tmpKey.setPosition(keyPositionSF);
        if (keys.size() == 0)
        {
            keys.push_back(tmpKey);
        }
        else
        {
            for(int i = 0; i < keys.size(); i++)
            {
                if(keys[i].getPosition() == tmpKey.getPosition())
                {
                    placeKey(mapData);
                }
            }
            keys.push_back(tmpKey);       
        }
    }

    void placePU(vector<vector<char>>& mapData)
    {
        vector<pair<int, int>> wallPositions;

        for (int i = 0; i < mapData.size(); ++i) 
        {
            for (int j = 0; j < mapData[i].size(); ++j) 
            {
                if (mapData[i][j] == 'B') 
                {
                    wallPositions.push_back(make_pair(i, j));
                }
            }
        }
        random_device rd;
        mt19937 gen(rd());
        shuffle(wallPositions.begin(), wallPositions.end(), gen);
        uniform_int_distribution<int> dist(0, wallPositions.size() - 1);
        int randomIndex = dist(gen);
        pair<int, int> PUPosition = wallPositions[randomIndex];
        sf::Vector2f playerPosition = player.getPosition();
        sf::Vector2f PUPositionSF(PUPosition.second * 50, PUPosition.first * 50);
        tmpPU.setPosition(PUPositionSF);
        if (PUs.size() == 0)
        {
            PUs.push_back(tmpPU);
        }
        else
        {
            for(int i = 0; i < PUs.size(); i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    if(PUs[i].getPosition() == tmpPU.getPosition() || PUs[i].getPosition() == keys[j].getPosition())
                    {
                        placePU(mapData);
                    }
                }
            }
            PUs.push_back(tmpPU);       
        }
    }

    void removeExpiredBombs()
    {
        bombs.erase(remove_if(bombs.begin(), bombs.end(), []( Bomb& bomb) 
        {
            return bomb.remove();
        }), bombs.end());
    }

    void drawTexture()
    {
        int numRows = map.size();
        int numCols = (numRows > 0) ? map[0].size() : 0;
        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                char c = map[i][j];
                sf::Vector2f position(j * 50, i * 50);
                if (c == 'B')
                {
                    SoftObstacle obs;
                    obs.setPosition(position);
                    obs.draw(window);
                }
                else if (c == 'P')
                {
                    HardObstacle obs;
                    obs.setPosition(position);
                    obs.draw(window);
                }
                else if(c == 'V')
                {
                    tmpEnemy.setPosition(position);
                    tmpEnemy.isVertical = true;
                    enemies.push_back(tmpEnemy);
                    map[i][j] = ' ';
                }
                else if(c == 'H')
                {
                    tmpEnemy.setPosition(position);
                    tmpEnemy.isVertical = false;
                    enemies.push_back(tmpEnemy);
                    map[i][j] = ' ';
                }
                else if(c == 'D')
                {
                    tmpEnemy.setPosition(position);
                    tmpEnemy.isVertical = false;
                    enemies.push_back(tmpEnemy);
                    map[i][j] = ' ';
                }
            }
        }
        int numTilesX = window.getSize().x / 50;
        int numTilesY = window.getSize().y / 50;
        for (int i = 0; i < numTilesX; ++i) {
            for (int j = 0; j < numTilesY; ++j) {
                if (map[j][i] == ' ') {
                    grass.setPosition(sf::Vector2f(i * 50, j * 50));
                    grass.draw(window);
                }
            }
        }


    }
    
    void EndGame() 
    {
        window.clear();
        sf::Font font;
        font.loadFromFile("assets/fonts/arial.ttf");
        sf::Text message;
        if(gameTimer == -1){
            message.setString("Time is finished");
            message.setFont(font);
            message.setCharacterSize(24);
        }
        else {
            message.setString("Lifes is finished");
            message.setFont(font);
            message.setCharacterSize(24);
        }
        message.setFillColor(sf::Color::White);
        message.setPosition(WINDOW_WIDTH/2.5, WINDOW_HEIGHT/2.5);
        window.draw(message);
        window.display();
    }

    void run() 
    {
        sf::Clock clock;
        initial();
        while (window.isOpen())
        {
            sf::Time deltaTime = clock.restart();
            processEvents(deltaTime);
            update(deltaTime);
            render();
        }
    }
void handleEnemyMovement(Enemy& enemy)
{
    const float ENEMY_SPEED = 5.0f;
    sf::Vector2f movement(0.0f, 0.0f);

    if (enemy.isVertical) {
        if (enemy.upOrRight) {
            movement.y -= ENEMY_SPEED;
        }
        else {
            movement.y += ENEMY_SPEED;
        }
    }
    else {
        if (enemy.upOrRight) {
            movement.x += ENEMY_SPEED;
        }
        else {
            movement.x -= ENEMY_SPEED;
        }
    }

    sf::FloatRect enemyBounds = enemy.getBounds();
    int x = static_cast<int>((enemyBounds.left)/ 50);
    int y = static_cast<int>((enemyBounds.top) / 50);
    //cout << "(" << x << " , " << y << ") " << endl; 
    if (x < 1 || x + 1 > map[0].size()|| y < 1 || y + 1 >= map.size()) 
    {
        //cout << " x: " << x << " y: " << y << " map[0].size(): " << map[0].size() << " map.size(): " << map.size();
        enemy.upOrRight = !enemy.upOrRight;
        movement = -movement;
        enemy.move(movement);
        //cout << endl;
        return;
    }

    else if (map[y + 1][x] == 'B' || map[y + 1][x] == 'P') 
    {
            if (enemy.isVertical) 
            {
                enemy.upOrRight = !enemy.upOrRight;
                movement.y = -movement.y;
            }
    }

    else if(map[y][x] == 'B' || map[y][x] == 'P')
    {
            if (enemy.isVertical) 
            {
                enemy.upOrRight = !enemy.upOrRight;
                movement.y = -movement.y;
            } 
            else
            {
                enemy.upOrRight = !enemy.upOrRight;
                movement.x = -movement.x;                
            }      
    }
    else if(map[y][x + 1] == 'B' || map[y][x + 1] == 'P')
    {
        if(!enemy.isVertical)
        {
            enemy.upOrRight = !enemy.upOrRight;
            movement.x = -movement.x;
        }
    }
    //cout << "movement (" << movement.x << " , " << movement.y << endl;
    enemy.move(movement);

}

    void handlePlayerMovement(sf::Time deltaTime)
    {
        sf::Vector2f movement(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            movement.y -= PLAYER_SPEED * deltaTime.asSeconds();
            player.setTexture("Up");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            movement.y += PLAYER_SPEED * deltaTime.asSeconds();
            player.setTexture("Down");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            movement.x -= PLAYER_SPEED * deltaTime.asSeconds();
            player.setTexture("Left");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            movement.x += PLAYER_SPEED * deltaTime.asSeconds();
            player.setTexture("Right");
        }

        sf::Vector2f newPosition = player.getPosition() + movement;
        sf::FloatRect enemyBounds = player.getBounds();
        sf::FloatRect windowBounds(0.0f, 50.0f - 6, WINDOW_WIDTH, WINDOW_HEIGHT - 50.0f - 6);

        sf::FloatRect newBounds(newPosition, sf::Vector2f(enemyBounds.width, enemyBounds.height));
        bool obstacleCollision = false;
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[i].size(); ++j)
            {
                char c = map[i][j];
                sf::Vector2f obstaclePosition(j * 50, i * 50);
                sf::FloatRect obstacleBounds(obstaclePosition, sf::Vector2f(40.0f, 40.0f));

                if (c == 'B' || c == 'P')
                {
                    if (newBounds.intersects(obstacleBounds))
                    {
                        obstacleCollision = true;
                        break;
                    }
                }
            }
        }

        if (!obstacleCollision && windowBounds.contains(newPosition) &&
            windowBounds.contains(newPosition + sf::Vector2f(enemyBounds.width, enemyBounds.height)))
        {   
            player.move(movement);
        }
    }

    void handleBombPlacement()
    {
            if(player.getNumOfBombs() < 3)
            {
                sf::Vector2f playerPosition = player.getPosition();
                int gridX = static_cast<int>(playerPosition.x + player.getBounds().width / 2) / 50;
                int gridY = static_cast<int>(playerPosition.y + player.getBounds().height / 2) / 50;
                float positionX = (gridX * 50);
                float positionY = (gridY * 50);
                if (gridX >= 0 && gridX < (WINDOW_WIDTH / 50) && gridY >= 0 && gridY < (WINDOW_HEIGHT / 50))
                {
                    tmpBomb.setPosition(sf::Vector2f(positionX, positionY));
                    bombs.push_back(tmpBomb);
                }
                player.incNumOfBombs();
            }
    }

    void readMapFile(const string& filename)
    {
        ifstream file(filename);
        string line;
        int first = 1;
        while (getline(file, line))
        {
            vector<char> row;
            if(!first)
            {
                for (char c : line)
                {
                    row.push_back(c);
                }
            }
            else {
                for (int j=0 ; j< WINDOW_WIDTH/50; j++)
                    row.push_back('.');
                first = 0;
                gameTimer = stoi(line);
            }
            map.push_back(row);
                
        }
        file.close();
        for(int i = 0; i < 3; i++)
        {
            placeKey(map);
        }
        for(int i = 0; i < 2; i++)
        {
            // sf::Vector2f randP = placeRandomPosition();
            // tmpPU.getPosition() = randP;
            // PUs.push_back(tmpPU);
            placePU(map);
            if(i == 0)
            {
                PUs[i].tmp = 0;

            }
            if(i == 1)
            {
                PUs[i].tmp = 1;
            }
        }
    }

    void drawInfoBoard() {
        sf::RectangleShape livesSection(sf::Vector2f(WINDOW_WIDTH, 50));
        livesSection.setFillColor(sf::Color(128,128,128));
        window.draw(livesSection);
        sf::Font font;
        font.loadFromFile("assets/fonts/arial.ttf");
        sf::Text livesText("Lives: " + to_string(player.getLives()), font, 20);
        livesText.setFillColor(sf::Color::White);
        livesText.setPosition(10, 10);
        sf::RectangleShape keysSection(sf::Vector2f(WINDOW_WIDTH, 50));
        keysSection.setFillColor(sf::Color(128,128,128));
        window.draw(keysSection);
        sf::Text keysText("Keys: " + to_string(player.getNumOfCollectedKeys()), font, 20);
        keysText.setFillColor(sf::Color::White);
        keysText.setPosition(100, 10);
        window.draw(livesText); 
        window.draw(keysText); 
        std::chrono::duration<double> countDownDuration(gameTimer); 
        std::chrono::duration<double> elapsedTime = std::chrono::system_clock::now() - startTime;
        std::chrono::duration<double> remainingTime = countDownDuration - elapsedTime;
        if(remainingTime.count() > 0){
            int remainingSeconds = static_cast<int>(remainingTime.count());
            sf::Text countdownText("Timer: " + std::to_string(remainingSeconds), font, 20);
            countdownText.setFillColor(sf::Color::White);
            countdownText.setPosition(200, 10);
            window.draw(countdownText);
        }
        else gameTimer = -1;
    }
private:

    void initial()
    {
        startTime = std::chrono::system_clock::now();
        readMapFile("map.txt");
    }

    void processEvents(sf::Time deltaTime)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::X)
                handleBombPlacement();
        }
    }
    void update(sf::Time deltaTime)
    {
        //cout << gameTimer <<endl;
        if(player.getLives() <= 0 || gameTimer == -1)
        {
            EndGame();
            finished = true;
        }
        handlePlayerMovement(deltaTime);
        int tmp = 0;
        for(Enemy &enemy : enemies)
        {
            handleEnemyMovement(enemy);
            tmp++;
        }
        float lastTimeCalled;
        for (Enemy& enemy : enemies)
        {
            float timePassed = clock.getElapsedTime().asSeconds();
            lastTimeCalled = timePassed + 0.5;
            //cout << lastTimeCalled << endl;
            if (lastTimeCalled < 2)
                continue;

            if (player.playerOnEnemy(enemy))
            {
                lastTimeCalled = 0;
                clock.restart();
                player.decLives();
            }
        }

        for (Bomb& bomb : bombs) {
            bomb.update(deltaTime);
            if (bomb.remove()) {
                player.decNumOfBombs();
                removeSoftObstaclesAroundBomb(bomb.getPosition());
                if(player.playerOnBomb(bomb)) {
                    player.decLives();
                }
                for(Enemy &enemy : enemies)
                {
                    if(enemy.enemyOnBomb(bomb))
                    {
                        enemy.shouldRemove();
                        cout << "enemy on bomb" << endl;
                    }
                }

            }
        }
        removeEnemy();
        removeExpiredBombs();
        handleKeyreveal();
        handlePUReveal();
        for(PowerUp& powerUp : PUs)
        {
            if(powerUp.isRevealed())
            {
                //cout << "powerup revealed" << endl;
                if(player.playerOnPU(powerUp))
                {
                    powerUp.shouldRemove();
                    cout << powerUp.tmp << endl;
                    if(powerUp.tmp == 0)
                    {
                        if(player.getLives() < 3)
                        {
                            cout << player.getLives() << endl;
                            player.incLive();
                        }
                    }
                    if(powerUp.tmp == 1)
                    {
                        doublePlayerSpeed();
                    }
                    
                }
            }
        }
        removePU(); //bug detected
        for (Key& key : keys) 
        {
            if(key.isRevealed())
            {
                if(player.playerOnKey(key)) 
                {
                    player.collectKey();
                    key.shouldRemove();
                }
            }
        }
        removeCollectedKeys();
    }

    void render()
    {
        window.clear();
        drawTexture();
        player.draw(window);
        for(Bomb &tmpBomb : bombs)
        {
            tmpBomb.draw(window);
        }
        for(Key &tmpKey : keys)
        {
            if(tmpKey.isRevealed())
            {
                tmpKey.draw(window);
            }
        }

        for(PowerUp &tmpPU : PUs)
        {
            if(tmpPU.isRevealed())
            {
                tmpPU.draw(window);
            }
        }
        for(Enemy &tmpEnemy : enemies)
        {
            tmpEnemy.draw(window);
        }
        drawInfoBoard();
        if(!finished)
            window.display();
    }

    std::chrono::time_point<std::chrono::system_clock> startTime;
    int gameTimer;
    int revealedKeys;
    Bomb tmpBomb;
    sf::RenderWindow window;
    Player player;
    vector<Bomb> bombs;
    Grass grass;
    vector<vector<char>> map;
    Key tmpKey;
    vector<Key> keys;
    PowerUp tmpPU;
    vector<PowerUp> PUs;
    vector<vector<char>> keysMap;
    int finished = false;
    Enemy tmpEnemy;
    vector<Enemy> enemies;
    sf::Time timer;
    bool obstacleCollision;
    sf::Clock clock;
    sf::Time timePassed;
    vector<vector<int>> tookenPositions;
    int revealedPUs;
};

int main()
{
    Game game;
    game.run();
    return 0;
}





