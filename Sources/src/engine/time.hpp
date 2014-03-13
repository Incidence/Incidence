#ifndef _TIME_
#define _TIME_

#include "SFML/Graphics.hpp"

class Time
{

public :
    static Time * get( void );
    static void kill( void );

    static void wait( sf::Time time );

    void update( void );
    sf::Time elapsed( void );
    float IPS( void );
    float deltaTime( void );
    static void setIPS( int ips );

private :
    Time( void );
    ~Time( void );

    static Time * m_singleton;

    sf::Clock m_elapsed;
    sf::Time m_lastTime;
    sf::Time m_lastFrame;
    static int m_IPS;
};

#endif // _TIME_
