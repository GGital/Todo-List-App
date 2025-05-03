#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Node
{
public:
    Node(float x, float y, const std::string &labelText, sf::Font &font);

    void draw(sf::RenderWindow &window) const;
    void setFillColor(std::string status);
    void setOutlineColor(const sf::Color &color);
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape shape;
    sf::Text label;
};
