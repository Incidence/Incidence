#include "end_state.hpp"
#include "../engine/time.hpp"

EndState::EndState( Game * g ) : m_ui(this)
{
    m_game = g;
    if(m_game) {
	    m_game = new Game();
    }
    m_i = 0;

	init();
}

EndState::~EndState( void )
{

}

void EndState::init( void )
{
    Button * b;
    Widget * w;
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

    w = new Widget();
    w->setText( "This story ends here..." );
    w->setTextSize( 3 );
    w->setPositionAbsolute( 100, 300 );
    m_ui.addWidget(w);
}

void EndState::draw( sf::RenderTarget & window )
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

void EndState::update( void )
{

}

void EndState::handleEvent( sf::Event & e )
{
    m_ui.handleEvent(e);
}

void EndState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_BACK :
        StateManager::get()->popState(2);
        break;

    default :
        break;

    }
}
