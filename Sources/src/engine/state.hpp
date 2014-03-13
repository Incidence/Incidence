#ifndef _STATE_
#define _STATE_

#include <SFML/Graphics.hpp>
#include <list>

class StateManager;

class State
{

public :
    State( void ) { };
    virtual ~State( void ) { };

    virtual void init( void ) = 0;
    virtual void draw( sf::RenderTarget & window ) = 0;
    virtual void update( void ) = 0;
    virtual void handleEvent( sf::Event & e ) = 0;
};

#endif // _STATE_
