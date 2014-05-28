#include "save_menu_state.hpp"
#include "../engine/time.hpp"

SaveMenuState::SaveMenuState( Game * g ) : m_ui(this)
{
    m_game = g;
    if(m_game == NULL) {
        m_game = new Game(50, 50);
    }

    m_i = rand()%((int)TIME_TO_CIRCLE);

	init();
}

SaveMenuState::~SaveMenuState( void )
{

}

void SaveMenuState::init( void )
{
    Widget * w;
    Button * b;
    TextInsert * ti;
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
    b->setPositionAbsolute( 350, 225 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ti = new TextInsert();
    ti->setName("textSave");
    ti->setLenght(6);
    ti->setBorder(sf::Color::Black);
    ti->setBorderSize(1);
    ti->setPositionAbsolute(300,280);
    ti->setSize(200,45);
    ti->select(true);
    m_ui.addWidget(ti);

    ge.type = EV_VALID;

    b = new Button();
    b->setText( "Save", sf::Color::Black );
    b->setTextOver(COLOR_OVER);
    b->setPositionAbsolute( 350, 325 );
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
            copyFile("saves/"+savePath+".save", "saves/auto_save.autosave");
            //m_game->saveGame("saves/"+savePath+".save");
            StateManager::get()->popState();
        }
        break;

    default :
        break;

    }
}
