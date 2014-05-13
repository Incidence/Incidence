#ifndef _END_STATE_
#define _END_STATE_

#include "../engine/state.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/ui/ui.hpp"
#include "../engine/ui/button.hpp"
#include "../game/game.hpp"

class EndState : public State
{

public :
    EndState( Game * g );
    ~EndState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );
    void treatEvent( GameEvent e );

private :
    Game * m_game;
	UI m_ui;
};

#endif // _END_STATE_
