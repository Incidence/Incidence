#include "end_state.hpp"

EndState::EndState( Game * g ) : m_ui(this)
{
    m_game = g;
    if(m_game) {
	    m_game = new Game();
    }

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

    w = new Widget();
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/background.png" ) );
    w->setPositionRelative(LEFT);
    w->setPositionRelative(TOP);
    m_ui.addWidget(w);

    ge.type = EV_BACK;

    b = new Button();
    b->setText( "Back", sf::Color::Black );
    b->setTextOver(sf::Color(100, 20, 20));
    b->setPositionAbsolute( 350, 125 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    w = new Widget();
    w->setText( "This story ends here..." );
    w->setTextSize( 20 );
    w->setPositionAbsolute( 280, 200 );
    m_ui.addWidget(w);
/*
    w = new Widget();
    w->setText( "This story ends here..." );
    w->setTextSize( 20 );
    w->setPositionAbsolute( 280, 250 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "This story ends here..." );
    w->setTextSize( 20 );
    w->setPositionAbsolute( 280, 300 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "This story ends here..." );
    w->setTextSize( 20 );
    w->setPositionAbsolute( 280, 350 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "This story ends here..." );
    w->setTextSize( 20 );
    w->setPositionAbsolute( 280, 400 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "This story ends here..." );
    w->setTextSize( 20 );
    w->setPositionAbsolute( 280, 450 );
    m_ui.addWidget(w);
*/
}

void EndState::draw( sf::RenderTarget & window )
{
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
