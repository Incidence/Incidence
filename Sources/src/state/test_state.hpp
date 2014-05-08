#ifndef _TEST_STATE_
#define _TEST_STATE_

#include "../engine/state.hpp"
#include "../engine/ui/ui.hpp"
#include "../game/game.hpp"

class TestState : public State
{

public :
    TestState( sf::RenderWindow * window );
    ~TestState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );
    void treatEvent( GameEvent e );

    void updateDay( void );

private :

    Game * m_game;
	sf::RenderWindow * m_window;
	sf::View m_view;

    int m_dayDuration;
    int m_dayBeginTime;
    bool m_night;
    int m_timePause;
    bool m_pause;

    UI m_ui;
    int m_select;
    int m_element;
};

#endif // _TEST_STATE_


