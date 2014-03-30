#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "tilemap.hpp"

typedef struct Node
{
    sf::Vector2i pos;
    Node * parent;
    float dist;
    float distTotal;
    float height;
} Node;


void removeNode( std::list< Node * > & open, std::list< Node * > & close, Node * n );
void addNode( std::list< Node * > & nodeList, Node * n );
bool containNode( std::list< Node * > & nodeList, Node * n );
void addNeighbor( std::list< Node * > & open, std::list< Node * > & close, Node * n, TileMap * tilemap, sf::Vector2i to, sf::Vector2i from, int perception );

std::list< sf::Vector2i > pathfinding( TileMap * tilemap, sf::Vector2i from, sf::Vector2i to, int entityWidth, int perception = 30);

#endif
