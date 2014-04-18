#include "peaceful_animal.hpp"

const char PeacefulAnimal::className[] = "PeacefulAnimal";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des méthodes de la classe.
Lunar<PeacefulAnimal>::RegType PeacefulAnimal::methods[] = {
    method(PeacefulAnimal, action),
    method(PeacefulAnimal, getEntities),
    method(PeacefulAnimal, getNearestResource),
    method(PeacefulAnimal, isNearHome),
    method(PeacefulAnimal, isNearResource),
    method(PeacefulAnimal, fullBag),
    method(PeacefulAnimal, emptyBag),
    method(PeacefulAnimal, getAngle),
    method(PeacefulAnimal, setAngle),
    method(PeacefulAnimal, isAttacked),
    method(PeacefulAnimal, getHealth),
    method(PeacefulAnimal, setTarget),
    method(PeacefulAnimal, isAttackMe),
    method(PeacefulAnimal, getDistanceToHome),
    method(PeacefulAnimal, getAngleToHome),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


PeacefulAnimal::PeacefulAnimal( lua_State * L ) : Entity(NULL)
{
    init();
}


PeacefulAnimal::PeacefulAnimal( EntityType t, Game * game ) : Entity(t, game)
{
    /// LUA
    // on enregistre la classe auprès de lua
    Lunar<PeacefulAnimal>::Register(Entity::state);

    // on vérifie si le script existe bien
    if(luaL_dofile(Entity::state, "lua/peaceful_animal.lua") != 0)
    {
        // il y a eu une erreur dans le script
        fprintf(stderr, "%s\n", lua_tostring(Entity::state, -1));
        exit(0);
    }
    /// ***

    init();
}

PeacefulAnimal::~PeacefulAnimal( void ) {}

void PeacefulAnimal::init( void )
{
    Entity::init();
    m_animation.load( "data/perso_pe.ani" );

    m_ressource = WOOD;
}

void PeacefulAnimal::callScript( void )
{
    if(!isDead()) {
        if( m_action == IDLE ) {
            m_way.clear();
            lua_settop(Entity::state, 0);
            Lunar<PeacefulAnimal>::push(Entity::state, this);
            if(Lunar<PeacefulAnimal>::call(Entity::state, "action", 0, 1) < 0) {
                std::cout << "Erreur : Script LUA - PeacefulAnimal" << std::endl;
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





