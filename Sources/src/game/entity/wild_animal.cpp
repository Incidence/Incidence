#include "wild_animal.hpp"

const char WildAnimal::className[] = "WildAnimal";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des méthodes de la classe.
Lunar<WildAnimal>::RegType WildAnimal::methods[] = {
    method(WildAnimal, action),
    method(WildAnimal, getEntities),
    method(WildAnimal, getNearestResource),
    method(WildAnimal, isNearHome),
    method(WildAnimal, isNearResource),
    method(WildAnimal, fullBag),
    method(WildAnimal, emptyBag),
    method(WildAnimal, getAngle),
    method(WildAnimal, setAngle),
    method(WildAnimal, isAttacked),
    method(WildAnimal, getHealth),
    method(WildAnimal, setTarget),
    method(WildAnimal, isAttackMe),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


WildAnimal::WildAnimal( lua_State * L ) : Entity(NULL)
{
    init();
}


WildAnimal::WildAnimal( EntityType t, Game * game ) : Entity(t, game)
{
    /// LUA
    // on enregistre la classe auprès de lua
    Lunar<WildAnimal>::Register(Entity::state);

    // on vérifie si le script existe bien
    if(luaL_dofile(Entity::state, "lua/wild_animal.lua") != 0)
    {
        // il y a eu une erreur dans le script
        fprintf(stderr, "%s\n", lua_tostring(Entity::state, -1));
        exit(0);
    }
    /// ***

    init();
}

WildAnimal::~WildAnimal( void ) {}

void WildAnimal::init( void )
{
    Entity::init();

    m_ressource = WOOD;
}

void WildAnimal::callScript( void )
{
    if(!isDead()) {
        if( m_action == IDLE ) {
            m_way.clear();
            lua_settop(Entity::state, 0);
            Lunar<WildAnimal>::push(Entity::state, this);
            if(Lunar<WildAnimal>::call(Entity::state, "action", 0, 1) < 0) {
                std::cout << "Erreur : Script LUA - WildAnimal" << std::endl;
                return;
            }

            // TODO : Recuperer le string retourne pour effectuer l'action demande
            float argc = lua_gettop(Entity::state);
            if( argc > 0 && lua_isstring(Entity::state, 1)) {
                std::string action = lua_tostring(Entity::state, 1);

                // ***
                if(action == "move") { m_action = MOVE; }
                if(action == "give") { m_action = INTERACT_HOME; }
                if(action == "gohome") { m_action = MOVE_HOME; }
                if(action == "attack") { m_action = ATTACK; }
                if(action == "take") { m_action = INTERACT_RESOURCE; }
                if(action == "gonearest") { m_action = MOVE_RESOURCE; }
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
        } else if ( m_action == RECOLT ) {
            recolting();
        }
    }
}





