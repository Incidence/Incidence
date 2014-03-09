#include "Lumberjack.hpp"

const char Lumberjack::className[] = "Lumberjack";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des méthodes de la classe.
Lunar<Lumberjack>::RegType Lumberjack::methods[] = {
    method(Lumberjack, action),
    method(Lumberjack, getEntities),
    method(Lumberjack, getNearestResource),
    method(Lumberjack, isNearHome),
    method(Lumberjack, isNearResource),
    method(Lumberjack, fullBag),
    method(Lumberjack, emptyBag),
    method(Lumberjack, setAngle),
    method(Lumberjack, isAttacked),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


Lumberjack::Lumberjack( lua_State * L ) : Entity(NULL)
{
    init();
}


Lumberjack::Lumberjack( EntityType t, Game * game ) : Entity(t, game)
{
    /// LUA
    // on enregistre la classe auprès de lua
    Lunar<Lumberjack>::Register(Entity::state);

    // on vérifie si le script existe bien
    if(luaL_dofile(Entity::state, "lua/lumberjack.lua") != 0)
    {
        // il y a eu une erreur dans le script
        fprintf(stderr, "%s\n", lua_tostring(Entity::state, -1));
        exit(0);
    }
    /// ***

    init();
}

Lumberjack::~Lumberjack( void ) {}

void Lumberjack::init( void )
{
    Entity::init();

    m_ressource = BOIS;
}

void Lumberjack::callScript( void )
{
    if( m_action == IDLE ) {
        lua_settop(Entity::state, 0);
        Lunar<Lumberjack>::push(Entity::state, this);
        Lunar<Lumberjack>::call(Entity::state, "action", 0, 0);

        // TODO : Recuperer le string retourne pour effectuer l'action demande
        float argc = lua_gettop(Entity::state);
        if( argc > 0 && lua_isstring(Entity::state, 1)) {
            std::string action = lua_tostring(Entity::state, 1);

            // ***
            if(action == "move") { m_action = MOVE; }
            /// TO COMPLETE ....
            // ***
        }
    } else if ( m_action == MOVE ) {
        move();
    } else if ( m_action == MOVE_HOME ) {
        goHome();
    } else if ( m_action == MOVE_RESOURCE ) {
        goNearestResource();
    } else if ( m_action == INTERACT_HOME ) {
        giveResource();
    } else if ( m_action == INTERACT_RESOURCE ) {
        takeResource();
    } else if ( m_action == ATTACK ) {
        attack();
    }
}





