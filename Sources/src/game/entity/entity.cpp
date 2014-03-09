#include "entity.hpp"

#include <cmath>

#include "../../engine/time.hpp"
#include "../../engine/foo.hpp"
#include "entity_set.hpp"

bool Entity::bLuaInit = false;

Entity::Entity(lua_State * L)
{
    Entity::luaInit();
    init();
}

Entity::Entity( EntityType t, Game * game ) : m_game(game), m_type(t)
{
    Entity::luaInit();
    init();
}

Entity::~Entity( void ) {}

void Entity::init( void )
{
    /// TODO : Animation default

    m_perception = 5;
    m_position = sf::Vector2f(0, 0);
    m_angle = 0;
    m_bag = 0;
    m_action = IDLE;
    m_ressource = AUCUNE;

    m_animation.load( "data/goku_stay.ani" );

    /// TO COMPLETE
}


int Entity::action(lua_State * L)
{
    // Redefini dans un script lua
    std::cerr << "Attention : Script non existant pour cette entite." << std::endl;
    return 0;
}

sf::Sprite * Entity::draw( void )
{
    sf::Sprite * s = m_animation.update();
    s->setPosition(m_position);
    return s;
}

// *********

int Entity::getEntities( lua_State * L )
{
    EntitySet * eSet = NULL; // Liste des entités aux alentours

    if(m_game) {
        /// TODO : Completer la liste
        std::list< Entity * > listEntities = m_game->getEntities(m_position, m_perception);

        for(std::list< Entity * >::iterator it = listEntities.begin(); it != listEntities.end(); ++it) {
            EntityStruct eStruct;
            eStruct.s_distance = distance(m_position, (*it)->m_position);
            eStruct.s_angle = 0; /// FIXME : Because je suis pas fort en trigo
            eStruct.s_type = (*it)->m_type;

            eSet->add(eStruct);
        }
    }

    Lunar<EntitySet>::push(L, eSet, true);
    return 1;
}

int Entity::isNearHome( lua_State * L )
{
    bool bNearHome = false; // vrai = proche home

    /// RECODE : Verifier la presence de la base

    lua_pushboolean(L, bNearHome);
    return 1;
}

int Entity::fullBag( lua_State * L )
{
    lua_pushboolean(L, m_bag > 0);
    return 1;
}

int Entity::emptyBag( lua_State * L )
{
    lua_pushboolean(L, m_bag == 0);
    return 1;
}

int Entity::setAngle( lua_State * L )
{
    float argc = lua_gettop(L);
    if( argc > 0 && lua_isnumber(L, 1)) {
        m_angle = lua_tonumber(L, 1);
    }
    return 0;
}

int Entity::isAttacked( lua_State * L )
{
    bool attacked = false;

    /// RECODE : Comment voir si on est attaque ?

    lua_pushboolean(L, attacked);
    return 1;
}

int Entity::getNearestResource( lua_State * L )
{
    // True s'i y a une ressource dans le champs de perception
    bool bNearest = false;

    if(m_game && m_game->m_carte) {
        sf::Vector2i posMap = (m_game->m_carte)->getXY(m_position);

        for(int x = posMap.x - m_perception; x < posMap.x + m_perception; ++x) {
            for(int y = posMap.y - m_perception; y < posMap.y + m_perception; ++y) {
                Element * pElement = m_game->m_carte->getElement( sf::Vector2i(x, y) );
                if( pElement && distance(posMap, sf::Vector2i(x, y)) < m_perception && pElement->containResource(m_ressource) ) {
                    bNearest = true;
                    /// @Attention
                    /// RECODE : La case doit etre accessible !
                    /// @Attention

                }
            }
        }
    }

    lua_pushboolean(L, bNearest);
    return 1;
}

int Entity::isNearResource( lua_State * L )
{
    bool bNear = false;

    if(m_game && m_game->m_carte) {
        // Vrai si ELEMENT avec M_RESSOURCE à portee de recolte (case adjacente)
        sf::Vector2i posMap = (m_game->m_carte)->getXY(m_position);
        Element * pElementRight = m_game->m_carte->getElement( sf::Vector2i(posMap.x + 1, posMap.y) );
        Element * pElementLeft = m_game->m_carte->getElement( sf::Vector2i(posMap.x - 1, posMap.y) );
        Element * pElementUp = m_game->m_carte->getElement( sf::Vector2i(posMap.x, posMap.y + 1) );
        Element * pElementDown = m_game->m_carte->getElement( sf::Vector2i(posMap.x, posMap.y - 1) );

        if(pElementDown && pElementLeft && pElementRight && pElementUp) {
            bNear = (   pElementDown->containResource(m_ressource) ||
                        pElementLeft->containResource(m_ressource) ||
                        pElementRight->containResource(m_ressource) ||
                        pElementUp->containResource(m_ressource) );
        }
    }

    lua_pushboolean(L, bNear);
    return 1;
}


// **********

void Entity::goHome( void )
{
    /// TODO
}

