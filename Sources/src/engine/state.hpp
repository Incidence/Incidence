#ifndef _STATE_
#define _STATE_

#include <SFML/Graphics.hpp>
#include <list>

#include "../engine/game_event.hpp"

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

    /// Event du jeu
    virtual void addEvent( GameEvent e ) {
        this->listEvent.push_back( e );
    }

    void processEvent( void ) {
        for(std::list< GameEvent >::iterator i = this->listEvent.begin(); i != this->listEvent.end(); i++)
        {
            this->treatEvent(*i);
        }
        this->listEvent.clear();
    }

    virtual void treatEvent( GameEvent e ) = 0;

private :

    std::list< GameEvent > listEvent;

};

#endif // _STATE_
