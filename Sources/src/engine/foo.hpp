#ifndef _FOO_
#define _FOO_

#include <string>
#include "SFML/Graphics.hpp"

std::string itos( int n );

float distance( sf::Vector2f p1, sf::Vector2f p2 );
float distance( sf::Vector2i p1, sf::Vector2i p2 );

sf::Vector2f posLarg(bool sensRotation, sf::Vector2f pos, sf::Vector2f direction, int width);

#endif // _FOO_
