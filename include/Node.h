#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Node
{
public:
    Node(float x, float y, const std::string &labelText, sf::Font &font);

    void draw(sf::RenderWindow &window) const;
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape shape;
    sf::Text label;
};
