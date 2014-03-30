#ifndef _TEST_STATE_
#define _TEST_STATE_

#include "../engine/state.hpp"
#include "../game/game.hpp"

class TestState : public State
{

public :
    TestState( void );
    ~TestState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );

private :

    Game * m_game;
};

#endif // _TEST_STATE_


