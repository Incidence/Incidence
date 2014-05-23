#include "main_menu_state.hpp"

MainMenuState::MainMenuState( sf::RenderWindow * window ) : m_ui(this)
{
    m_window = window;
    m_game = new Game();

	init();
}

MainMenuState::~MainMenuState( void )
{

}

void MainMenuState::init( void )
{
    Widget * w;
    Button * b;
    GameEvent ge;
	
	w = new Widget();
    w->setSprite( DataManager::get()->getSprite( "data/img/background.png" ) );
    w->setPositionAbsolute( 0, 0 );
    m_ui.addWidget(w);
	
    ge.type = EV_START;

    b = new Button();
    b->setText( "Start", sf::Color::White );
    b->setBorder( sf::Color(95,57,33) );
    b->setBorderOver( sf::Color(230,211,33) );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 100 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LOAD_MENU;

    b = new Button();
    b->setText( "Load", sf::Color::White );
    b->setBorder( sf::Color(95,57,33) );
    b->setBorderOver( sf::Color(230,211,33) );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 200 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_EXIT;

    b = new Button();
    b->setText( "Exit", sf::Color::White );
    b->setBorder( sf::Color(95,57,33) );
    b->setBorderOver( sf::Color(230,211,33) );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 300 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);
}

void MainMenuState::draw( sf::RenderTarget & window )
{
	m_game->drawCarte(window);
	
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
