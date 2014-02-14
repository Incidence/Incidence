#ifndef _STATE_MANAGER_
#define _STATE_MANAGER_

#include <SFML/Graphics.hpp>
#include <stack>

class State;

class StateManager
{

public :
    static StateManager * get( void );
    static void kill( void );

    void update( void );
    void draw( sf::RenderTarget & window );
    void handleEvent( sf::Event & e );

    void addState( State * s );
    void popState( void );
    State * getCurrent( void );
    void setCurrent( void );
    bool isEmpty( void ) const;

private :
    StateManager( void );
    ~StateManager( void );

    static StateManager * singleton;

    void deleteState( void );

    State * m_current;
    std::stack<State*> m_stateManaged;
    bool m_pop;

};

#endif // _STATE_MANAGER_
