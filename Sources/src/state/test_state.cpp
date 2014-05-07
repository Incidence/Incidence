#include "test_state.hpp"

#include "../engine/state_manager.hpp"
#include "../engine/time.hpp"

#include "../game/game.hpp"
#include "../game/entity/entity.hpp"
#include "../game/entity/lumberjack.hpp"
#include "../game/entity/enemy_citizen.hpp"
#include "../game/entity/gatherer.hpp"
#include "../game/entity/hunter.hpp"
#include "../game/entity/peaceful_animal.hpp"
#include "../game/entity/wild_animal.hpp"
#include "../game/entity/pickman.hpp"

#include "night_state.hpp"
#include "game_menu_state.hpp"

#include "../engine/ui/button.hpp"
#include "../engine/ui/container.hpp"

#include <iostream>

TestState::TestState( sf::RenderWindow * window ) : m_game(NULL), m_dayDuration(30), m_dayBeginTime(0), m_night(true), m_ui(this)
{
    m_game = new Game();
	m_window = window;
	sf::Vector2u windowSize = m_window->getSize();
	m_view = sf::View(sf::Vector2f(windowSize.x/2,windowSize.y/2), sf::Vector2f(windowSize.x,windowSize.y));

	init();
}

TestState::~TestState( void )
{
    if(m_game) {
        delete m_game;
    }
}

void TestState::init( void )
{
    Container * c;
    Button * b;
    Widget * w;

    c = new Container;
    c->setBackground(sf::Color(150, 150, 150));
    c->setSize(800, 20);
    c->setPositionRelative(TOP);
    c->setPositionRelative(LEFT);

    w = new Widget;
    w->setName("PI_compteur");
    w->setText( "PI : " + itos(m_game->m_incidencePoint), sf::Color::White );
    w->setPositionAbsolute( 50, 5 );

    c->addWidget(w);
    m_ui.addWidget(c);


    c = new Container;
    c->setName("cont_selection");
    c->setBackground(sf::Color(150, 150, 150));
    c->setSize(30, 600);
    c->setPositionAbsolute(770, 0);
    m_ui.addWidget(c);

    GameEvent ge;

    b = new Button;
    b->setText("Sols");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_SOL;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 30 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("Elements");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_ELEMENT;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 60 );
    b->setEvent( ge );
    c->addWidget(b);

    /// ----

    c = new Container;
    c->setName("cont_sols");
    c->setBackground(sf::Color(150, 150, 150));
    c->setSize(30, 600);
    c->setPositionAbsolute(770, 0);
    c->setShow(false);
    m_ui.addWidget(c);

    b = new Button;
    b->setText("falaise");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_FALAISE;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 30 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("sable");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_SABLE;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 60 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("terre");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_TERRE_SECHE;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 90 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("herbe");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_TERRE;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 120 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("herbe mouillé");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_TERRE_INNONDE;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 150 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("eau");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_EAU;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 180 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("retour");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_CANCEL;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 250 );
    b->setEvent( ge );
    c->addWidget(b);


    /// ----

    c = new Container;
    c->setName("cont_elem");
    c->setBackground(sf::Color(150, 150, 150));
    c->setSize(30, 600);
    c->setPositionAbsolute(770, 0);
    c->setShow(false);
    m_ui.addWidget(c);

    b = new Button;
    b->setText("arbre");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_ARBRE;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 30 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("pierre");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_PIERRE;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 60 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("fruit");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_FRUITIER;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 90 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("buisson");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_SELECT_BUISSON;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 120 );
    b->setEvent( ge );
    c->addWidget(b);

    b = new Button;
    b->setText("retour");
    b->setBorderOver(sf::Color::Red);
    b->setBorderSize(1);
    ge.type = EV_CANCEL;
    b->setPositionAbsolute(770, 0);
    b->move( 5, 250 );
    b->setEvent( ge );
    c->addWidget(b);
}

void TestState::draw( sf::RenderTarget & window )
{
	window.setView(m_view);
    m_game->draw(window);
    window.setView(window.getDefaultView());
    m_ui.draw(window);
}

void TestState::update( void )
{
    if(m_night) {
        m_dayBeginTime = Time::get()->elapsed().asSeconds();
        m_night = false;
    }

	sf::Vector2u dimensions = (m_game->getTilemap())->getDimensions();
	sf::Vector2u tilesize = ((m_game->getTilemap())->getTileSet())->getTileSize();
	Animation* Rain = m_game->getWeather()->getRainAnimation();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_view.getCenter().x > m_view.getSize().x/2) {
		m_view.move(-((int)tilesize.x),0);
		if(Rain->m_position.x>=32)
            {
                Rain->m_position.x-=32;
            }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_view.getCenter().x < dimensions.x*tilesize.x-m_view.getSize().x/2) {
		m_view.move(tilesize.x,0);
		if(Rain->m_position.x<(150-(800/32))*32)
            {
                Rain->m_position.x+=32;
            }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_view.getCenter().y > m_view.getSize().y/2) {
		m_view.move(0,-((int)tilesize.y));
		if(Rain->m_position.y>=32)
            {
                Rain->m_position.y-=32;
            }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_view.getCenter().y < dimensions.y*tilesize.y-m_view.getSize().y/2) {
		m_view.move(0,tilesize.y);
		if(Rain->m_position.y<(150-(600/32))*32)
            {
                Rain->m_position.y+=32;
            }
	}

    updateDay();
    m_game->update();

    m_ui.getWidget("PI_compteur")->setText("PI : " + itos(m_game->m_incidencePoint), sf::Color::White);
}

