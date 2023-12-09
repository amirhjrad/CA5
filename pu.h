#ifndef PU_H
#define PU_H
#include <SFML/Graphics.hpp>
#include <iostream>

class PowerUp
{
public:
    PowerUp();
    void loadTexture();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    bool isRemovable();
    void shouldRemove();
    bool isRevealed();
    void shouldReveal();
   void setTexture(int flag);
    int tmp;
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf:: Texture texture2;
    bool remove;
    bool Revealed;
};


#endif