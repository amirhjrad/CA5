#ifndef KEY_H
#define KEY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Key {
public:
    Key();
    void loadTexture();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    bool isRemovable();
    void shouldRemove();
    bool isRevealed();
    void shouldReveal();
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    bool remove;
    bool Revealed;
};

#endif