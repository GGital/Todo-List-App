#include "Node.h"

Node::Node(float x, float y, const std::string &labelText, sf::Font &font)
{
    shape.setRadius(30.f);
    shape.setFillColor(sf::Color(100, 149, 237)); // Cornflower blue
    shape.setOrigin(30.f, 30.f);                  // Center origin
    shape.setPosition(x, y);

    label.setFont(font);
    label.setString(labelText);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color::White);
    label.setPosition(x - 10.f, y + 40.f); // slightly below the node
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
