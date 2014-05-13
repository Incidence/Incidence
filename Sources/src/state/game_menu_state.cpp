#include "game_menu_state.hpp"

GameMenuState::GameMenuState( Game * g ) : m_ui(this)
{
    m_game = g;

	init();
}

GameMenuState::~GameMenuState( void )
{

}

void GameMenuState::init( void )
{
    Button * b;
    GameEvent ge;

    ge.type = EV_BACK;

    b = new Button();
    b->setText( "Back", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 100 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_SAVE_MENU;

    b = new Button();
    b->setText( "Save", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 200 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LOAD_MENU;

    b = new Button();
    b->setText( "Load", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 300 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_QUIT;

    b = new Button();
    b->setText( "Quit", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 400 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);
}

void GameMenuState::draw( sf::RenderTarget & window )
{
    window.setView(window.getDefaultView());
    m_ui.draw(window);
}

void GameMenuState::update( void )
{

}

void GameMenuState::handleEvent( sf::Event & e )
{
    m_ui.handleEvent(e);
}

void GameMenuState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_BACK :
        StateManager::get()->popState();
        break;

    case EV_QUIT :
		StateManager::get()->popState(2);
        break;

    case EV_SAVE_MENU :
        StateManager::get()->addState(new SaveMenuState(m_game));
        break;

    case EV_LOAD_MENU :
        StateManager::get()->addState(new LoadMenuState(m_game));
        break;

    default :
        break;

    }
}
