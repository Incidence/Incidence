#include "foo.hpp"

#include <iostream>
#include <sstream>
#include <cmath>

void debug( std::string s )
{
    std::cout << s << std::endl;
}

void debug( int i )
{
    std::cout << i << std::endl;
}

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


sf::Vector2f getAbsolutePosition( sf::FloatRect r, sf::FloatRect c, RelativePosition p )
{
    sf::Vector2f v( r.left, r.top );

    switch( p )
    {
        case TOP :
            v.y = c.top;
            break;

        case BOTTOM :
            v.y = c.height - r.height + c.top;
            break;

        case MIDDLE :
            v.y = c.height/2 - r.height/2 + c.top;
            break;

        case LEFT :
            v.x = c.left;
            break;

        case RIGHT :
            v.x = c.width - r.width + c.left;
            break;

        case CENTER :
            v.x = c.width/2 - r.width/2 + c.left;
            break;

        default :
            break;
    }

    return v;
}

bool isInner( sf::FloatRect r, sf::Vector2i p )
{
    return ( p.y > r.top && p.y < r.top + r.height ) && ( p.x > r.left && p.x < r.left + r.width  );
}

sf::Vector2f rotateOnCircle( float i, float r, sf::Vector2f C )
{
    sf::Vector2f p;
    p.x = C.x + r * cos(i * 2 * M_PI);
    p.y = C.y + r * sin(i * 2 * M_PI);

    return p;
}


