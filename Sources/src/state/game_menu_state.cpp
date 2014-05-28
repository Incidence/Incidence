#include "game_menu_state.hpp"
#include "../engine/time.hpp"

GameMenuState::GameMenuState( Game * g ) : m_ui(this)
{
    m_game = g;
    if(!m_game) {
        m_game = new Game(50, 50);
    }
    m_i = rand()%((int)TIME_TO_CIRCLE);

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

    w = new Widget();
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/background.png" ) );
    w->setPositionRelative(LEFT);
    w->setPositionRelative(TOP);
    m_ui.addWidget(w);

    ge.type = EV_BACK;

    b = new Button();
    b->setText( "Back", sf::Color::Black );
    b->setTextOver(COLOR_OVER);
    b->setPositionAbsolute( 350, 200 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_SAVE_MENU;

    b = new Button();
    b->setText( "Save", sf::Color::Black );
    b->setTextOver(COLOR_OVER);
    b->setPositionAbsolute( 350, 250 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LOAD_MENU;

    b = new Button();
    b->setText( "Load", sf::Color::Black );
    b->setTextOver(COLOR_OVER);
    b->setPositionAbsolute( 350, 300 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_QUIT;

    b = new Button();
    b->setText( "Quit", sf::Color::Black );
    b->setTextOver(COLOR_OVER);
    b->setPositionAbsolute( 350, 350 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);
}

void GameMenuState::draw( sf::RenderTarget & window )
{
    sf::Vector2u windowSize = window.getSize();
    m_i += Time::get()->deltaTime();
    if (m_i > TIME_TO_CIRCLE)
    {
        m_i-=TIME_TO_CIRCLE;
    }
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
        DataManager::get()->getMusic("data/menu.ogg")->stop();
        DataManager::get()->getMusic("data/partie.ogg")->play();
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
