#include "time.hpp"

#include <iostream>
#include "SFML/Graphics.hpp"

Time * Time::m_singleton = NULL;
int Time::m_IPS = 60;

Time * Time::get( void )
{
    if(!m_singleton) { m_singleton = new Time(); }
    return m_singleton;
}

void Time::kill( void )
{
    delete m_singleton;
}

void Time::wait( sf::Time timeWait )
{
    sf::sleep(timeWait);
}

void Time::update( void )
{
    m_lastFrame = m_elapsed.getElapsedTime() - m_lastTime;
    m_lastTime = m_elapsed.getElapsedTime();


}

Time::Time( void )
{
    m_lastTime = sf::Time::Zero;
    m_lastFrame = sf::Time::Zero;
}

Time::~Time( void )
{

}


sf::Time Time::elapsed( void )
{
    return m_elapsed.getElapsedTime();
}

float Time::IPS( void )
{
    return m_lastFrame.asSeconds() * m_IPS;
}

float Time::deltaTime( void )
{
    return m_lastFrame.asSeconds();
}

void Time::setIPS( int ips )
{
    m_IPS = ips;
}
