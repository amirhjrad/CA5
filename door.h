#ifndef DOOR_H
#define DOOR_H
#include <SFML/Graphics.hpp>


class Door {
public:
    Door();
    void loadTexture();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

private:
    sf::RectangleShape shape;
    sf::Texture texture;
};
#endif