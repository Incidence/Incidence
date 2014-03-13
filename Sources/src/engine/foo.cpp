#include "foo.hpp"

#include <sstream>
#include <cmath>

std::string itos( int n )
{
    std::ostringstream oss;
    oss << n;
    return oss.str();
}


float distance( sf::Vector2f p1, sf::Vector2f p2 )
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

float distance( sf::Vector2i p1, sf::Vector2i p2 )
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}


sf::Vector2f posLarg(bool sensRotation, sf::Vector2f pos, sf::Vector2f direction, int width)
{
    float c(1), d;
    sf::Vector2f temp, dir;

    dir.x = direction.x - pos.x;
    dir.y = direction.y - pos.y;

    d = ( sqrt( dir.x * dir.x + dir.y * dir.y ) );

    if (d != 0)
    {
        c = width / d;
    }

    dir.x = dir.x * c;
    dir.y = dir.y * c;

    if (sensRotation == true)
    {
        /* Sens Inverse */
        /*  Y <- -X
            X <- Y */
        pos.y -= dir.x;
        pos.x += dir.y;
    }
    else
    {
        /* Sens Horraire */
        /*  X <- -Y
            Y <- X */
        pos.x -= dir.y;
        pos.y += dir.x;
    }

    return pos;
}
