#ifndef _LOAD_MENU_STATE_
#define _LOAD_MENU_STATE_

#include <dirent.h>

#include "../engine/data_manager.hpp"
#include "../engine/state.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/ui/ui.hpp"
#include "../engine/ui/button.hpp"
#include "../state/test_state.hpp"

class LoadMenuState : public State
{

public :
    LoadMenuState( Game * g );
    ~LoadMenuState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );
    void treatEvent( GameEvent e );

private :
    static const unsigned int m_itemNb = 5;
    unsigned int m_position;
    std::vector< std::string > m_files;
    Game * m_game;
	UI m_ui;
};

#endif // _LOAD_MENU_STATE_
