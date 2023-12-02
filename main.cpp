#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <random>
#include <algorithm>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 200.0f;
const float BOMB_TIMER_DURATION = 2.0f;
const float EXPLOSION_TIMER_DURATION = 0.5f; 


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

class Player {
public:
    Player(){
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        shape.setPosition(0.0f, 50.0f);
        loadTexture();
        setTexture("Right");
        numOfBombs = 0;
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
        cout << "player(" << PlayerXPos << "," << PlayerYPos<< ")" << endl;
        cout << "bomb(" << bombPos.x << "," << bombPos.y << ")" << endl;
        if(playerPos == bombPos || 
          (PlayerXPos > bombPos.x && PlayerXPos <= (bombPos.x + 2*50.0) && PlayerYPos <= bombPos.y + 50/2 && PlayerYPos >= bombPos.y - 50/2) ||
          (PlayerXPos < bombPos.x && playerPos.x >= bombPos.x - 2*50.0 && PlayerYPos <= bombPos.y + 50/2 && PlayerYPos >= bombPos.y - 50/2) ||
          (PlayerYPos <= bombPos.y + 50 && PlayerYPos >= bombPos.y - 50.0 && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + 50.0/2) ||
          (PlayerYPos >= bombPos.y && PlayerYPos <= bombPos.y + 2*50.0 && PlayerXPos >= bombPos.x && PlayerXPos <= bombPos.x + 50.0/2)
          )
            return true;
        else return false;
    }

    void move(sf::Vector2f& movement) { shape.move(movement); }

    void setPosition(sf::Vector2f& position) { shape.setPosition(position); }

    int getNumOfBombs() { return numOfBombs; }

    int getLives() { return lives; }

    void incNumOfBombs() { numOfBombs += 1 ; }

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

class Key {
public:
    Key() 
    {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        loadTexture();
    };
    void loadTexture()
    {
        texture.loadFromFile("assets/key.png");
        shape.setTexture(&texture);
    }
    vector<vector<char>> placeKeys(const vector<vector<char>>& mapData) 
    {
        vector<pair<int, int>> wallPositions;

        for (int i = 0; i < map.size(); ++i) 
        {
            for (int j = 0; j < map[i].size(); ++j) 
            {
                if (map[i][j] == 'B') 
                {
                    wallPositions.push_back(make_pair(i, j));
                }
            }
        }

        random_device rd;
        mt19937 gen(rd());
        shuffle(wallPositions.begin(), wallPositions.end(), gen);
        vector<pair<int, int>> keyPositions(wallPositions.begin(), wallPositions.begin() + 3);

        vector<vector<char>> keysMap = map;
        for (const auto& pos : keyPositions) 
        {
            keysMap[pos.first][pos.second] = 'K';
        }
        return keysMap;
    }
    void incCollectedKeysNum() {collectedKeys += 1;}
    int getCollectedKeys() {return collectedKeys;}
    void draw(sf::RenderWindow& window) {window.draw(shape);}

private:
    vector<vector<char>> map;
    sf::RectangleShape shape;
    int collectedKeys;
    sf::Texture texture;
};


class Game
{
public:
    Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game") { }
        
    void revealKeys()
    {

    }
    void removeCollectedKeys()
    {

    }
    void collectKeys()
    {
        
    }
    void removeSoftObstaclesAroundBomb(const sf::Vector2f& bombPosition)
    {
        int bombGridX = static_cast<int>(bombPosition.x) / 50;
        int bombGridY = static_cast<int>(bombPosition.y) / 50;
        int radius = 1; 
        if (bombGridY - radius >= 0 && map[bombGridY - radius][bombGridX] == 'B')
            map[bombGridY - radius][bombGridX] = ' ';
        if (bombGridY + radius < map.size() && map[bombGridY + radius][bombGridX] == 'B')
            map[bombGridY + radius][bombGridX] = ' ';
        if (bombGridX - radius >= 0 && map[bombGridY][bombGridX - radius] == 'B')
            map[bombGridY][bombGridX - radius] = ' ';
        if (bombGridX + radius < map[bombGridY].size() && map[bombGridY][bombGridX + radius] == 'B')
            map[bombGridY][bombGridX + radius] = ' ';
    }

    void removeExpiredBombs()
    {
        bombs.erase(remove_if(bombs.begin(), bombs.end(), []( Bomb& bomb) {
            return bomb.remove();
        }), bombs.end());
    }
    
    void drawTexture()
    {
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
            }
        }
    }
    
    void EndGame() 
    {
        window.clear();
        sf::Font font;
        font.loadFromFile("assets/fonts/arial.ttf");
        sf::Text message("You have lost", font, 24);
        message.setFillColor(sf::Color::White);
        message.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
        window.draw(message);
        window.display();
    }

    void run() {
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
        sf::FloatRect playerBounds = player.getBounds();
        sf::FloatRect windowBounds(0.0f, 50.0f - 6, WINDOW_WIDTH, WINDOW_HEIGHT - 50.0f - 6);

        sf::FloatRect newBounds(newPosition, sf::Vector2f(playerBounds.width, playerBounds.height));
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
            windowBounds.contains(newPosition + sf::Vector2f(playerBounds.width, playerBounds.height)))
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
            }
            map.push_back(row);
                
        }
        file.close();
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
        window.draw(livesText); 

        sf::RectangleShape keysSection(sf::Vector2f(WINDOW_WIDTH, 50));
        keysSection.setFillColor(sf::Color(128,128,128));
        window.draw(keysSection);
        sf::Text keysText("Keys: " + to_string(keys.getCollectedKeys()), font, 20);
        keysText.setFillColor(sf::Color::White);
        keysText.setPosition(20, 10);
        window.draw(keysText); 
    }
private:

    void initial()
    {
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
            /* if (event.type == sf::Event::KeyPressed && 
                     (event.key.code == sf::Keyboard::W ||
                      event.key.code == sf::Keyboard::Up ||
                      event.key.code == sf::Keyboard::S ||
                      event.key.code == sf::Keyboard::Down ||
                      event.key.code == sf::Keyboard::D ||
                      event.key.code == sf::Keyboard::Right ||
                      event.key.code == sf::Keyboard::A ||
                      event.key.code == sf::Keyboard::Left))
                        handlePlayerMovement(deltaTime); */
        }
    }

    void update(sf::Time deltaTime)
    {
        if(player.getLives() <= 0)
        {
            EndGame();
            finished = true;
        }
        handlePlayerMovement(deltaTime);
        for (Bomb& bomb : bombs) {
            bomb.update(deltaTime);
            if (bomb.remove()) {
                player.decNumOfBombs();
                removeSoftObstaclesAroundBomb(bomb.getPosition());
                if(player.playerOnBomb(bomb)) {
                    player.decLives();
                }
            }
        }
        removeExpiredBombs();
    }

    void render()
    {
        window.clear();
        drawTexture();
        player.draw(window);
        for(Bomb &tmpBomb : bombs){
            tmpBomb.draw(window);
        }
        drawInfoBoard();
        if(!finished)
            window.display();
    }


    Bomb tmpBomb;
    sf::RenderWindow window;
    Player player;
    vector<Bomb> bombs;
    Grass grass;
    vector<vector<char>> map;
    Key keys;
    int finished = false;
};

int main()
{
    Game game;
    game.run();
    return 0;
}


