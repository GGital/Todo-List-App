#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"

class Edge
{
public:
    Edge(Node *a, Node *b);
    sf::Vertex line[2];
    void draw(sf::RenderWindow &window) const;

private:
    const Node *nodeA;
    const Node *nodeB;
};
