#include "Edge.h"

Edge::Edge(sf::Vector2f start, sf::Vector2f end)
{
    line[0] = sf::Vertex(start, sf::Color::White);
    line[1] = sf::Vertex(end, sf::Color::White);
}

void Edge::draw(sf::RenderWindow &window) const
{
    window.draw(line, 2, sf::Lines);
}
