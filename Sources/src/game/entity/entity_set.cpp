#include "entity_set.hpp"


const char EntitySet::className[] = "EntitySet";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des méthodes de la classe.
Lunar<EntitySet>::RegType EntitySet::methods[] = {
    method(EntitySet, getSize),
    method(EntitySet, getDistance),
    method(EntitySet, getAngle),
    method(EntitySet, getType),
    method(EntitySet, getHealth),
    method(EntitySet, getID),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


EntitySet::EntitySet( void ) {
    // on enregistre la classe auprès de lua
    Lunar<EntitySet>::Register(Entity::state);
}
EntitySet::EntitySet( lua_State * L ) {}
EntitySet::~EntitySet( void ) {}

int EntitySet::getSize( void )
{
    return m_entitySet.size();
}

int EntitySet::getSize( lua_State * L )
{
    lua_pushnumber(L, m_entitySet.size());
    return 1;
}

int EntitySet::getDistance( lua_State * L )
{
    int argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(id == -1 && id >= (int)m_entitySet.size()) {
        return 0;
    }

    lua_pushnumber(L, m_entitySet[id]->s_distance);
    return 1;
}

int EntitySet::getAngle( lua_State * L )
{
    int argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(id == -1 && id >= (int)m_entitySet.size()) {
        return 0;
    }

    lua_pushnumber(L, m_entitySet[id]->s_angle);
    return 1;
}

int EntitySet::getType( lua_State * L )
{
    int argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(id == -1 && id >= (int)m_entitySet.size()) {
        return 0;
    }

    lua_pushnumber(L, m_entitySet[id]->s_type);
    return 1;
}

int EntitySet::getHealth( lua_State * L )
{
    int argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(id == -1 && id >= (int)m_entitySet.size()) {
        return 0;
    }

    lua_pushnumber(L, m_entitySet[id]->s_health);
    return 1;
}

int EntitySet::getID( lua_State * L )
{
    int argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(id == -1 && id >= (int)m_entitySet.size()) {
        return 0;
    }

    lua_pushnumber(L, m_entitySet[id]->s_id);
    return 1;
}


void EntitySet::clear( void )
{
    for(unsigned int i = 0; i < m_entitySet.size(); ++i) {
        if(m_entitySet[i]) { delete m_entitySet[i]; }
        m_entitySet[i] = NULL;
    }
    m_entitySet.clear();
}

void EntitySet::add( EntityStruct * e )
{
    m_entitySet.push_back(e);
}


