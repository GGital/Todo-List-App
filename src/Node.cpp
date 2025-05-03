#include "Node.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

Node::Node(float x, float y, const std::string &labelText, sf::Font &font)
{
    shape.setRadius(30.f);
    shape.setFillColor(sf::Color(100, 149, 237)); // Cornflower blue
    shape.setOrigin(30.f, 30.f);                  // Center origin
    shape.setPosition(x, y);
    shape.setOutlineColor(sf::Color::Yellow); // Set outline color
    shape.setOutlineThickness(2.f);           // Set outline thickness

    label.setFont(font);
    label.setString(labelText);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color::White);
    label.setPosition(x - 90.f, y + 40.f); // slightly below the node
}

void Node::draw(sf::RenderWindow &window) const
{
    window.draw(shape);
    window.draw(label);
}

sf::Vector2f Node::getPosition() const
{
    return shape.getPosition();
}

void Node::setFillColor(std::string status)
{
    sf::Color color;
    if (status == "Completed")
    {
        color = sf::Color::Green;
    }
    else if (status == "In progress")
    {
        color = sf::Color::Red;
    }
    else if (status == "Not started")
    {
        color = sf::Color(100, 149, 237);
    }
    else
    {
        color = sf::Color(100, 149, 237); // Default color
    }
    shape.setFillColor(color);
}

void Node::setOutlineColor(const sf::Color &color)
{
    shape.setOutlineColor(color);
    shape.setOutlineThickness(2.f); // Set outline thickness
}
