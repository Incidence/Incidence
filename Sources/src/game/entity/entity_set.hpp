#ifndef _ENTITY_SET_
#define _ENTITY_SET_

#include "entity.hpp"
#include "entity_type.hpp"

class Entity;

typedef struct {
    EntityType s_type;
    float s_distance;
    float s_angle;
    Health s_health;
    unsigned int s_id;
} EntityStruct;


class EntitySet
{

public :
    EntitySet( void );
    EntitySet( lua_State * L );
    ~EntitySet( void );

    int getSize( void );
    int getSize( lua_State * L ); // : int
    int getDistance( lua_State * L ); // : float (int (id_entity))
    int getAngle( lua_State * L ); // : float (int (id_entity))
    int getType( lua_State * L ); // : EntityType (int (id_entity))
    int getHealth( lua_State * L ); // : Health (int (id_entity))
    int getID( lua_State * L );

    void clear( void );

    void add( EntityStruct * e );

private :
    /// Lua
    friend class Lunar<EntitySet>;
	static const char className[];
	static Lunar<EntitySet>::RegType methods[];

    std::vector< EntityStruct * > m_entitySet;

};

#endif // _ENTITY_SET_
