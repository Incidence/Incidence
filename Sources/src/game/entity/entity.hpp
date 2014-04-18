#ifndef _ENTITY_
#define _ENTITY_

#include "SFML/Graphics.hpp"

#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "../game.hpp"
#include "entity_set.hpp"
#include "entity_type.hpp"

class EntitySet;
class Game;

class Entity
{

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
    int setTarget( lua_State * L ); // : void (int (id_target))
    int isAttackMe( lua_State * L ); // : bool (int (id_target))
    int getHealth( lua_State * L ); // : Health
    int getDistanceToHome( lua_State * L ); // int
    int getAngleToHome( lua_State * L ); // : float
    // *****

    void goHome( void );
    void goNearestResource( void );
    void move( void );
    void takeResource( void );
    void giveResource( void );
    void attack( void );

    bool nearEntity( const Entity * e );
    bool isDead() const;
    void isAttackedBy( Entity * e );

    void recolting( void );

    // Getters :

    sf::Vector2f getPosition( void ) const;

    void setPosition( sf::Vector2f p );

protected :
    Game * m_game;

    Animation m_animation;
    int m_perception;
    RessourceType m_ressource;
    sf::Vector2i m_recolt;

    std::list< sf::Vector2f > m_way;
    sf::Vector2f m_position;
    float m_angle;
    float m_speed;

    EntityType m_type;
    int m_bag;

    Health m_health;

    Entity * m_target;

    Action m_action;

    float m_waitTime;

public :
    /// Lua
    static void luaInit( void );
    static bool bLuaInit;
    static lua_State * state;

    friend class Game;
};

#endif // _ENTITY_
