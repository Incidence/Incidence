#include "entity_set.hpp"


const char EntitySet::className[] = "EntitySet";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des méthodes de la classe.
Lunar<EntitySet>::RegType EntitySet::methods[] = {
    method(EntitySet, getSize),
    method(EntitySet, getDistance),
    method(EntitySet, getAngle),
    method(EntitySet, getType),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


EntitySet::EntitySet( void ) {}
EntitySet::EntitySet( lua_State * L ) {}
EntitySet::~EntitySet( void ) {}

int EntitySet::getSize( lua_State * L )
{
    lua_pushnumber(L, m_entityList.size());
    return 1;
}

int EntitySet::getDistance( lua_State * L )
{
    float argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(id == -1 && id >= (int)m_entityList.size()) {
        return 0;
    }

    lua_pushnumber(L, m_entityList[id].s_distance);
    return 1;
}

int EntitySet::getAngle( lua_State * L )
{
    float argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(id == -1 && id >= (int)m_entityList.size()) {
        return 0;
    }

    lua_pushnumber(L, m_entityList[id].s_angle);
    return 1;
}

int EntitySet::getType( lua_State * L )
{
    float argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(id == -1 && id >= (int)m_entityList.size()) {
        return 0;
    }

    lua_pushnumber(L, m_entityList[id].s_type);
    return 1;
}

void EntitySet::add( EntityStruct e )
{
    m_entityList.push_back(e);
}


