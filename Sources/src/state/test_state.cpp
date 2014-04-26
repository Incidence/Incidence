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

#include <iostream>

TestState::TestState( sf::RenderWindow * window ) : m_game(NULL), m_dayDuration(30), m_dayBeginTime(0), m_night(true)
{
    m_game = new Game();
	m_window = window;
	sf::Vector2u windowSize = m_window->getSize();
	m_view = sf::View(sf::Vector2f(windowSize.x/2,windowSize.y/2), sf::Vector2f(windowSize.x,windowSize.y));
}

TestState::~TestState( void )
{
    if(m_game) {
        delete m_game;
    }
}

void TestState::init( void )
{

}

void TestState::draw( sf::RenderTarget & window )
{
	window.setView(m_view);
    m_game->draw(window);
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


            case sf::Keyboard::K :
            {
                StateManager::get()->addState(new NightState(m_game));
            } break;


            case sf::Keyboard::Escape :
            {
                StateManager::get()->popState();
            } break;

            default :
                break;

        }
    }
    m_game->handleEvent(e);
}

void TestState::treatEvent( GameEvent e ) {}


void TestState::updateDay( void )
{

    if(m_dayBeginTime + m_dayDuration - 5 < Time::get()->elapsed().asSeconds()) {
        // ALL GO_HOME
    }

    if(m_dayBeginTime + m_dayDuration < Time::get()->elapsed().asSeconds()) {
        StateManager::get()->addState( new NightState(m_game) );
        m_night = true;
    }
}
