#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 200.0f;

class Player {
public:
    Player(){
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
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
    }

    void loadTexture()
    {
        texture.loadFromFile("assets/bomb.png");
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
    Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game") {
        loadTexture();
    }
        
    void drawTexture(){
        int numTilesX = WINDOW_WIDTH / 50;
            int numTilesY = WINDOW_HEIGHT / 50;

            // Draw grass tiles to cover the window
            for (int i = 0; i < numTilesX; ++i) {
                for (int j = 0; j < numTilesY; ++j) {
                    sf::Sprite grassSprite;
                    grassSprite.setTexture(textureGrass);
                    grassSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));  // Set the texture rectangle size to 50x50
                    grassSprite.setPosition(i * 50, j * 50);  // Set the position based on the tile size
                    window.draw(grassSprite);
                }
            }
    }

    void loadTexture(){
        textureGrass.loadFromFile("assets/grass.png");
    }
    
    void run() {
        sf::Clock clock;
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

        if (windowBounds.contains(newPosition) &&
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

private:
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
    sf::Texture textureGrass;
};

int main()
{
    Game game;
    game.run();
    return 0;
}