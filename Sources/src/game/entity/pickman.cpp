#include "pickman.hpp"

const char Pickman::className[] = "Pickman";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des méthodes de la classe.
Lunar<Pickman>::RegType Pickman::methods[] = {
    method(Pickman, action),
    method(Pickman, getEntities),
    method(Pickman, getNearestResource),
    method(Pickman, isNearHome),
    method(Pickman, isNearResource),
    method(Pickman, fullBag),
    method(Pickman, emptyBag),
    method(Pickman, getAngle),
    method(Pickman, setAngle),
    method(Pickman, isAttacked),
    method(Pickman, getHealth),
    method(Pickman, setTarget),
    method(Pickman, isAttackMe),
    method(Pickman, getDistanceToHome),
    method(Pickman, getAngleToHome),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


Pickman::Pickman( lua_State * L ) : Entity(NULL)
{
    init();
}


Pickman::Pickman( EntityType t, Game * game ) : Entity(t, game)
{
    /// LUA
    // on enregistre la classe auprès de lua
    Lunar<Pickman>::Register(Entity::state);

    // on vérifie si le script existe bien
    if(luaL_dofile(Entity::state, "lua/pickman.lua") != 0)
    {
        // il y a eu une erreur dans le script
        fprintf(stderr, "%s\n", lua_tostring(Entity::state, -1));
        exit(0);
    }
    /// ***

    init();
}

Pickman::~Pickman( void ) {}

void Pickman::init( void )
{
    Entity::init();
    initAnimations();
    m_ressource = STONE;
}

void Pickman::initAnimations()
{
   // m_animationList[A_STAY]=new Animation("data/ani/pickman_idle.ani" );
   m_animationList[A_UP]=new Animation("data/ani/pickman_up.ani" );
   m_animationList[A_DOWN]=new Animation("data/ani/pickman_down.ani" );
   m_animationList[A_LEFT]=new Animation("data/ani/pickman_left.ani" );
   m_animationList[A_RIGHT]=new Animation("data/ani/pickman_right.ani" );
   //m_animationList[A_HIT]=new Animation("data/ani/pickman_attack.ani" );
   //m_animationList[A_ACTION]=new Animation("data/ani/pickman_action.ani" );

    m_animation=m_animationList[A_DOWN];
}

void Pickman::callScript( void )
{
    if(!isDead()) {
        if( m_action == IDLE ) {
            m_way.clear();
            lua_settop(Entity::state, 0);
            Lunar<Pickman>::push(Entity::state, this);
            if(Lunar<Pickman>::call(Entity::state, "action", 0, 1) < 0) {
                std::cout << "Erreur : Script LUA - Pickman" << std::endl;
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





