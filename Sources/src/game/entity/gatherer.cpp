#include "gatherer.hpp"

const char Gatherer::className[] = "Gatherer";

#define method(class, name) {#name, &class::name}

// On initialise le tableau des m�thodes de la classe.
Lunar<Gatherer>::RegType Gatherer::methods[] = {
    method(Gatherer, action),
    method(Gatherer, getEntities),
    method(Gatherer, getNearestResource),
    method(Gatherer, isNearHome),
    method(Gatherer, isNearResource),
    method(Gatherer, fullBag),
    method(Gatherer, emptyBag),
    method(Gatherer, getAngle),
    method(Gatherer, setAngle),
    method(Gatherer, isAttacked),
    method(Gatherer, getHealth),
    method(Gatherer, setTarget),
    method(Gatherer, isAttackMe),
    method(Gatherer, getDistanceToHome),
    method(Gatherer, getDistance),
    method(Gatherer, getAngleToHome),
    method(Gatherer, getRandom),
    /// @Danger ******* /!\ TO COMPLETE /!\ ******* @Danger
    {0,0}
};


Gatherer::Gatherer( lua_State * L ) : Entity(NULL)
{
    init();
}


Gatherer::Gatherer( EntityType t, Game * game, Entity * e ) : Entity(t, game, 'g')
{
    /// LUA
    // on enregistre la classe aupr�s de lua
    Lunar<Gatherer>::Register(Entity::state);

    // on v�rifie si le script existe bien
    if(luaL_dofile(Entity::state, "lua/gatherer.lua") != 0)
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

Gatherer::~Gatherer( void ) {}

void Gatherer::init( void )
{
    Entity::init();
    initAnimations();
    m_ressource = FOOD;
}

void Gatherer::initAnimations()
{
   // m_animationList[A_STAY]=new Animation("data/ani/gatherer_idle.ani" );
   m_animationList[A_UP]=new Animation("data/ani/gatherer_up.ani" );
   m_animationList[A_DOWN]=new Animation("data/ani/gatherer_down.ani" );
   m_animationList[A_LEFT]=new Animation("data/ani/gatherer_left.ani" );
   m_animationList[A_RIGHT]=new Animation("data/ani/gatherer_right.ani" );
   //m_animationList[A_HIT]=new Animation("data/ani/gatherer_attack.ani" );
   //m_animationList[A_ACTION]=new Animation("data/ani/gatherer_action.ani" );

    m_animation=m_animationList[A_DOWN];
}

void Gatherer::callScript( void )
{
    if(!isDead()) {
        if( m_action == IDLE ) {
            m_way.clear();
            lua_settop(Entity::state, 0);
            Lunar<Gatherer>::push(Entity::state, this);
            if(Lunar<Gatherer>::call(Entity::state, "action", 0, 1) < 0) {
                std::cout << "Erreur : Script LUA - Gatherer" << std::endl;
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





