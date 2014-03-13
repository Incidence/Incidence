#ifndef _ENTITY_
#define _ENTITY_

#include "SFML/Graphics.hpp"

#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "../game.hpp"

class Game;

typedef enum {
    ALLY_CITIZEN,
    ENEMY_CITIZEN,
    WILD_ANIMAL,
    PEACEFUL_ANIMAL,
    DEFAULT_ENTITY
} EntityType;

class Entity
{

public :
    typedef enum {
        MOVE,
        MOVE_HOME,
        MOVE_RESOURCE,
        INTERACT_HOME,
        INTERACT_RESOURCE,
        ATTACK,
        IDLE
    } Action;


public :
    Entity( EntityType t, Game * game );
    Entity( lua_State * L );
    virtual ~Entity( void );

    virtual void init( void );

    virtual int action(lua_State * L);

    virtual void callScript( void ) = 0;
    sf::Sprite * draw( void );

    // Use by LUA Script
    int getEntities( lua_State * L ); // : EntitySet
    int getNearestResource( lua_State * L ); // : bool
    int isNearHome( lua_State * L ); // : bool
    int isNearResource( lua_State * L ); // : bool
    int fullBag( lua_State * L ); // : bool
    int emptyBag( lua_State * L ); // : bool
    int getAngle( lua_State * L ); // : float
    int setAngle( lua_State * L ); // : void (L = float(angle))
    int isAttacked( lua_State * L ); // : bool
    // *****

    void goHome( void );
    void goNearestResource( void );
    void move( void );
    void takeResource( void );
    void giveResource( void );
    void attack( void );

    // Getters :

    sf::Vector2f getPosition( void ) const;

    void setPosition( sf::Vector2f p );

protected :
    Game * m_game;

    Animation m_animation;
    int m_perception;
    RessourceType m_ressource;

    std::list< sf::Vector2f > m_way;
    sf::Vector2f m_position;
    float m_angle;
    float m_speed;

    EntityType m_type;
    int m_bag;

    Action m_action;

public :
    /// Lua
    static void luaInit( void );
    static bool bLuaInit;
    static lua_State * state;
};

#endif // _ENTITY_
