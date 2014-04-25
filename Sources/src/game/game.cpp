#include "game.hpp"

#include <list>

#include "level/tileset.hpp"
#include "../engine/foo.hpp"
#include "../engine/time.hpp"


/// TODO
Game::Game( void ) : m_tilemap(NULL), m_dayDuration(50000), m_dayBeginTime(0)
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

	m_home.load("data/buildings/home.bld");
	m_home.setPosition(10, 10);
	m_buildings.push_back(m_home);

	m_tilemap->freePlace(m_home.getPosition());
}

void Game::spawnEntity( Entity & e )
{
    if ((e.m_type == ALLY_CITIZEN) || (e.m_type == HUNTER))
    {
        e.setPosition(sf::Vector2f((this->m_home.getPosition().x*32)+16,(this->m_home.getPosition().y*32)+16));
    }
    else if ((e.m_type == WILD_ANIMAL) || (e.m_type == PEACEFUL_ANIMAL))
    {
        int x(rand() % (this->m_tilemap->getDimensions().x));
        int y;
        if ((x > (this->m_home.getPosition().x-5)) || (x < (this->m_home.getPosition().x+5)))
        {
            y = rand() % (this->m_tilemap->getDimensions().y-9);
            if (y > (this->m_home.getPosition().y-5))
            {
                y += 9;
            }
        }
        else
        {
            y = (rand() % (this->m_tilemap->getDimensions().y));
        }
        this->m_tilemap->freePlace(sf::Vector2i(x,y));
        e.setPosition(sf::Vector2f((x*32)+16,(y*32)+16));
    }
    else if (e.m_type == ENEMY_CITIZEN)
    {
        unsigned int x(rand() % (this->m_tilemap->getDimensions().x));
        unsigned int y;
        if ((x > 4) && (x < (this->m_tilemap->getDimensions().x-5)))
        {
            y = rand() % 10;
            if (y > 4)
            {
                y += (this->m_tilemap->getDimensions().y-10);
            }
        }
        else
        {
            y = rand() % (this->m_tilemap->getDimensions().y);
        }
        this->m_tilemap->freePlace(sf::Vector2i(x,y));
        e.setPosition(sf::Vector2f((x*32)+16,(y*32)+16));
    }
    else
    {
        std::cerr << "In \"void Game::spawnEntity( Entity & e )\" : unexpected value of \"e\" !" << std::endl;
    }
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
        m_tilemap->userSetGround(3,m_tilemap->getXY(sf::Vector2f(e.mouseButton.x, e.mouseButton.y)));
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
    spawnEntity(*e);
}


void Game::setPI(int n)
{
    m_incidencePoint=n;
}

int Game::getPI()
{
    return m_incidencePoint;
}

int Game::getQtyWood() {

	return qtyWood;

}

int Game::getQtyFood() {

	return qtyFood;

}

int Game::getQtyStone() {

	return qtyStone;

}

void Game::updateDay( void )
{
    if(m_dayBeginTime + m_dayDuration < Time::get()->elapsed().asSeconds()) {
        m_dayBeginTime = Time::get()->elapsed().asSeconds();

        int i = rand() % 2;
        m_weather->setWeatherToday(i==0 ? RAINY : SUNNY);
        std::cout << "New DAY ! (" << (i==0 ? "RAINY" : "SUNNY") << ")" << std::endl;
        doIncidences(m_tilemap,m_weather, m_home.getPosition(),m_entityList);
    }
}

void Game::addRessource(RessourceType t, int qty)
{
    switch(t) {
        case FOOD :
            qtyFood += qty;
            break;
        case WOOD :
            qtyWood += qty;
            break;
        case STONE :
            qtyStone += qty;
            break;
        default :
            break;
    }
}

