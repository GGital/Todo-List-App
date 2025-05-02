#include "Edge.h"

Edge::Edge(Node *a, Node *b) : nodeA(a), nodeB(b)
{
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;
}

void Edge::draw(sf::RenderWindow &window) const
{
    sf::Vertex line[2] = {
        sf::Vertex(nodeA->getPosition(), sf::Color::White),
        sf::Vertex(nodeB->getPosition(), sf::Color::White)};
    window.draw(line, 2, sf::Lines);
}
