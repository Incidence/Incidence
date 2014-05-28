#include "main_menu_state.hpp"

#include "../engine/time.hpp"

MainMenuState::MainMenuState( sf::RenderWindow * window ) : m_ui(this)
{
    m_window = window;
    m_game = new Game(50, 50);

    m_i = rand()%((int)TIME_TO_CIRCLE);
	init();
}

MainMenuState::~MainMenuState( void )
{

}

void MainMenuState::init( void )
{
    DataManager::get()->addMusic("data/partie.ogg");
    DataManager::get()->addMusic("data/menu.ogg");
    DataManager::get()->getMusic("data/menu.ogg")->play();
    Widget * w;
    Button * b;
    GameEvent ge;

    w = new Widget();
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/background.png" ) );
    w->setPositionRelative(LEFT);
    w->setPositionRelative(TOP);
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "INCIDENCE", sf::Color::Black );
    w->setTextSize(40);
    w->setPositionAbsolute(290,150);
    m_ui.addWidget(w);

    ge.type = EV_START;

    b = new Button();
    b->setText( "Start", sf::Color::Black );
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

    ge.type = EV_EXIT;

    b = new Button();
    b->setText( "Exit", sf::Color::Black );
    b->setTextOver(COLOR_OVER);
    b->setPositionAbsolute( 350, 350 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);
}

void MainMenuState::draw( sf::RenderTarget & window )
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
        StateManager::get()->addState(new TestState(m_window, m_game));
        DataManager::get()->getMusic("data/menu.ogg")->stop();
        DataManager::get()->getMusic("data/partie.ogg")->play();
        break;

    case EV_EXIT :
        StateManager::get()->popState();
        break;

    case EV_LOAD_MENU :
        StateManager::get()->addState(new TestState(m_window, m_game));
        StateManager::get()->addState(new LoadMenuState(m_game,0));
        break;

    default :
        break;

    }
}
