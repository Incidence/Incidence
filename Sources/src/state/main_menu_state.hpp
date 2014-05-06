#ifndef _MAIN_MENU_STATE_
#define _MAIN_MENU_STATE_

#include "../engine/state.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/ui/ui.hpp"
#include "../engine/ui/button.hpp"
#include "../state/test_state.hpp"
#include "../state/load_menu_state.hpp"

class MainMenuState : public State
{

public :
    MainMenuState( sf::RenderWindow * window );
    ~MainMenuState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );
    void treatEvent( GameEvent e );

private :
    sf::RenderWindow * m_window;
	UI m_ui;
};

#endif // _MAIN_MENU_STATE_
