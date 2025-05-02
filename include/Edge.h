#pragma once
#include <SFML/Graphics.hpp>

class Edge
{
public:
    Edge(sf::Vector2f start, sf::Vector2f end);

    void draw(sf::RenderWindow &window) const;

private:
    sf::Vertex line[2];
};
