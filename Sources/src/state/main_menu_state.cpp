#include "main_menu_state.hpp"

MainMenuState::MainMenuState( sf::RenderWindow * window ) : m_ui(this)
{
    m_window = window;

	init();
}

MainMenuState::~MainMenuState( void )
{

}

void MainMenuState::init( void )
{
    Button * b;
    GameEvent ge;

    ge.type = EV_START;

    b = new Button();
    b->setText( "Start", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 100 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LOAD_MENU;

    b = new Button();
    b->setText( "Load", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 200 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_EXIT;

    b = new Button();
    b->setText( "Exit", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 300 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);
}

void MainMenuState::draw( sf::RenderTarget & window )
{
    window.setView(window.getDefaultView());
    m_ui.draw(window);
}

void MainMenuState::update( void )
{

}

void MainMenuState::handleEvent( sf::Event & e )
{
    m_ui.handleEvent(e);
}

void MainMenuState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_START :
        StateManager::get()->addState(new TestState(m_window));
        break;

    case EV_EXIT :
        StateManager::get()->popState();
        break;

    case EV_LOAD_MENU :
        StateManager::get()->addState(new LoadMenuState(new Game));
        break;

    default :
        break;

    }
}
