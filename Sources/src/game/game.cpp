#include "game.hpp"

#include <list>

#include "level/tileset.hpp"
#include "../engine/foo.hpp"
#include "../engine/time.hpp"
#include "../engine/state_manager.hpp"
#include "../state/night_state.hpp"

#include "../game/entity/entity.hpp"
#include "../game/entity/lumberjack.hpp"
#include "../game/entity/enemy_citizen.hpp"
#include "../game/entity/gatherer.hpp"
#include "../game/entity/hunter.hpp"
#include "../game/entity/peaceful_animal.hpp"
#include "../game/entity/wild_animal.hpp"
#include "../game/entity/pickman.hpp"

/// TODO
Game::Game( void ) : m_tilemap(NULL)
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
	m_weather=new Weather(RAINY,"data/ani/rain.ani");
	m_incidencePoint=0;

	m_home.load("data/buildings/home.bld");
	m_home.setPosition(10, 10);
	m_buildings.push_back(m_home);

	m_tilemap->freePlace(m_home.getPosition());

	this->addEntity( new Gatherer(ALLY_CITIZEN, this));
	this->addEntity( new Hunter(HUNTER, this));
	this->addEntity( new Lumberjack(ALLY_CITIZEN, this));
	this->addEntity( new Pickman(ALLY_CITIZEN, this));

	for(int i(0) ; i < 10 ; ++i) {
		this->addEntity( new EnemyCitizen(ENEMY_CITIZEN, this));
		this->addEntity( new PeacefulAnimal(PEACEFUL_ANIMAL, this));
		this->addEntity( new WildAnimal(WILD_ANIMAL, this));
	}

	//(m_tilemap->getTileSet())->TEST();
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

void Game::loadGame( std::string path )
{

	std::ifstream file( path.c_str() );
	if(!file) {
		std::cout << "Ouverture du fichier de sauvegarde de la partie impossible." << std::endl;
	}

	file >> path;

	m_tilemap->load( path );


    file >> qtyFood >> qtyStone >> qtyWood;
    file >> m_incidencePoint;

    unsigned int gatherer = 0, lumberjack = 0, pickman = 0, hunter = 0, wild = 0, peaceful = 0, enemy = 0, m = 0;
    char w = 's';

    file >> gatherer >> lumberjack >> pickman >> hunter >> wild >> peaceful >> enemy;
    file >> m >> w;
    m_weather->setWeatherGrade(m);

    if(w == 'r') {
        m_weather->setWeatherToday(RAINY);
    } else {
        m_weather->setWeatherToday(SUNNY);
    }

    m_entityList.clear();

    for(unsigned int g = 0; g < gatherer; g++) {
        addEntity(new Gatherer(ALLY_CITIZEN, this));
    }

    for(unsigned int l = 0; l < lumberjack; l++) {
        addEntity(new Lumberjack(ALLY_CITIZEN, this));
    }

    for(unsigned int p = 0; p < pickman; p++) {
        addEntity(new Pickman(ALLY_CITIZEN, this));
    }

    for(unsigned int h = 0; h < hunter; h++) {
        addEntity(new Hunter(HUNTER, this));
    }

    for(unsigned int w = 0; w < wild; w++) {
        addEntity(new WildAnimal(WILD_ANIMAL, this));
    }

    for(unsigned int a = 0; a < peaceful; a++) {
        addEntity(new PeacefulAnimal(PEACEFUL_ANIMAL, this));
    }

    for(unsigned int e = 0; e < enemy; e++) {
        addEntity(new EnemyCitizen(ENEMY_CITIZEN, this));
    }

}

