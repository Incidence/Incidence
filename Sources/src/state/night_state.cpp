#include "night_state.hpp"

#include "../engine/state_manager.hpp"
#include "../engine/ui/button.hpp"
#include "../engine/time.hpp"

NightState::NightState( Game * g ) : m_ui(this)
{
    m_game = g;

	init();
}

NightState::~NightState( void )
{

}

void NightState::init( void )
{
    m_prctLumberjack = 5;
    m_prctPickman = 5;
    m_prctHunter = 5;
    m_prctGatherer = 5;

    Widget * w;
    Button * b;

    w = new Widget();
    w->setContent( new WidgetContent( "TEXT", "Lumberjack % : ", sf::Color::White ) );
    w->setPositionAbsolute( 100, 40 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setContent( new WidgetContent( "TEXT", "Hunter % : ", sf::Color::White ) );
    w->setPositionAbsolute( 100, 80 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setContent( new WidgetContent( "TEXT", "Pickman % : ", sf::Color::White ) );
    w->setPositionAbsolute( 100, 120 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setContent( new WidgetContent( "TEXT", "Gatherer % : ", sf::Color::White ) );
    w->setPositionAbsolute( 100, 160 );
    m_ui.addWidget(w);

    // ------

    w = new Widget();
    w->setName("textLumberjack");
    w->setContent( new WidgetContent( "TEXT", itos(m_prctLumberjack), sf::Color::White ) );
    w->setPositionAbsolute( 300, 40 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setName("textHunter");
    w->setContent( new WidgetContent( "TEXT", itos(m_prctHunter), sf::Color::White ) );
    w->setPositionAbsolute( 300, 80 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setName("textPickman");
    w->setContent( new WidgetContent( "TEXT", itos(m_prctPickman), sf::Color::White ) );
    w->setPositionAbsolute( 300, 120 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setName("textGatherer");
    w->setContent( new WidgetContent( "TEXT", itos(m_prctGatherer), sf::Color::White ) );
    w->setPositionAbsolute( 300, 160 );
    m_ui.addWidget(w);

    // -----

    GameEvent ge;
    ge.type = EV_MORE_LUMBERJACK;

    b = new Button();
    b->setContent( new WidgetContent( "TEXT", "+", sf::Color::Green ) );
    b->setBorder( sf::Color::Yellow );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 250, 40 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_HUNTER;

    b = new Button();
    b->setContent( new WidgetContent( "TEXT", "+", sf::Color::Green ) );
    b->setBorder( sf::Color::Yellow );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 250, 80 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_PICKMAN;

    b = new Button();
    b->setContent( new WidgetContent( "TEXT", "+", sf::Color::Green ) );
    b->setBorder( sf::Color::Yellow );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 250, 120 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_GATHERER;

    b = new Button();
    b->setContent( new WidgetContent( "TEXT", "+", sf::Color::Green ) );
    b->setBorder( sf::Color::Yellow );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 250, 160 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    // -----

    ge.type = EV_LESS_LUMBERJACK;

    b = new Button();
    b->setContent( new WidgetContent( "TEXT", "-", sf::Color::Red ) );
    b->setBorder( sf::Color::Yellow );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 340, 40 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LESS_HUNTER;

    b = new Button();
    b->setContent( new WidgetContent( "TEXT", "-", sf::Color::Red ) );
    b->setBorder( sf::Color::Yellow );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 340, 80 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LESS_PICKMAN;

    b = new Button();
    b->setName("d");
    b->setContent( new WidgetContent( "TEXT", "-", sf::Color::Red ) );
    b->setBorder( sf::Color::Yellow );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 340, 120 );
    b->setSize( 32, 32 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LESS_GATHERER;

    b = new Button();
    b->setContent( new WidgetContent( "TEXT", "-", sf::Color::Red ) );
    b->setBorder( sf::Color::Yellow );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute(340, 160 );
    b->setSize( 32, 32 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    // ----------

    ge.type = EV_SELECT_RAIN;

    b = new Button();
    b->setContent( new WidgetContent( "SPRITE", "data/img/rainButton.png" ) );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 200, 300 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    w = new Widget();
    w->setName("rainSelected");
    w->setShow(false);
    w->setContent( new WidgetContent( "SPRITE", "data/img/validButton.png" ) );
    w->setPositionAbsolute( 240, 300 );
    m_ui.addWidget(w);


    ge.type = EV_SELECT_SUN;

    b = new Button();
    b->setContent( new WidgetContent( "SPRITE", "data/img/sunButton.png" ) );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 300 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    w = new Widget();
    w->setName("sunSelected");
    w->setShow(false);
    w->setContent( new WidgetContent( "SPRITE", "data/img/validButton.png" ) );
    w->setPositionAbsolute( 340, 300 );
    m_ui.addWidget(w);

    // ----------

    ge.type = EV_VALID;

    b = new Button();
    b->setContent( new WidgetContent( "SPRITE", "data/img/validButton.png" ) );
    b->setBorderOver( sf::Color::Green );
    b->setBorderSize(2);
    b->setPositionAbsolute( 400, 400 );
    b->setEvent( ge );
    m_ui.addWidget(b);

}

void NightState::draw( sf::RenderTarget & window )
{

    window.setView(window.getDefaultView());
    m_ui.draw(window);
}

void NightState::update( void )
{

}

void NightState::handleEvent( sf::Event & e )
{
    m_ui.handleEvent(e);
}

void NightState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_LESS_GATHERER :
        m_prctGatherer--;
        m_ui.getWidget("textGatherer")->setContent( new WidgetContent( "TEXT", itos(m_prctGatherer), sf::Color::White ) );
        break;

    case EV_MORE_GATHERER :
        m_prctGatherer++;
        m_ui.getWidget("textGatherer")->setContent( new WidgetContent( "TEXT", itos(m_prctGatherer), sf::Color::White ) );
        break;

    case EV_LESS_HUNTER :
        m_prctHunter--;
        m_ui.getWidget("textHunter")->setContent( new WidgetContent( "TEXT", itos(m_prctHunter), sf::Color::White ) );
        break;

    case EV_MORE_HUNTER :
        m_prctHunter++;
        m_ui.getWidget("textHunter")->setContent( new WidgetContent( "TEXT", itos(m_prctHunter), sf::Color::White ) );
        break;

    case EV_LESS_PICKMAN :
        m_prctPickman--;
        m_ui.getWidget("textPickman")->setContent( new WidgetContent( "TEXT", itos(m_prctPickman), sf::Color::White ) );
        break;

    case EV_MORE_PICKMAN :
        m_prctPickman++;
        m_ui.getWidget("textPickman")->setContent( new WidgetContent( "TEXT", itos(m_prctPickman), sf::Color::White ) );
        break;

    case EV_LESS_LUMBERJACK :
        m_prctLumberjack--;
        m_ui.getWidget("textLumberjack")->setContent( new WidgetContent( "TEXT", itos(m_prctLumberjack), sf::Color::White ) );
        break;

    case EV_MORE_LUMBERJACK :
        m_prctLumberjack++;
        m_ui.getWidget("textLumberjack")->setContent( new WidgetContent( "TEXT", itos(m_prctLumberjack), sf::Color::White ) );
        break;

        /// ---

    case EV_SELECT_RAIN :
        m_ui.getWidget("rainSelected")->setShow(true);
        m_ui.getWidget("sunSelected")->setShow(false);
        break;

    case EV_SELECT_SUN :
        m_ui.getWidget("sunSelected")->setShow(true);
        m_ui.getWidget("rainSelected")->setShow(false);
        break;

        /// ---


    case EV_VALID :
        StateManager::get()->popState();
        m_game->m_dayBeginTime = Time::get()->elapsed().asSeconds();
        m_game->m_weather->setWeatherToday(m_ui.getWidget("rainSelected")->isShow() ? RAINY : SUNNY);
        doIncidences(m_game->m_tilemap, m_game->m_weather, m_game->m_home.getPosition(), m_game->m_entityList);
        break;

    default :
        break;

    }
}
