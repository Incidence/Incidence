#ifndef _GAME_MENU_STATE_
#define _GAME_MENU_STATE_

#include "../engine/data_manager.hpp"
#include "../engine/state.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/ui/ui.hpp"
#include "../engine/ui/button.hpp"
#include "../state/save_menu_state.hpp"
#include "../state/load_menu_state.hpp"

class GameMenuState : public State
{

public :
    GameMenuState( Game * g );
    ~GameMenuState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );
    void treatEvent( GameEvent e );

private :
    Game * m_game;
	UI m_ui;
	float m_i;
};

#endif // _GAME_MENU_STATE_