void Game::saveGame( std::string path )
{
	std::ofstream file( path.c_str() );
	if(!file) {
		std::cout << "Ecriture du fichier de sauvegarde de la partie impossible." << std::endl;
	}

    m_tilemap->save( path.append(".map") );

    file << path << std::endl;

    file << qtyFood << " " << qtyStone << " " << qtyWood << std::endl;
    file << m_incidencePoint << std::endl;

    int gatherer = 0, lumberjack = 0, pickman = 0, hunter = 0, wild = 0, peaceful = 0, enemy = 0;

    for(unsigned int i = 0; i < m_entityList.size(); i++) {
        if(!m_entityList[i]->isDead()) {
            if(m_entityList[i]->m_job == 'g') {
                gatherer++;
            } else if(m_entityList[i]->m_job == 'l') {
                lumberjack++;
            } else if(m_entityList[i]->m_job == 'p') {
                pickman++;
            } else if(m_entityList[i]->m_job == 'h') {
                hunter++;
            } else if(m_entityList[i]->m_job == 'w') {
                wild++;
            } else if(m_entityList[i]->m_job == 'a') {
                peaceful++;
            } else if(m_entityList[i]->m_job == 'e') {
                enemy++;
            }
        }
    }

    file << gatherer << " " << lumberjack << " " << pickman << " " << hunter << " " << wild << " " << peaceful << " " << enemy << std::endl;
    file << m_weather->getWeatherGrade() << " " << (m_weather->getWeatherToday() == RAINY ? "r" : "s") << std::endl;

}

void Game::update( void )
{
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
            window.draw( (*it)->m_state );
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
    if (e.type == sf::Event::KeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			//dilateFluids(m_tilemap);
            for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_GOOD);
                }
            }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			//erodeFluids(m_tilemap);
            for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_NORMAL);
                }
            }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			//dilateNearFluids(m_tilemap);
			for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_TIRED);
                }
            }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			//erodeNearFluids(m_tilemap);
			for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_WEAK);
                }
            }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
			//dilateForests(m_tilemap);
			for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_VERY_WEAK);
                }
            }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
			//erodeForests(m_tilemap);
			for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_TIRED_GOOD);
                }
            }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
			//dilateNearCliffs(m_tilemap);
			for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_TIRED_NORMAL);
                }
            }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
			//erodeNearCliffs(m_tilemap);
			for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_TIRED_WEAK);
                }
            }

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
			//burnRessources(m_tilemap);
			for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it)
            {
                if( !(*it)->isDead() )
                {
                    (*it)->setStateicon(S_TIRED_VERY_WEAK);
                }
            }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
			burnRessources(m_tilemap);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			m_weather->setWeatherToday(SUNNY);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			m_weather->setWeatherToday(RAINY);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			if (m_Ambiancemusic.openFromFile("data/ambiance_civ.ogg")) //musique un peu plus percutante
            {
                m_Ambiancemusic.setLoop(true);
                m_Ambiancemusic.play();
            }
            else{std::cout<<"erreur chargement musique"<<std::endl;}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (m_Ambiancemusic.openFromFile("data/ambiance_magic.ogg")) //musique douce
            {
                m_Ambiancemusic.setLoop(true);
                m_Ambiancemusic.play();
            }
            else{std::cout<<"erreur chargement musique"<<std::endl;}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
			m_Ambiancemusic.stop();
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


void Game::allHome( void )
{
    for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        if( !(*it)->isDead() && (*it)->m_action != MOVE) {
            (*it)->m_action = MOVE_HOME;
        }
    }
}


void Game::clearEntity( void )
{
    m_entityList.clear();
}

void Game::actionElement( int type,sf::Vector2i position )
{
    int cost(this->m_tilemap->getElementCost( type ));
    if (this->m_incidencePoint >= cost)
    {
        this->m_tilemap->addElement( type,position );
        this->m_incidencePoint -= cost;
    }
    else
    {
        /// NOT ENOUGH POINTS
        std::cout << "Not enough points !" << std::endl;
    }
}

void Game::actionGround( int type,sf::Vector2i position )
{
    int cost(this->m_tilemap->getGroundCost( type,position ));
    if (this->m_incidencePoint >= cost)
    {
        this->m_tilemap->userSetGround( type,position );
        this->m_incidencePoint -= cost;
    }
    else
    {
        /// NOT ENOUGH POINTS
        std::cout << "Not enough points !" << std::endl;
    }
}
