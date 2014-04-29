#include "hunter.hpp"

const char Hunter::className[] = "Hunter";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des méthodes de la classe.
Lunar<Hunter>::RegType Hunter::methods[] = {
    method(Hunter, action),
    method(Hunter, getEntities),
    method(Hunter, getNearestResource),
    method(Hunter, isNearHome),
    method(Hunter, isNearResource),
    method(Hunter, fullBag),
    method(Hunter, emptyBag),
    method(Hunter, getAngle),
    method(Hunter, setAngle),
    method(Hunter, isAttacked),
    method(Hunter, getHealth),
    method(Hunter, setTarget),
    method(Hunter, isAttackMe),
    method(Hunter, getDistanceToHome),
    method(Hunter, getAngleToHome),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


Hunter::Hunter( lua_State * L ) : Entity(NULL)
{
    init();
}


Hunter::Hunter( EntityType t, Game * game ) : Entity(t, game, 'h')
{
    /// LUA
    // on enregistre la classe auprès de lua
    Lunar<Hunter>::Register(Entity::state);

    // on vérifie si le script existe bien
    if(luaL_dofile(Entity::state, "lua/hunter.lua") != 0)
    {
        // il y a eu une erreur dans le script
        fprintf(stderr, "%s\n", lua_tostring(Entity::state, -1));
        exit(0);
    }
    /// ***

    init();
}

Hunter::~Hunter( void ) {}

void Hunter::init( void )
{
    Entity::init();
    initAnimations();
    m_ressource = WOOD;
    m_speed = 80;
}

void Hunter::initAnimations()
{
   // m_animationList[A_STAY]=new Animation("data/ani/hunter_idle.ani" );
   m_animationList[A_UP]=new Animation("data/ani/hunter_up.ani" );
   m_animationList[A_DOWN]=new Animation("data/ani/hunter_down.ani" );
   m_animationList[A_LEFT]=new Animation("data/ani/hunter_left.ani" );
   m_animationList[A_RIGHT]=new Animation("data/ani/hunter_right.ani" );
   //m_animationList[A_HIT]=new Animation("data/ani/hunter_attack.ani" );
   //m_animationList[A_ACTION]=new Animation("data/ani/hunter_action.ani" );

    m_animation=m_animationList[A_DOWN];
}

void Hunter::callScript( void )
{
    if(!isDead()) {
        if( m_action == IDLE ) {
            m_way.clear();
            lua_settop(Entity::state, 0);
            Lunar<Hunter>::push(Entity::state, this);
            if(Lunar<Hunter>::call(Entity::state, "action", 0, 1) < 0) {
                std::cout << "Erreur : Script LUA - Hunter" << std::endl;
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





