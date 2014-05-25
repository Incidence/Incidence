#include "save_menu_state.hpp"
#include "../engine/time.hpp"

SaveMenuState::SaveMenuState( Game * g ) : m_ui(this)
{
    m_game = g;
    if(m_game == NULL) {
        m_game = new Game(50, 50);
    }

    m_i = 0;

	init();
}

SaveMenuState::~SaveMenuState( void )
{

}

void SaveMenuState::init( void )
{
    Button * b;
    TextInsert * ti;
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

    ti = new TextInsert();
    ti->setName("textSave");
    b->setBackground( sf::Color(100, 100, 100));
    ti->setBorder(sf::Color(95,57,33));
    ti->setBorderSize(1);
    ti->setPositionAbsolute(300,200);
    ti->setSize(300,50);
    ti->select(true);
    m_ui.addWidget(ti);

    ge.type = EV_VALID;

    b = new Button();
    b->setText( "Save", sf::Color::White );
    b->setBackground( sf::Color(100, 100, 100));
    b->setBorder( sf::Color(95,57,33) );
    b->setBorderOver( sf::Color(230,211,33) );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 300 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);
}

void SaveMenuState::draw( sf::RenderTarget & window )
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

void SaveMenuState::update( void )
{

}

void SaveMenuState::handleEvent( sf::Event & e )
{
    m_ui.handleEvent(e);
}

void SaveMenuState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_BACK :
        StateManager::get()->popState();
        break;

    case EV_VALID :
        {
            std::string savePath((static_cast<TextInsert*>(m_ui.getWidget("textSave")))->getTextEnter());
            //m_game->saveGame("saves/"+savePath+".save");
            copyFile("saves/"+savePath+".save", "saves/auto_save.autosave");
            StateManager::get()->popState();
        }
        break;

    default :
        break;

    }
}