void TestState::handleEvent( sf::Event & e )
{
    if( e.type == sf::Event::KeyPressed )
    {
        switch(e.key.code)
        {
            case sf::Keyboard::A :
            {
                m_game->addEntity(new Lumberjack(ALLY_CITIZEN, m_game));
            } break;

            case sf::Keyboard::Z :
            {
                m_game->addEntity(new Gatherer(ALLY_CITIZEN, m_game));
            } break;

            case sf::Keyboard::E :
            {
                m_game->addEntity(new EnemyCitizen(ENEMY_CITIZEN, m_game));
            } break;

            case sf::Keyboard::R :
            {
                m_game->addEntity(new Hunter(HUNTER, m_game));
            } break;

            case sf::Keyboard::T :
            {
                m_game->addEntity(new PeacefulAnimal(PEACEFUL_ANIMAL, m_game));
            } break;

            case sf::Keyboard::Y :
            {
                m_game->addEntity(new WildAnimal(WILD_ANIMAL, m_game));
            } break;

            case sf::Keyboard::U :
            {
                m_game->addEntity(new Pickman(ALLY_CITIZEN, m_game));
            } break;



            case sf::Keyboard::S :
            {
                if(e.key.control) {
                    m_game->saveGame("saves/test.save");
                    m_night = true;
                }
            } break;

            case sf::Keyboard::O :
            {
                if(e.key.control) {
                    m_game->loadGame("saves/test.save");
                    m_night = true;
                }
            } break;

            case sf::Keyboard::K :
            {
                StateManager::get()->addState(new NightState(m_game));
            } break;


            case sf::Keyboard::Escape :
            {
                StateManager::get()->addState(new GameMenuState(m_game));
            } break;

            default :
                break;

        }
    }


    if(! m_ui.handleEvent(e)) {
        if ( e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && m_element != -1 ) {
            if(m_element == 0) {
                m_game->actionGround(m_select, m_game->m_tilemap->getXY(sf::Vector2f(e.mouseButton.x + m_view.getCenter().x - m_view.getSize().x/2, e.mouseButton.y + m_view.getCenter().y - m_view.getSize().y/2)));
            } else if(m_element == 1) {
                m_game->actionElement(m_select, m_game->m_tilemap->getXY(sf::Vector2f(e.mouseButton.x, e.mouseButton.y)));
            }
        }
    }

     if ( e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right ) {
            m_select = -1;
    }

    m_game->handleEvent(e);
}

void TestState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_SELECT_SOL :
        m_ui.getWidget("cont_sols")->setShow(true);
        m_ui.getWidget("cont_selection")->setShow(false);
        m_ui.getWidget("cont_elem")->setShow(false);
        std::cout << "selec sol" << std::endl;
        m_element = 0;
        break;

    case EV_SELECT_ELEMENT :
        m_ui.getWidget("cont_sols")->setShow(false);
        m_ui.getWidget("cont_selection")->setShow(false);
        m_ui.getWidget("cont_elem")->setShow(true);
        std::cout << "selec elem" << std::endl;
        m_element = 1;
        break;

    case EV_CANCEL :
        m_ui.getWidget("cont_sols")->setShow(false);
        m_ui.getWidget("cont_selection")->setShow(true);
        m_ui.getWidget("cont_elem")->setShow(false);
        std::cout << "cancel" << std::endl;
        m_element = -1;
        break;

/// //

    case EV_SELECT_FALAISE :
        m_select = 5;
        std::cout << "fal sol" << std::endl;
        break;

    case EV_SELECT_SABLE :
        m_select = 4;
        std::cout << "sable sol" << std::endl;
        break;

    case EV_SELECT_TERRE_SECHE :
        m_select = 3;
        std::cout << "sec sol" << std::endl;
        break;

    case EV_SELECT_TERRE :
        m_select = 2;
        std::cout << "terre sol" << std::endl;
        break;

    case EV_SELECT_TERRE_INNONDE :
        m_select = 1;
        std::cout << "inno sol" << std::endl;
        break;

    case EV_SELECT_EAU :
        m_select = 0;
        std::cout << "eau sol" << std::endl;
        break;


    case EV_SELECT_ARBRE :
        m_select = 0;
        std::cout << "arbre sol" << std::endl;
        break;

    case EV_SELECT_FRUITIER :
        m_select = 1;
        std::cout << "fruit sol" << std::endl;
        break;

    case EV_SELECT_BUISSON :
        m_select = 2;
        std::cout << "buisson sol" << std::endl;
        break;

    case EV_SELECT_PIERRE :
        m_select = 3;
        std::cout << "roch sol" << std::endl;
        break;

    default :
        break;

    }
}


void TestState::updateDay( void )
{

    if(m_dayBeginTime + m_dayDuration - 5 < Time::get()->elapsed().asSeconds()) {
        // ALL GO_HOME
        m_game->allHome();
    }

    if(m_dayBeginTime + m_dayDuration < Time::get()->elapsed().asSeconds()) {
        StateManager::get()->addState( new NightState(m_game) );
        m_night = true;
    }
}
