#include "foo.hpp"

#include <sstream>

std::string itos( int n )
{
    std::ostringstream oss;
    oss << n;
    return oss.str();
}


float distance( sf::Vector2f p1, sf::Vector2f p2 )
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
