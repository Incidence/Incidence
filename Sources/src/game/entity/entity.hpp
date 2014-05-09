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
    Entity( EntityType t, Game * game, char j );
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
    bool isNearHome( void );
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

    EntityType getType();
	Health getHealth();
	void setHealth(Health h);

    float getGiveTime();
    void updateGiveTime(float t);
    int getGiveQuantity();
    void updateGiveQuantity();

    bool isTired();
    bool isSick();
    void setisTired(bool t);
    void setisSick(bool s);
    float weaknessCoeff(Health h);//mise ici car erreur avec multiple definition si mise dans entity_type.hpp
    void initStateiconList();
    void setStateicon(StateType s);

    const char m_job;

protected :
    Game * m_game;

    Animation* m_animation;
    std::map<AnimationType,Animation*> m_animationList;
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

    float m_giveTime;
    int m_giveQuantity;

    bool m_isAttacked;
    bool m_isSick;
    bool m_isTired;

    sf::Sprite m_etat;
    std::map<StateType,sf::Texture> m_stateiconList;

public :

    /// Lua
    static void luaInit( void );
    static bool bLuaInit;
    static lua_State * state;

    friend class Game;
};

#endif // _ENTITY_
