#include "lumberjack.hpp"

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
    method(Lumberjack, getAngle),
    method(Lumberjack, setAngle),
    method(Lumberjack, isAttacked),
    method(Lumberjack, getHealth),
    method(Lumberjack, setTarget),
    method(Lumberjack, isAttackMe),
    method(Lumberjack, getDistanceToHome),
    method(Lumberjack, getAngleToHome),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


Lumberjack::Lumberjack( lua_State * L ) : Entity(NULL)
{
    init();
}


Lumberjack::Lumberjack( EntityType t, Game * game, Entity * e ) : Entity(t, game, 'l')
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
    if(e) {
        m_health = e->getHealth();
        m_isSick = e->isSick();
    }
}

Lumberjack::~Lumberjack( void ) {}

void Lumberjack::init( void )
{
    Entity::init();
   initAnimations();
    m_ressource = WOOD;
}

void Lumberjack::initAnimations()
{
   // m_animationList[STAY]=new Animation("data/ani/lumberjack_idle.ani" );
   m_animationList[A_UP]=new Animation("data/ani/lumberjack_up.ani" );
   m_animationList[A_DOWN]=new Animation("data/ani/lumberjack_down.ani" );
   m_animationList[A_LEFT]=new Animation("data/ani/lumberjack_left.ani" );
   m_animationList[A_RIGHT]=new Animation("data/ani/lumberjack_right.ani" );
   //m_animationList[A_HIT]=new Animation("data/ani/lumberjack_attack.ani" );
   //m_animationList[A_ACTION]=new Animation("data/ani/lumberjack_action.ani" );

    m_animation=m_animationList[A_DOWN];
}

void Lumberjack::callScript( void )
{
    if(!isDead()) {
        if( m_action == IDLE ) {
            m_way.clear();
            lua_settop(Entity::state, 0);
            Lunar<Lumberjack>::push(Entity::state, this);
            if(Lunar<Lumberjack>::call(Entity::state, "action", 0, 1) < 0) {
                std::cout << "Erreur : Script LUA - Lumberjack" << std::endl;
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





