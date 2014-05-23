#include "main_menu_state.hpp"

#include "../engine/time.hpp"

MainMenuState::MainMenuState( sf::RenderWindow * window ) : m_ui(this)
{
    m_window = window;
    m_game = new Game(50, 50);

    m_i = 0;
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

    ge.type = EV_START;

    b = new Button();
    b->setText( "Start", sf::Color::White );
    b->setBackground( sf::Color(100, 100, 100));
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
    b->setBackground( sf::Color(100, 100, 100));
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
    b->setBackground( sf::Color(100, 100, 100));
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
    sf::Vector2u windowSize = window.getSize();
    m_i += Time::get()->deltaTime();
    sf::Vector2f p = rotateOnCircle(m_i / TIME_TO_CIRCLE, 11*32, sf::Vector2f(25*32, 25*32));
	sf::View v = sf::View(sf::Vector2f(p.x, p.y), sf::Vector2f(windowSize.x,windowSize.y));
    window.setView(v);
	m_game->drawMap(window);

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
        StateManager::get()->addState(new LoadMenuState(m_game));
        break;

    default :
        break;

    }
}
