#ifndef _NIGHT_STATE_
#define _NIGHT_STATE_

#include "../engine/state.hpp"
#include "../game/game.hpp"
#include "../engine/ui/ui.hpp"

class NightState : public State
{

public :
    NightState( Game * g );
    ~NightState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );
    void treatEvent( GameEvent e );

    int prct(int v);

    void validation( void );

private :

    int m_prctLumberjack;
    int m_prctPickman;
    int m_prctHunter;
    int m_prctGatherer;

    Game * m_game;
	UI m_ui;
};

#endif // _NIGHT_STATE_
