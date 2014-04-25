#ifndef _FOO_
#define _FOO_

#include <string>
#include "SFML/Graphics.hpp"

void debug( std::string s );
void debug( int i );

std::string itos( int n );

float distance( sf::Vector2f p1, sf::Vector2f p2 );
float distance( sf::Vector2i p1, sf::Vector2i p2 );

sf::Vector2f posLarg(bool sensRotation, sf::Vector2f pos, sf::Vector2f direction, int width);

typedef enum RelativePosition{ TOP, BOTTOM, MIDDLE, LEFT, RIGHT, CENTER, NONE } RelativePosition;

sf::Vector2f getAbsolutePosition( sf::FloatRect r, sf::FloatRect c, RelativePosition p );
bool isInner( sf::FloatRect r, sf::Vector2i p );

#endif // _FOO_
