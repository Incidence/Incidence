#include "night_state.hpp"

#include "../engine/state_manager.hpp"
#include "../engine/ui/button.hpp"
#include "../engine/time.hpp"

#include "../game/entity/lumberjack.hpp"
#include "../game/entity/enemy_citizen.hpp"
#include "../game/entity/gatherer.hpp"
#include "../game/entity/hunter.hpp"
#include "../game/entity/peaceful_animal.hpp"
#include "../game/entity/wild_animal.hpp"
#include "../game/entity/pickman.hpp"

#include "../engine/data_manager.hpp"

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
    w->setSprite( DataManager::get()->getSprite( "data/img/nightBackground.png" ) );
    w->setPositionAbsolute( 0, 0 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Lumberjack % : ", sf::Color::Black );
    w->setPositionAbsolute( 100, 40 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Hunter % : ", sf::Color::Black );
    w->setPositionAbsolute( 100, 80 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Pickman % : ", sf::Color::Black );
    w->setPositionAbsolute( 100, 120 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Gatherer % : ", sf::Color::Black );
    w->setPositionAbsolute( 100, 160 );
    m_ui.addWidget(w);

    // ------

    w = new Widget();
    w->setName("textLumberjack");
    w->setText( itos(prct(m_prctLumberjack)), sf::Color::Black );
    w->setPositionAbsolute( 300, 40 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setName("textHunter");
    w->setText( itos(prct(m_prctHunter)), sf::Color::Black );
    w->setPositionAbsolute( 300, 80 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setName("textPickman");
    w->setText( itos(prct(m_prctPickman)), sf::Color::Black );
    w->setPositionAbsolute( 300, 120 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setName("textGatherer");
    w->setText( itos(prct(m_prctGatherer)), sf::Color::Black );
    w->setPositionAbsolute( 300, 160 );
    m_ui.addWidget(w);

    // -----

    GameEvent ge;
    ge.type = EV_MORE_LUMBERJACK;

    b = new Button();
    b->setText( "+", sf::Color::Green );
    b->setBorder( sf::Color::Black );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 250, 40 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_HUNTER;

    b = new Button();
    b->setText( "+", sf::Color::Green );
    b->setBorder( sf::Color::Black );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 250, 80 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_PICKMAN;

    b = new Button();
    b->setText( "+", sf::Color::Green );
    b->setBorder( sf::Color::Black );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 250, 120 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_GATHERER;

    b = new Button();
    b->setText( "+", sf::Color::Green );
    b->setBorder( sf::Color::Black );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 250, 160 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    // -----

    ge.type = EV_LESS_LUMBERJACK;

    b = new Button();
    b->setText( "-", sf::Color::Red );
    b->setBorder( sf::Color::Black );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 340, 40 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LESS_HUNTER;

    b = new Button();
    b->setText( "-", sf::Color::Red );
    b->setBorder( sf::Color::Black );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 340, 80 );
    b->setSize(32, 32);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LESS_PICKMAN;

    b = new Button();
    b->setName("d");
    b->setText( "-", sf::Color::Red );
    b->setBorder( sf::Color::Black );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 340, 120 );
    b->setSize( 32, 32 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_LESS_GATHERER;

    b = new Button();
    b->setText( "-", sf::Color::Red );
    b->setBorder( sf::Color::Black );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute(340, 160 );
    b->setSize( 32, 32 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    // ----------

    ge.type = EV_SELECT_RAIN;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/rainButton.png" ) );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 200, 300 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    w = new Widget();
    w->setName("rainSelected");
    w->setShow(false);
    w->setSprite( DataManager::get()->getSprite( "data/img/validButton.png" ) );
    w->setPositionAbsolute( 240, 300 );
    m_ui.addWidget(w);


    ge.type = EV_SELECT_SUN;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/sunButton.png" ) );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 300 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    w = new Widget();
    w->setName("sunSelected");
    w->setShow(true);
    w->setSprite( DataManager::get()->getSprite( "data/img/validButton.png" ) );
    w->setPositionAbsolute( 340, 300 );
    m_ui.addWidget(w);

    // ----------

    ge.type = EV_VALID;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/validButton.png" ) );
    b->setBorderOver( sf::Color::Green );
    b->setBorderSize(2);
    b->setPositionAbsolute( 400, 400 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    //ge.type = EV_RESET; -> réinitialise les paramètres ??

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/resetButton.png" ) );
    b->setBorderOver( sf::Color::Red );
    b->setBorderSize(2);
    b->setPositionAbsolute( 150, 400 );
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
        break;

    case EV_MORE_GATHERER :
        m_prctGatherer++;
        break;

    case EV_LESS_HUNTER :
        m_prctHunter--;
        break;

    case EV_MORE_HUNTER :
        m_prctHunter++;
        break;

    case EV_LESS_PICKMAN :
        m_prctPickman--;
        break;

    case EV_MORE_PICKMAN :
        m_prctPickman++;
        break;

    case EV_LESS_LUMBERJACK :
        m_prctLumberjack--;
        break;

    case EV_MORE_LUMBERJACK :
        m_prctLumberjack++;
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
        validation();
        break;

    default :
        break;

    }

    if(m_prctGatherer < 0) { m_prctGatherer = 0; }
    if(m_prctHunter < 0) { m_prctHunter = 0; }
    if(m_prctLumberjack < 0) { m_prctLumberjack = 0; }
    if(m_prctPickman < 0) { m_prctPickman = 0; }

    m_ui.getWidget("textGatherer")->setText( itos(prct(m_prctGatherer)), sf::Color::White );
    m_ui.getWidget("textLumberjack")->setText( itos(prct(m_prctLumberjack)), sf::Color::White );
    m_ui.getWidget("textPickman")->setText( itos(prct(m_prctPickman)), sf::Color::White );
    m_ui.getWidget("textHunter")->setText( itos(prct(m_prctHunter)), sf::Color::White );
}


int NightState::prct(int v)
{
    return (v*100) / (m_prctGatherer + m_prctHunter + m_prctLumberjack + m_prctPickman);
}


void NightState::validation( void )
{
    StateManager::get()->popState();

    allyCitizenDeath(m_game);
    int nb = allyCitizenBirth(m_game);

    std::cout << "new : " << nb << std::endl;

    doIncidences(m_game->m_tilemap, m_game->m_weather, m_game->m_home.getPosition(), m_game->m_entityList);
    m_game->m_weather->setWeatherToday(m_ui.getWidget("rainSelected")->isShow() ? RAINY : SUNNY);

    m_game->clearEntity();

    for(int i = 0; i < nb; i++) {

        int r = rand() % 100;

        if(r < prct(m_prctGatherer)) {
            m_game->addEntity( new Gatherer(ALLY_CITIZEN, m_game));
        } else if (r < prct(m_prctGatherer + m_prctHunter)) {
            m_game->addEntity( new Hunter(HUNTER, m_game));
        } else if (r < prct(m_prctGatherer + m_prctHunter + m_prctLumberjack)) {
            m_game->addEntity( new Lumberjack(ALLY_CITIZEN, m_game));
        } else {
            m_game->addEntity( new Pickman(ALLY_CITIZEN, m_game));
        }
    }

    for(int i = 0; i < wildAnimalBirth(m_game); i++) {
        m_game->addEntity( new WildAnimal(WILD_ANIMAL, m_game));
    }

    for(int i = 0; i < peacefulAnimalBirth(m_game); i++) {
        m_game->addEntity( new PeacefulAnimal(PEACEFUL_ANIMAL, m_game));
    }

    for(int i = 0; i < enemyCitizenBirth(m_game); i++) {
        m_game->addEntity( new EnemyCitizen(ENEMY_CITIZEN, m_game));
    }
}
