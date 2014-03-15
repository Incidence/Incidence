#include "game.hpp"

#include <list>

#include "level/tileset.hpp"
#include "../engine/foo.hpp"
#include "../engine/time.hpp"

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

    for(std::list< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        delete *it;
    }
}

void Game::newGame( void )
{
    if(m_tilemap) {
        delete m_tilemap;
    }

	m_tilemap = new TileMap(TileSet("data/tileset.png"), sf::Vector2u(150,150));
	m_tilemap->generate();
}

void Game::loadGame( std::string path ) {}
void Game::saveGame( std::string path ) {}

void Game::update( void )
{
    int c = 0;
    for(std::list< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        (*it)->callScript();
        c++;
    }
}

void Game::draw( sf::RenderTarget & window )
{
    m_tilemap->drawGrounds( window );
    m_tilemap->drawElementsDown( window );

    for(std::list< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        window.draw( * (*it)->draw() );
    }

    m_tilemap->drawElementsUp( window );
}

void Game::handleEvent( sf::Event & e )
{
    if (e.type == sf::Event::MouseButtonPressed) {
        for(std::list< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
            (*it)->setPosition(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
        }
    }
}


std::list< Entity * > Game::getEntities( void )
{
    return m_entityList;
}

std::list< Entity * > Game::getEntities( sf::Vector2f position, int distancePerception )
{
    std::list< Entity * > res;

    for(std::list< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        if( distance(position, (*it)->getPosition()) < distancePerception ) {
            res.push_back(*it);
        }
    }

    return res;
}

void Game::addEntity( Entity * e )
{
    m_entityList.push_back(e);
}

