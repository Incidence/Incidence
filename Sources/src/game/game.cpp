#include "game.hpp"

#include <list>

#include "level/TileSet.hpp"
#include "../engine/foo.hpp"

/// TODO
Game::Game( void ) : m_carte(NULL)
{
    newGame();
}

Game::~Game( void )
{
    if(m_carte) {
        delete m_carte;
    }

    for(std::list< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        delete *it;
    }
}

void Game::newGame( void )
{
    if(m_carte) {
        delete m_carte;
    }

	m_carte = new Carte(TileSet("Ressources/tileset.png"), sf::Vector2u(29,32));
	m_carte->generate();
}

void Game::loadGame( std::string path ) {}
void Game::saveGame( std::string path ) {}

void Game::update( void )
{
    for(std::list< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        (*it)->callScript();
    }
}

void Game::draw( sf::RenderTarget & window )
{
    m_carte->drawSols( window );
    m_carte->drawElementsBas( window );

    for(std::list< Entity * >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
        window.draw( * (*it)->draw() );
    }

    m_carte->drawElementsHaut( window );
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

