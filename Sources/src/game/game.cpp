#include "game.hpp"

#include <list>

#include "level/tileset.hpp"
#include "../engine/foo.hpp"
#include "../engine/time.hpp"
#include "incidences.hpp"

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

    for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        delete *it;
    }
}

void Game::newGame( void )
{
    if(m_tilemap) {
        delete m_tilemap;
    }

	m_tilemap = new TileMap(TileSet("data/tileset.png"), sf::Vector2u(150, 150));
	m_tilemap->generate();
}

void Game::loadGame( std::string path ) {}
void Game::saveGame( std::string path ) {}

void Game::update( void )
{
    for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        if( !(*it)->isDead() ) {
            (*it)->callScript();
        }
    }
}

void Game::draw( sf::RenderTarget & window )
{
    m_tilemap->drawGrounds( window );
    m_tilemap->drawElementsDown( window );

    for(std::vector< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        if( !(*it)->isDead() ) {
            window.draw( * (*it)->draw() );
        }
    }

    m_tilemap->drawElementsUp( window );
}

void Game::handleEvent( sf::Event & e )
{
    if (e.type == sf::Event::MouseButtonPressed) {
        if( m_entityList.size() > 0 ) {
            m_entityList[0]->setPosition(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
        }
    }
												if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
													erodeFluids(m_tilemap);
												}
												if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
													dilateFluids(m_tilemap);
												}
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

void Game::addEntity( Entity * e )
{
    m_entityList.push_back(e);
}

















