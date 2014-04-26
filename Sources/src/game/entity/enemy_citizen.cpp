#include "enemy_citizen.hpp"

#include "../../engine/foo.hpp"
#include "entity.hpp"

const char EnemyCitizen::className[] = "EnemyCitizen";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des méthodes de la classe.
Lunar<EnemyCitizen>::RegType EnemyCitizen::methods[] = {
    method(EnemyCitizen, action),
    method(EnemyCitizen, getEntities),
    method(EnemyCitizen, getNearestResource),
    method(EnemyCitizen, isNearHome),
    method(EnemyCitizen, isNearResource),
    method(EnemyCitizen, fullBag),
    method(EnemyCitizen, emptyBag),
    method(EnemyCitizen, getAngle),
    method(EnemyCitizen, setAngle),
    method(EnemyCitizen, getHealth),
    method(EnemyCitizen, isAttacked),
    method(EnemyCitizen, setTarget),
    method(EnemyCitizen, isAttackMe),
    method(EnemyCitizen, getDistanceToHome),
    method(EnemyCitizen, getAngleToHome),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


EnemyCitizen::EnemyCitizen( lua_State * L ) : Entity(NULL)
{
    init();
}


EnemyCitizen::EnemyCitizen( EntityType t, Game * game ) : Entity(t, game)
{
    /// LUA
    // on enregistre la classe auprès de lua
    Lunar<EnemyCitizen>::Register(Entity::state);

    // on vérifie si le script existe bien
    if(luaL_dofile(Entity::state, "lua/enemy_citizen.lua") != 0)
    {
        // il y a eu une erreur dans le script
        fprintf(stderr, "%s\n", lua_tostring(Entity::state, -1));
        exit(0);
    }
    /// ***

    init();
}

EnemyCitizen::~EnemyCitizen( void ) {}

void EnemyCitizen::init( void )
{
    Entity::init();
    initAnimations();
    m_ressource = NOTHING;
}


void EnemyCitizen::initAnimations()
{
   // m_animationList[A_STAY]=new Animation("data/ani/enemy_idle.ani" );
   m_animationList[A_UP]=new Animation("data/ani/enemy_up.ani" );
   m_animationList[A_DOWN]=new Animation("data/ani/enemy_down.ani" );
   m_animationList[A_LEFT]=new Animation("data/ani/enemy_left.ani" );
   m_animationList[A_RIGHT]=new Animation("data/ani/enemy_right.ani" );
   //m_animationList[A_HIT]=new Animation("data/ani/enemy_attack.ani" );
   //m_animationList[A_ACTION]=new Animation("data/ani/enemy_action.ani" );

    m_animation=m_animationList[A_DOWN];
}

void EnemyCitizen::callScript( void )
{
    if(!isDead()) {
        if( m_action == IDLE ) {
            m_way.clear();
            lua_settop(Entity::state, 0);
            Lunar<EnemyCitizen>::push(Entity::state, this);
            if(Lunar<EnemyCitizen>::call(Entity::state, "action", 0, 1) < 0) {
                std::cout << "Erreur : Script LUA - EnemyCitizen" << std::endl;
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
        }
    }
}





