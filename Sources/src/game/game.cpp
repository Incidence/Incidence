#include "game.hpp"

#include <list>

#include "level/tileset.hpp"
#include "../engine/foo.hpp"
#include "../engine/time.hpp"


/// TODO
Game::Game( void ) : m_tilemap(NULL), m_dayDuration(5), m_dayBeginTime(0)
{
    newGame();
}

Game::~Game( void )
{
    if(m_tilemap) {
        delete m_tilemap;
    }

    if(m_weather)
    {
        delete m_weather;
    }

    for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        delete *it;
    }
}

void Game::newGame( void )
{
    if(m_tilemap) {
        delete m_tilemap;
    }

    m_tilemap = new TileMap(TileSet("data/tileset.ini"), sf::Vector2u(150, 150));
	m_tilemap->generate();
	m_weather=new Weather(RAINY,"data/rain.ani");
	m_incidencePoint=0;
}

void Game::loadGame( std::string path ) {}
void Game::saveGame( std::string path ) {}

void Game::update( void )
{
    updateDay();

    for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        if( !(*it)->isDead() ) {
            (*it)->callScript();
            float temps=Time::get()->elapsed().asMilliseconds();
            if((*it)->getGiveTime()<temps)
            {
                m_incidencePoint+=(*it)->getGiveQuantity();
                //std::cout<<"nbpi : "<<m_incidencePoint<<std::endl; //pour le debug voir le nombre de PI courant
                (*it)->updateGiveTime(temps);
            }
        }
    }
}

void Game::draw( sf::RenderTarget & window )
{
    m_tilemap->drawGrounds( window );
    m_tilemap->drawElementsDown( window );
    
    for(std::vector< Building >::iterator it = m_buildings.begin(); it != m_buildings.end(); it++) {
    	(*it).drawBottom( window );
    }

    for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        if( !(*it)->isDead() ) {
            window.draw( * (*it)->draw() );
        }
    }
    m_tilemap->drawElementsUp( window );
    
    for(std::vector< Building >::iterator it = m_buildings.begin(); it != m_buildings.end(); it++) {
    	(*it).drawTop( window );
    }
    
    m_weather->draw(window);
}

void Game::handleEvent( sf::Event & e )
{
    if (e.type == sf::Event::MouseButtonPressed) {
        if( m_entityList.size() > 0 ) {
            m_entityList[0]->setPosition(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
        }
    }
    if (e.type == sf::Event::KeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			dilateFluids(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			erodeFluids(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			dilateNearFluids(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			erodeNearFluids(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
			dilateForests(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
			erodeForests(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
			dilateNearCliffs(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
			erodeNearCliffs(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
			burnRessources(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
			spawnRessources(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_tilemap->save("saves/test.ims");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
			m_tilemap->load("saves/test.ims");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			m_weather->setWeatherToday(SUNNY);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			m_weather->setWeatherToday(RAINY);
		}


    }
}

TileMap * Game::getTilemap( void ) {

	return m_tilemap;

}

Entity * Game::getEntity( int id )
{
    if(id >= 0 && id < (int)m_entityList.size()) {
        return m_entityList[id];
    } else {
        return NULL;
    }
}

std::vector< Entity * > Game::getEntities( void )
{
    return m_entityList;
}

 Weather * Game::getWeather()
 {
     return m_weather;
 }

void Game::addEntity( Entity * e )
{
    m_entityList.push_back(e);
}


void Game::setPI(int n)
{
    m_incidencePoint=n;
}

int Game::getPI()
{
    return m_incidencePoint;
}

void Game::updateDay( void )
{
    if(m_dayBeginTime + m_dayDuration < Time::get()->elapsed().asSeconds()) {
        m_dayBeginTime = Time::get()->elapsed().asSeconds();

        int i = rand() % 2;
        m_weather->setWeatherToday(i==0 ? RAINY : SUNNY);
        std::cout << "New DAY ! (" << (i==0 ? "RAINY" : "SUNNY") << ")" << std::endl;
        doIncidences(m_tilemap,m_weather);
    }
}


