#ifndef _GAME_
#define _GAME_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "level.hpp"
#include "entity/entity.hpp"
#include "incidences.hpp"
#include "building/building.hpp"
#include "weather.hpp"

#define TIME_TO_CIRCLE 60.0f

class Entity;

class Game
{

public :
    Game( unsigned int w = 150, unsigned int h = 150 );
    ~Game( void );

    void newGame( unsigned int w, unsigned int h );
    void loadGame( std::string path );
    void saveGame( std::string path );

    void update( void );
    void draw( sf::RenderTarget & window );
    void drawMap( sf::RenderTarget & window );
    void handleEvent( sf::Event & e );

    Entity * getEntity( int id );
    std::vector< Entity * > getEntities( void );
    TileMap * getTilemap( void );
    Weather * getWeather();
    void addEntity( Entity * e );
    void clearEntity( void );

    void setPI(int n);
    int getPI();

    int getQtyWood();
    int getQtyFood();
    int getQtyStone();

    void addRessource(RessourceType t, int qty);
    
    unsigned int getDaysCount();

    void incrementDaysCount();

    void spawnEntity( Entity & e );
    void allHome( void );

    void actionElement( int type,sf::Vector2i position );
    void actionGround( int type,sf::Vector2i position );

private :
    TileMap * m_tilemap;
    std::vector< Building > m_buildings;
    Building m_home;
    std::vector< Entity * > m_entityList;
    Weather * m_weather;
    int m_incidencePoint;

    int qtyWood;
    int qtyFood;
    int qtyStone;
    
    unsigned int m_daysCount;

    sf::Music m_Ambiancemusic;

    friend class Entity;
    friend class NightState;
    friend class TestState;
};


#endif // _GAME_
