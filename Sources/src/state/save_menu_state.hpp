#ifndef _SAVE_MENU_STATE_
#define _SAVE_MENU_STATE_

#include "../engine/data_manager.hpp"
#include "../engine/state.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/ui/ui.hpp"
#include "../engine/ui/button.hpp"
#include "../engine/ui/text_insert.hpp"
#include "../state/test_state.hpp"

class SaveMenuState : public State
{

public :
    SaveMenuState( Game * g );
    ~SaveMenuState( void );

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

#endif // _SAVE_MENU_STATE_
