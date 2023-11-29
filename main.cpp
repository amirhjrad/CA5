#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 200.0f;
const float BOMB_TIMER_DURATION = 2.0f;
const float EXPLOSION_TIMER_DURATION = 0.5f; 

class Player {
public:
    Player(){
        shape.setSize(sf::Vector2f(45.0f, 45.0f));
        shape.setPosition(0.0f, 0.0f);
        loadTexture();
        setTexture("Right");
    }

    void loadTexture(){
        textureUp.loadFromFile("assets/boy/up.png");
        textureDown.loadFromFile("assets/boy/down.png");
        textureLeft.loadFromFile("assets/boy/left.png");
        textureRight.loadFromFile("assets/boy/right.png");
    }

    void move(sf::Vector2f& movement) { shape.move(movement); }

    void setPosition(sf::Vector2f& position) { shape.setPosition(position); }

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
    Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game") { }
        

    void removeSoftObstaclesAroundBomb(const sf::Vector2f& bombPosition)
    {
        int bombGridX = static_cast<int>(bombPosition.x) / 50;
        int bombGridY = static_cast<int>(bombPosition.y) / 50;

        // Remove SoftObstacle objects around the bomb within a certain radius
        int radius = 1; // Adjust the radius as needed
        for (int i = bombGridY - radius; i <= bombGridY + radius; ++i)
        {
            for (int j = bombGridX - radius; j <= bombGridX + radius; ++j)
            {
                if (i >= 0 && i < map.size() && j >= 0 && j < map[i].size())
                {
                    if (map[i][j] == 'B')
                    {
                        map[i][j] = ' ';
                    }
                }
            }
        }
    }

    void removeExpiredBombs()
    {
        bombs.erase(std::remove_if(bombs.begin(), bombs.end(), []( Bomb& bomb) {
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
    
    void run() {
        sf::Clock clock;
        initial();
        while (window.isOpen())
        {
            sf::Time deltaTime = clock.restart();
            processEvents();
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
        sf::FloatRect windowBounds(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);

        sf::FloatRect newBounds(newPosition, sf::Vector2f(playerBounds.width, playerBounds.height));
        bool obstacleCollision = false;
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[i].size(); ++j)
            {
                char c = map[i][j];
                sf::Vector2f obstaclePosition(j * 50, i * 50);
                sf::FloatRect obstacleBounds(obstaclePosition, sf::Vector2f(50.0f, 50.0f));

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            sf::Vector2f playerPosition = player.getPosition();

            // Calculate the grid position within the grass area
            int gridX = static_cast<int>(playerPosition.x + player.getBounds().width / 2) / 50;
            int gridY = static_cast<int>(playerPosition.y + player.getBounds().height / 2) / 50;

            // Calculate the position within the grass area
            float positionX = (gridX * 50);
            float positionY = (gridY * 50);

            // Set the bomb only if the center of the player position is within the grass area
            if (gridX >= 0 && gridX < (WINDOW_WIDTH / 50) && gridY >= 0 && gridY < (WINDOW_HEIGHT / 50))
            {
                tmpBomb.setPosition(sf::Vector2f(positionX, positionY));
                bombs.push_back(tmpBomb);
            }
        }
    }

    void readMapFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                std::vector<char> row;
                for (char c : line)
                {
                    row.push_back(c);
                }
                map.push_back(row);
            }
            file.close();
        }
        else
        {
            std::cerr << "Failed to open the map file." << std::endl;
        }
    }

private:

    void initial()
    {
        readMapFile("map.txt");
    }

    void processEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void update(sf::Time deltaTime)
    {
        handlePlayerMovement(deltaTime);
        handleBombPlacement();
        for (Bomb& bomb : bombs) {
            bomb.update(deltaTime);
            if (bomb.remove()) {
                removeSoftObstaclesAroundBomb(bomb.getPosition());
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
        window.display();
    }

    Bomb tmpBomb;
    sf::RenderWindow window;
    Player player;
    vector<Bomb> bombs;
    Grass grass;
    vector<vector<char>> map;
};

int main()
{
    Game game;
    game.run();
    return 0;
}