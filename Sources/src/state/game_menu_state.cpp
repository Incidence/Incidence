#include "game_menu_state.hpp"
#include "../engine/time.hpp"

GameMenuState::GameMenuState( Game * g ) : m_ui(this)
{
    m_game = g;
    if(!m_game) {
        m_game = new Game(50, 50);
    }
    m_i = 0;

	init();
}

GameMenuState::~GameMenuState( void )
{

}

void GameMenuState::init( void )
{
    Widget * w;
    Button * b;
    GameEvent ge;

    ge.type = EV_BACK;

    b = new Button();
    b->setText( "Back", sf::Color::White );
    b->setBackground( sf::Color(100, 100, 100));
    b->setBorder( sf::Color(95,57,33) );
    b->setBorderOver( sf::Color(230,211,33) );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 100 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_SAVE_MENU;

    b = new Button();
    b->setText( "Save", sf::Color::White );
    b->setBackground( sf::Color(100, 100, 100));
    b->setBorder( sf::Color(95,57,33) );
    b->setBorderOver( sf::Color(230,211,33) );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 200 );
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
    b->setPositionAbsolute( 300, 300 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_QUIT;

    b = new Button();
    b->setText( "Quit", sf::Color::White );
    b->setBackground( sf::Color(100, 100, 100));
    b->setBorder( sf::Color(95,57,33) );
    b->setBorderOver( sf::Color(230,211,33) );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 400 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);
}

void GameMenuState::draw( sf::RenderTarget & window )
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
        StateManager::get()->addState(new LoadMenuState(m_game,1));
        break;

    default :
        break;

    }
}
