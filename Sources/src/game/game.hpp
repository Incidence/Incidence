#ifndef _GAME_
#define _GAME_

#include <string>
#include <list>
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

    std::list< Entity * > getEntities( void );
    std::list< Entity * > getEntities( sf::Vector2f position, int distancePerception );

    void addEntity( Entity * e );

private :
    Carte * m_carte;
    std::list< Entity * > m_entityList;

    friend class Entity;
};


#endif // _GAME_
