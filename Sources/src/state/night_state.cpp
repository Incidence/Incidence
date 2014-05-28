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
    m_prctLumberjack = 25;
    m_prctPickman = 25;
    m_prctHunter = 25;
    m_prctGatherer = 25;

    Widget * w;
    Button * b;

    w = new Widget();
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/nightBackground.png" ) );
    w->setPositionAbsolute( 0, 0 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Lumberjack", sf::Color::White );
    w->setPositionAbsolute( 110, 10 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Hunter", sf::Color::White );
    w->setPositionAbsolute( 10, 110 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Pickman", sf::Color::White );
    w->setPositionAbsolute( 240, 110 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Gatherer", sf::Color::White );
    w->setPositionAbsolute( 110, 290 );
    m_ui.addWidget(w);

    // ------

    GameEvent ge;
    ge.type = EV_MORE_LUMBERJACK;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/plus.png" ) );
    b->setBorder( sf::Color::White );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 150, 40 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_HUNTER;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/plus.png" ) );
    b->setBorder( sf::Color::White );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 40, 150 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_PICKMAN;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/plus.png" ) );
    b->setBorder( sf::Color::White );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 260, 150 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_MORE_GATHERER;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/plus.png" ) );
    b->setBorder( sf::Color::White );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 150, 260 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    // ----------

    ge.type = EV_SELECT_RAIN;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/rainButton.png" ) );
    b->setBorderOver( sf::Color::White );
    b->setBorderSize(1);
    b->setPositionAbsolute( 50, 420 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    w = new Widget();
    w->setName("rainSelected");
    w->setShow(false);
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/validButton.png" ) );
    w->setPositionAbsolute( 90, 420 );
    m_ui.addWidget(w);


    ge.type = EV_SELECT_SUN;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/sunButton.png" ) );
    b->setBorderOver( sf::Color::White );
    b->setBorderSize(1);
    b->setPositionAbsolute( 200, 420 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    w = new Widget();
    w->setName("sunSelected");
    w->setShow(true);
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/validButton.png" ) );
    w->setPositionAbsolute( 240, 420 );
    m_ui.addWidget(w);

    // ----------

    ge.type = EV_VALID;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/validButton.png" ) );
    b->setBorderOver( sf::Color::White );
    b->setBorderSize(2);
    b->setPositionAbsolute( 250, 520 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_RESET;

    b = new Button();
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/resetButton.png" ) );
    b->setBorderOver( sf::Color::White );
    b->setBorderSize(2);
    b->setPositionAbsolute( 50, 520 );
    b->setEvent( ge );
    m_ui.addWidget(b);

    m_probabilityShape.setPointCount(4);
    m_probabilityShape.setFillColor(sf::Color::White);
    m_probabilityShape.setPoint(0,sf::Vector2f(135,160));
    m_probabilityShape.setPoint(1,sf::Vector2f(160,135));
    m_probabilityShape.setPoint(2,sf::Vector2f(185,160));
    m_probabilityShape.setPoint(3,sf::Vector2f(160,185));


    w = new Widget();
    w->setText( "Night "+itos(m_game->getDaysCount()+1), sf::Color::White );
    w->setTextSize(50);
    w->setPositionAbsolute( 450, 20 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Population : "+itos(m_game->getPopulation().size()), sf::Color::White );
    w->setTextSize(20);
    w->setPositionAbsolute( 460, 100 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Food : "+itos(m_game->getQtyFood()), sf::Color::White );
    w->setTextSize(20);
    w->setPositionAbsolute( 460, 150 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Wood : "+itos(m_game->getQtyWood()), sf::Color::White );
    w->setTextSize(20);
    w->setPositionAbsolute( 460, 200 );
    m_ui.addWidget(w);

    w = new Widget();
    w->setText( "Stone : "+itos(m_game->getQtyStone()), sf::Color::White );
    w->setTextSize(20);
    w->setPositionAbsolute( 460, 250 );
    m_ui.addWidget(w);
}

void NightState::draw( sf::RenderTarget & window )
{
    window.setView(window.getDefaultView());
    m_ui.draw(window);
    window.draw(m_probabilityShape);
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

    case EV_MORE_GATHERER :
        {
            unsigned int temp(0);
            if (m_prctHunter > 5)
            {
                m_prctHunter--;
                temp++;
            }
            if (m_prctLumberjack > 5)
            {
                m_prctLumberjack--;
                temp++;
            }
            if (m_prctPickman > 5)
            {
                m_prctPickman--;
                temp++;
            }
            m_prctGatherer += temp;
        }
        break;

    case EV_MORE_HUNTER :
        {
            unsigned int temp(0);
            if (m_prctGatherer > 5)
            {
                m_prctGatherer--;
                temp++;
            }
            if (m_prctLumberjack > 5)
            {
                m_prctLumberjack--;
                temp++;
            }
            if (m_prctPickman > 5)
            {
                m_prctPickman--;
                temp++;
            }
            m_prctHunter += temp;
        }
        break;

    case EV_MORE_PICKMAN :
        {
            unsigned int temp(0);
            if (m_prctHunter > 5)
            {
                m_prctHunter--;
                temp++;
            }
            if (m_prctLumberjack > 5)
            {
                m_prctLumberjack--;
                temp++;
            }
            if (m_prctGatherer > 5)
            {
                m_prctGatherer--;
                temp++;
            }
            m_prctPickman += temp;
        }
        break;

    case EV_MORE_LUMBERJACK :
        {
            unsigned int temp(0);
            if (m_prctHunter > 5)
            {
                m_prctHunter--;
                temp++;
            }
            if (m_prctGatherer > 5)
            {
                m_prctGatherer--;
                temp++;
            }
            if (m_prctPickman > 5)
            {
                m_prctPickman--;
                temp++;
            }
            m_prctLumberjack += temp;
        }
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

    case EV_RESET :
        {
            m_prctGatherer = 25;
            m_prctHunter = 25;
            m_prctLumberjack = 25;
            m_prctPickman = 25;
            m_ui.getWidget("sunSelected")->setShow(true);
            m_ui.getWidget("rainSelected")->setShow(false);
        }
        break;

    default :
        break;

    }

    m_probabilityShape.setPoint(0,sf::Vector2f(160-m_prctHunter,160));
    m_probabilityShape.setPoint(1,sf::Vector2f(160,160-m_prctLumberjack));
    m_probabilityShape.setPoint(2,sf::Vector2f(160+m_prctPickman,160));
    m_probabilityShape.setPoint(3,sf::Vector2f(160,160+m_prctGatherer));
}


void NightState::validation( void )
{
    StateManager::get()->popState();

    allyCitizenDeath(m_game);
    int nb = allyCitizenBirth(m_game);
    int wa = wildAnimalBirth(m_game), pa = peacefulAnimalBirth(m_game), ce = enemyCitizenBirth(m_game);

    std::cout << "new : " << nb << std::endl;

/// RECODE
    std::vector< Entity * > ee = m_game->getPopulation();
    std::vector< Entity * > newAlly;

    for(int i = 0; i < nb; i++) {

        Entity * et = NULL;
        if(i < (int)ee.size()) {
            et = ee[i];
        }

        int r = rand() % 100;

        if(r < m_prctGatherer) {
            newAlly.push_back( new Gatherer(ALLY_CITIZEN, m_game, et));
        } else if (r < (m_prctGatherer + m_prctHunter)) {
            newAlly.push_back( new Hunter(HUNTER, m_game, et));
        } else if (r < (m_prctGatherer + m_prctHunter + m_prctLumberjack)) {
            newAlly.push_back( new Lumberjack(ALLY_CITIZEN, m_game, et));
        } else {
            newAlly.push_back( new Pickman(ALLY_CITIZEN, m_game, et));
        }
    }

    m_game->clearEntity();
    m_game->addEntities(newAlly);


    for(int i = 0; i < wa; i++) {
        m_game->addEntity( new WildAnimal(WILD_ANIMAL, m_game));
    }

    for(int i = 0; i < pa; i++) {
        m_game->addEntity( new PeacefulAnimal(PEACEFUL_ANIMAL, m_game));
    }

    for(int i = 0; i < ce; i++) {
        m_game->addEntity( new EnemyCitizen(ENEMY_CITIZEN, m_game));
    }

    updateRessources(m_game);
    doIncidences(m_game->m_tilemap, m_game->m_weather, m_game->m_home.getPosition(), m_game->m_entityList);
    m_game->m_weather->setWeatherToday(m_ui.getWidget("rainSelected")->isShow() ? RAINY : SUNNY);

    m_game->incrementDaysCount();
}
