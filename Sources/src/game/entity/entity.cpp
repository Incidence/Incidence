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
    m_position = sf::Vector2f(200, 200);
    m_angle = 0;
    m_speed = 40;
    m_bag = 0;
    m_action = IDLE;
    m_ressource = NOTHING;

    m_animation.load( "data/perso.ani" );

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
    s->setOrigin(16, 16);
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
    bool bNearHome = true; // vrai = proche home

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

int Entity::getAngle( lua_State * L )
{
    lua_pushnumber(L, m_angle);
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

    if(m_game && m_game->m_tilemap) {
        sf::Vector2i posMap = (m_game->m_tilemap)->getXY(m_position);

        for(int x = posMap.x - m_perception; x < posMap.x + m_perception; ++x) {
            for(int y = posMap.y - m_perception; y < posMap.y + m_perception; ++y) {
                Element * pElement = m_game->m_tilemap->getElement( sf::Vector2i(x, y) );
                if( pElement && distance(posMap, sf::Vector2i(x, y)) < m_perception && pElement->containResource(m_ressource) ) {
                    std::list< sf::Vector2f > w = m_game->m_tilemap->findWay(m_position, m_game->m_tilemap->getAbs(sf::Vector2i(x, y)), 30);
                    bNearest = !w.empty();
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

    if(m_game && m_game->m_tilemap) {
        // Vrai si ELEMENT avec M_RESSOURCE à portee de recolte (case adjacente)
        sf::Vector2i posMap = (m_game->m_tilemap)->getXY(m_position);
        Element * pElementRight = m_game->m_tilemap->getElement( sf::Vector2i(posMap.x + 1, posMap.y) );
        Element * pElementLeft = m_game->m_tilemap->getElement( sf::Vector2i(posMap.x - 1, posMap.y) );
        Element * pElementUp = m_game->m_tilemap->getElement( sf::Vector2i(posMap.x, posMap.y + 1) );
        Element * pElementDown = m_game->m_tilemap->getElement( sf::Vector2i(posMap.x, posMap.y - 1) );

        bNear =((pElementDown && pElementDown->containResource(m_ressource)) ||
                (pElementLeft && pElementLeft->containResource(m_ressource)) ||
                (pElementRight && pElementRight->containResource(m_ressource)) ||
                (pElementUp && pElementUp->containResource(m_ressource)) );
    }

    lua_pushboolean(L, bNear);
    return 1;
}


// **********

void Entity::goHome( void )
{
    /// TODO
    m_action = IDLE;
}

void Entity::move( void )
{
    if(m_game && m_game->m_tilemap) {

        if(m_way.empty()) {
            sf::Vector2f vDirect;
            vDirect.x = cos(m_angle / 180 * M_PI) * 2 * 32 + m_position.x;
            vDirect.y = sin(m_angle / 180 * M_PI) * 2 * 32 + m_position.y;

            /// RECODE : 30
            m_way = m_game->m_tilemap->findWay(m_position, vDirect, 30);
        }

        sf::Vector2f dest = m_way.front();

        float div = distance(dest, m_position);

        if(div < 2) {
            m_position = dest;
            m_way.pop_front();
        } else {
            dest.x = (dest.x - m_position.x) / div;
            dest.y = (dest.y - m_position.y) / div;

            m_position.x += dest.x * m_speed * Time::get()->deltaTime();
            m_position.y += dest.y * m_speed * Time::get()->deltaTime();
        }

        if(m_way.empty()) {
            m_action = IDLE;
        }
    }

}

void Entity::attack( void )
{
    /// TODO
    m_action = IDLE;
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

    if(m_game && m_game->m_tilemap) {
        sf::Vector2i posMap = (m_game->m_tilemap)->getXY(m_position);
        sf::Vector2i posNearest( sf::Vector2i(posMap.x + 10000, posMap.y + 10000) ); // To infinte !

        for(int x = posMap.x - m_perception; x < posMap.x + m_perception; ++x) {
            for(int y = posMap.y - m_perception; y < posMap.y + m_perception; ++y) {
                Element * pElement = m_game->m_tilemap->getElement( sf::Vector2i(x, y) );
                if(pElement && distance(posMap, sf::Vector2i(x, y)) < m_perception && pElement->containResource(m_ressource) ) {
                    if(distance(posMap, sf::Vector2i(x, y)) < distance(posMap, posNearest)) {
                        posNearest = sf::Vector2i(x, y);
                    }
                }
            }
        }

        if(distance(posMap, posNearest) < m_perception) {
            /// RECODE : 30
            m_way = m_game->m_tilemap->findWay(m_position, m_game->m_tilemap->getAbs(posNearest), 30);
            m_action = MOVE;
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

    if(m_game && m_game->m_tilemap) {
        sf::Vector2i mapPos = m_game->m_tilemap->getXY(m_position);
        int iElementNeighbor = 0;
        Element * pElement = NULL;
        mapPos.x += 1; // RIGHT
        pElement = m_game->m_tilemap->getElement(mapPos);
        iElementNeighbor = (pElement && pElement->containResource(m_ressource)) ? 1 : iElementNeighbor;

        mapPos = m_game->m_tilemap->getXY(m_position);
        mapPos.x -= 1; // LEFT
        pElement = m_game->m_tilemap->getElement(mapPos);
        iElementNeighbor = (pElement && pElement->containResource(m_ressource)) ? 2 : iElementNeighbor;

        mapPos = m_game->m_tilemap->getXY(m_position);
        mapPos.y += 1; //UP
        pElement = m_game->m_tilemap->getElement(mapPos);
        iElementNeighbor = (pElement && pElement->containResource(m_ressource)) ? 3 : iElementNeighbor;

        mapPos = m_game->m_tilemap->getXY(m_position);
        mapPos.y -= 1; // DOWN
        pElement = m_game->m_tilemap->getElement(mapPos);
        iElementNeighbor = (pElement && pElement->containResource(m_ressource)) ? 4 : iElementNeighbor;

        mapPos = m_game->m_tilemap->getXY(m_position);
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

        pElement = m_game->m_tilemap->getElement(mapPos);
        if(pElement) {
            m_bag = pElement->getQuantityOf(m_ressource);
            m_game->m_tilemap->removeElement(mapPos);
        }
    }

    m_action = IDLE;
}

void Entity::giveResource( void )
{
    /// TODO

    /*
        Home proche ?
            donner ressource
        Sinon RIEN
    */
    m_bag = 0;
    m_action = IDLE;
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
        lua_pushnumber(Entity::state, PEACEFUL_ANIMAL);
        lua_setglobal(Entity::state, "PEACEFUL_ANIMAL");
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


void Entity::setPosition( sf::Vector2f p )
{
    m_position = p;
    m_way.clear();
    m_action = IDLE;
}





