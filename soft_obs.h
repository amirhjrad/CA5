#ifndef SOFT_OBS_H
#define SOFT_OBS_H
#include <SFML/Graphics.hpp>

class SoftObstacle {
public:
    SoftObstacle();
    void loadTexture();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
private:
    sf::RectangleShape shape;
    sf::Texture texture;
};

#endif