void Entity::move( void )
{
    /// RECODE : Use PathFinding

    // Deplacement basique sans collision
    sf::Vector2f vDirect;
    vDirect.x = cos(m_angle) * m_speed * Time::get()->deltaTime();
    vDirect.y = sin(m_angle) * m_speed * Time::get()->deltaTime();

    m_position.x += vDirect.x;
    m_position.y += vDirect.y;
}

void Entity::attack( void )
{
    /// TODO
}


void Entity::goNearestResource( void )
{
    /// TODO
    /*
        Cherche l'ELEMENT avec M_RESSOURCE le plus proche
            pathfinding vers ELEMENT
            action = MOVE
        Sinon RIEN
    */

    if(m_game && m_game->m_carte) {
        sf::Vector2i posMap = (m_game->m_carte)->getXY(m_position);
        sf::Vector2i posNearest( sf::Vector2i(posMap.x + 10000, posMap.y + 10000) ); // To infinte !

        for(int x = posMap.x - m_perception; x < posMap.x + m_perception; ++x) {
            for(int y = posMap.y - m_perception; y < posMap.y + m_perception; ++y) {
                Element * pElement = m_game->m_carte->getElement( sf::Vector2i(x, y) );
                if(pElement && distance(posMap, sf::Vector2i(x, y)) < m_perception && pElement->containResource(m_ressource) ) {
                    if(distance(posMap, sf::Vector2i(x, y)) < distance(posMap, posNearest)) {
                        posNearest = sf::Vector2i(x, y);
                    }
                }
            }
        }

        if(distance(posMap, posNearest) < m_perception) {
            /// TODO : Aller la bas
        }
    }
}

void Entity::takeResource( void )
{
    /// TODO
    /*
        ELEMENT avec du M_RESSOURCE proche ?
            prendre ressource
        Sinon RIEN
    */

    if(m_game && m_game->m_carte) {
        sf::Vector2i mapPos = m_game->m_carte->getXY(m_position);
        int iElementNeighbor = 0;
        Element * pElement = NULL;
        mapPos.x += 1; // RIGHT
        pElement = m_game->m_carte->getElement(mapPos);
        iElementNeighbor = pElement && pElement->containResource(m_ressource) ? 1 : iElementNeighbor;
        mapPos.x -= 2; // LEFT
        pElement = m_game->m_carte->getElement(mapPos);
        iElementNeighbor = pElement && pElement->containResource(m_ressource) ? 2 : iElementNeighbor;
        mapPos.x += 1;
        mapPos.y += 1; //UP
        pElement = m_game->m_carte->getElement(mapPos);
        iElementNeighbor = pElement && pElement->containResource(m_ressource) ? 3 : iElementNeighbor;
        mapPos.y -= 2; // DOWN
        iElementNeighbor = pElement && pElement->containResource(m_ressource) ? 4 : iElementNeighbor;

        mapPos = m_game->m_carte->getXY(m_position);
        switch(iElementNeighbor) {
            case 1 :
                mapPos.x += 1;
                break;

            case 2 :
                mapPos.x -= 1;
                break;

            case 3 :
                mapPos.y += 1;
                break;

            case 4 :
                mapPos.y -= 1;
                break;

            default :
                return;
                break;
        }

        pElement = m_game->m_carte->getElement(mapPos);
        if(pElement) {
            m_bag = pElement->getQuantityOf(m_ressource);
            m_game->m_carte->supprimerElement(mapPos);
        }
    }
}

void Entity::giveResource( void )
{
    /// TODO

    /*
        Home proche ?
            donner ressource
        Sinon RIEN
    */
}

// Initialisation de LUA (fait qu'une fois)

lua_State * Entity::state = NULL;

void Entity::luaInit( void )
{
     if(!Entity::bLuaInit) {
        /// Init lua_State
        // on créer un contexte d'exécution de Lua
        Entity::state = lua_open();
        // on charge les bibliothèques standards de Lua
        luaL_openlibs(Entity::state);
        /// ***

        // Init Variable global pour LUA
        lua_pushnumber(Entity::state, ALLY_CITIZEN);
        lua_setglobal(Entity::state, "ALLY_CITIZEN");
        lua_pushnumber(Entity::state, ENEMY_CITIZEN);
        lua_setglobal(Entity::state, "ENEMY_CITIZEN");
        lua_pushnumber(Entity::state, WILD_ANIMAL);
        lua_setglobal(Entity::state, "WILD_ANIMAL");
        lua_pushnumber(Entity::state, PEACEFULL_ANIMAL);
        lua_setglobal(Entity::state, "PEACEFULL_ANIMAL");
        lua_pushnumber(Entity::state, DEFAULT_ENTITY);
        lua_setglobal(Entity::state, "DEFAULT_ENTITY");

        Entity::bLuaInit = true;
    }
}

// GETTERS :

sf::Vector2f Entity::getPosition( void ) const
{
    return m_position;
}





