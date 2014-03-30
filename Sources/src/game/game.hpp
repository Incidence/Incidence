#ifndef _GAME_
#define _GAME_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "entity/entity.hpp"

class Entity;

class Game
{

public :
    Game( void );
    ~Game( void );

    void newGame( void );
    void loadGame( std::string path );
    void saveGame( std::string path );

    void update( void );
    void draw( sf::RenderTarget & window );
    void handleEvent( sf::Event & e );

    Entity * getEntity( int id );
    std::vector< Entity * > getEntities( void );

    void addEntity( Entity * e );

private :
    TileMap * m_tilemap;
    std::vector< Entity * > m_entityList;

    friend class Entity;
};


#endif // _GAME_
