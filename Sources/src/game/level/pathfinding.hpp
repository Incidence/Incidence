#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "carte.hpp"

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
void addNeighbor( std::list< Node * > & open, std::list< Node * > & close, Node * n, Carte * carte, sf::Vector2i from );

std::list< sf::Vector2i > pathfinding( Carte * carte, sf::Vector2i from, sf::Vector2i to, int entityWidth);

#endif
