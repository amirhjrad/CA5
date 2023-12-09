#ifndef HARD_OBS_H
#define HARD_OBS_H
#include <SFML/Graphics.hpp>

class HardObstacle {
public:
    HardObstacle();
    void loadTexture();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
private:
    sf::RectangleShape shape;
    sf::Texture texture;
};

#endif