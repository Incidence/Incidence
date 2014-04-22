#include "entity.hpp"

#include "../../engine/time.hpp"
#include "../../engine/foo.hpp"
#include "entity_set.hpp"
#include <cmath>



#define TEMPS_PI 5000//temps de base pour qu'une entité donne des PI en ms


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
    m_target = NULL;
    m_isAttacked = false;

    m_perception = 5;
    m_position = sf::Vector2f(200, 200);
    m_angle = 0;
    m_speed = 40;
    m_bag = 0;
    m_action = IDLE;
    m_ressource = NOTHING;
    m_health = GOOD;
    m_waitTime = 0;
    m_giveTime=Time::get()->elapsed().asMilliseconds()+rand()%10+TEMPS_PI;
    m_giveQuantity=2;
    m_animation.load( "data/perso_lu.ani" );

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
    EntitySet * e = new EntitySet;

    if(m_game) {
        /// TODO : Completer la liste

        std::vector< Entity * > listEntities = m_game->getEntities();

        for(unsigned int i = 0; i < listEntities.size(); ++i) {
            if(listEntities[i] != this && !listEntities[i]->isDead() && distance(listEntities[i]->getPosition(), m_position) <= m_perception * 32) {
                EntityStruct * eStruct = new EntityStruct;

                eStruct->s_distance = distance(m_position, listEntities[i]->m_position);
                eStruct->s_angle = eStruct->s_distance > 0 ? std::atan2(listEntities[i]->getPosition().y - getPosition().y, listEntities[i]->getPosition().x - getPosition().x) : 0;
                eStruct->s_type = listEntities[i]->m_type;
                eStruct->s_id = i;
                eStruct->s_health = listEntities[i]->m_health;

                e->add(eStruct);
            }
        }
    }

    Lunar<EntitySet>::push(L, e, true);

    //delete e;

    return 1;
}

bool Entity::isNearHome( void )
{
    if(m_type != ALLY_CITIZEN && m_type != HUNTER) { return true; }
    if(m_game && m_game->m_tilemap) {
        return distance(m_game->m_tilemap->getAbs(m_game->m_home.getPosition()), m_position) <= 32;
    }

    return false;
}

int Entity::isNearHome( lua_State * L )
{
    bool bNearHome = isNearHome(); // vrai = proche home

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
    int argc = lua_gettop(L);
    if( argc > 0 && lua_isnumber(L, 1)) {
        m_angle = lua_tonumber(L, 1);
    }
    return 0;
}

int Entity::getHealth( lua_State * L )
{
    lua_pushnumber(L, m_health);
    return 1;
}

int Entity::isAttacked( lua_State * L )
{
    bool attacked = m_isAttacked;

    lua_pushboolean(L, attacked);
    return 1;
}


int Entity::setTarget( lua_State * L )
{
    int argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    if(m_game) {
        m_target = m_game->getEntity(id);
        if(m_target == this) { m_target = NULL; }
        //else { m_target->m_isAttacked = true; }
    }

    return 0;
}


int Entity::isAttackMe( lua_State * L )
{
    int argc = lua_gettop(L);
    int id = -1;
    if( argc > 0 && lua_isnumber(L, 1)) {
        id = lua_tonumber(L, 1);
    }

    Entity * e;
    if(m_game && (e = m_game->getEntity(id))) {
        lua_pushboolean(L, e->m_target == this);
        return 1;
    } else {
        return 0;
    }
}

int Entity::getNearestResource( lua_State * L )
{
    // True s'i y a une ressource dans le champs de perception
    if(m_game && m_game->m_tilemap) {
        sf::Vector2i posMap = (m_game->m_tilemap)->getXY(m_position);

        for(int x = posMap.x - m_perception; x <= posMap.x + m_perception; ++x) {
            for(int y = posMap.y - m_perception; y <= posMap.y + m_perception; ++y) {
                Harvestable * pHarvestable = m_game->m_tilemap->getHarvestable( sf::Vector2i(x, y) );
                if( pHarvestable && distance(posMap, sf::Vector2i(x, y)) <= m_perception && pHarvestable->containRessource(m_ressource) ) {
                    std::list< sf::Vector2f > w = m_game->m_tilemap->findWay(m_position, m_game->m_tilemap->getAbs(sf::Vector2i(x, y)), 30, m_perception);
                    if(!w.empty()) {
                        lua_pushboolean(L, true);
                        return 1;
                    }
                }
            }
        }
    }

    lua_pushboolean(L, false);
    return 1;
}

int Entity::isNearResource( lua_State * L )
{
    bool bNear = false;

    if(m_game && m_game->m_tilemap) {
        // Vrai si ELEMENT avec M_RESSOURCE à portee de recolte (case adjacente)
        sf::Vector2i posMap = (m_game->m_tilemap)->getXY(m_position);
        Harvestable * pHarvestableRight = m_game->m_tilemap->getHarvestable( sf::Vector2i(posMap.x + 1, posMap.y) );
        Harvestable * pHarvestableLeft = m_game->m_tilemap->getHarvestable( sf::Vector2i(posMap.x - 1, posMap.y) );
        Harvestable * pHarvestableUp = m_game->m_tilemap->getHarvestable( sf::Vector2i(posMap.x, posMap.y + 1) );
        Harvestable * pHarvestableDown = m_game->m_tilemap->getHarvestable( sf::Vector2i(posMap.x, posMap.y - 1) );

        bNear =((pHarvestableDown && pHarvestableDown->containRessource(m_ressource)) ||
                (pHarvestableLeft && pHarvestableLeft->containRessource(m_ressource)) ||
                (pHarvestableRight && pHarvestableRight->containRessource(m_ressource)) ||
                (pHarvestableUp && pHarvestableUp->containRessource(m_ressource)) );
    }

    lua_pushboolean(L, bNear);
    return 1;
}

int Entity::getDistanceToHome( lua_State * L )
{
    int argc = lua_gettop(L);
    int d = 0;

    if( argc > 0 && lua_isnumber(L, 1)) {
        int id = -1;
        id = lua_tonumber(L, 1);
        if(id != -1) {
            d = distance(m_game->m_tilemap->getAbs(m_game->m_home.getPosition()), m_game->m_entityList[id]->getPosition());
        }
        // la distance d'une entites
    } else {
        // ma propre distance
        d = distance(m_game->m_tilemap->getAbs(m_game->m_home.getPosition()), m_position);
    }

    lua_pushnumber(L, d);
    return 1;
}

int Entity::getAngleToHome( lua_State * L )
{
    /// RECODE

    lua_pushnumber(L, 0);
    return 1;
}


// **********

void Entity::goHome( void )
{
    if( ( m_type == ALLY_CITIZEN || m_type == HUNTER ) && m_game && m_game->m_tilemap) {
        m_way = m_game->m_tilemap->findWay(m_position, m_game->m_tilemap->getAbs(m_game->m_home.getPosition()), 30, 99999);
        std::cout << m_way.size() << std::endl;
        m_action = MOVE;
    }
    else {
        m_action = IDLE;
    }
}

void Entity::move( void )
{
    if(m_game && m_game->m_tilemap) {

        if(m_way.empty()) {
            sf::Vector2f vDirect;
            vDirect.x = cos(m_angle) * 3 * 32 + m_position.x;
            vDirect.y = sin(m_angle) * 3 * 32 + m_position.y;

            /// RECODE : 30
            m_way = m_game->m_tilemap->findWay(m_position, vDirect, 30, m_perception);
        }

        m_game->m_tilemap->m_cut = m_way;
        sf::Vector2f dest = m_way.front();

        float div = distance(dest, m_position);

        if(div < 2) {
            m_position = dest;
			// résoud le free() : invalid pointer mais les entités se bloquent vers les murs :
			// - soit fonction move ou pathfinding à modifier
			// - soit les entités sont connes
			// Rq : un hunter bloqué devant un mur se redéplace pour attaquer un ennemi donc
			// je pencherais plutôt pour la deuxième solution :-p
            if(m_way.size() > 0) {
				m_way.pop_front();
			}
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
    if(m_target) {
        if(m_target->isDead()) {
            m_action = IDLE;
            m_target->m_isAttacked = false;
            m_target = NULL;
        }
        else if(nearEntity(m_target)) {
            m_target->isAttackedBy(this);
            m_action = IDLE;
        }
        else {
            float dist = distance(m_target->getPosition(), getPosition());
            m_angle = dist > 0 ? std::atan2(m_target->getPosition().y - getPosition().y, m_target->getPosition().x - getPosition().x) : 0;
            m_action = MOVE;
            move();
        }
    } else {
        m_action = IDLE;
    }

}


void Entity::goNearestResource( void )
{
    /*
        Cherche l'ELEMENT avec M_RESSOURCE le plus proche
            pathfinding vers ELEMENT
            action = MOVE
        Sinon RIEN
    */

    m_way.clear();

    if(m_game && m_game->m_tilemap) {
        sf::Vector2i posMap = (m_game->m_tilemap)->getXY(m_position);
        float posNearest = 10000; // To infinite !

        for(int x = posMap.x - m_perception; x <= posMap.x + m_perception; ++x) {
            for(int y = posMap.y - m_perception; y <= posMap.y + m_perception; ++y) {
                Harvestable * pHarvestable = m_game->m_tilemap->getHarvestable( sf::Vector2i(x, y) );
                /// AMELIORATION
                if(pHarvestable && distance(posMap, sf::Vector2i(x, y)) <= m_perception && pHarvestable->containRessource(m_ressource) ) {
                    std::list< sf::Vector2f > w = m_game->m_tilemap->findWay(m_position, m_game->m_tilemap->getAbs(sf::Vector2i(x, y)), 30, m_perception);

                    // Calcul distance a faire, si < nearest : = m_way
                    if(!w.empty()) {
                        float dist = 0;
                        sf::Vector2f current = *(w.begin());
                        for(std::list< sf::Vector2f >::iterator it = w.begin(); it != w.end(); ++it) {
                            dist += distance(current, *it);
                            current = (*it);
                        }

                        if(dist < posNearest) {
                            posNearest = dist;
                            m_way = w;
                        }
                    }
                }
            }
        }

        if(!m_way.empty()) {
            m_action = MOVE;
        } else {
            m_action = IDLE;
        }
    }
}

void Entity::takeResource( void )
{
    /*
        ELEMENT avec du M_RESSOURCE proche ?
            prendre ressource
        Sinon RIEN
    */

    if(m_game && m_game->m_tilemap) {
        sf::Vector2i mapPos = m_game->m_tilemap->getXY(m_position);
        int iHarvestableNeighbor = 0;
        Harvestable * pHarvestable = NULL;
        mapPos.x += 1; // RIGHT
        pHarvestable = m_game->m_tilemap->getHarvestable(mapPos);
        iHarvestableNeighbor = (pHarvestable && pHarvestable->containRessource(m_ressource)) ? 1 : iHarvestableNeighbor;

        mapPos = m_game->m_tilemap->getXY(m_position);
        mapPos.x -= 1; // LEFT
        pHarvestable = m_game->m_tilemap->getHarvestable(mapPos);
        iHarvestableNeighbor = (pHarvestable && pHarvestable->containRessource(m_ressource)) ? 2 : iHarvestableNeighbor;

        mapPos = m_game->m_tilemap->getXY(m_position);
        mapPos.y += 1; //UP
        pHarvestable = m_game->m_tilemap->getHarvestable(mapPos);
        iHarvestableNeighbor = (pHarvestable && pHarvestable->containRessource(m_ressource)) ? 3 : iHarvestableNeighbor;

        mapPos = m_game->m_tilemap->getXY(m_position);
        mapPos.y -= 1; // DOWN
        pHarvestable = m_game->m_tilemap->getHarvestable(mapPos);
        iHarvestableNeighbor = (pHarvestable && pHarvestable->containRessource(m_ressource)) ? 4 : iHarvestableNeighbor;

        mapPos = m_game->m_tilemap->getXY(m_position);
        switch(iHarvestableNeighbor) {
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
                m_action = IDLE;
                pHarvestable = NULL;
                return;
                break;
        }

        pHarvestable = m_game->m_tilemap->getHarvestable(mapPos);
        m_recolt = mapPos;
        m_waitTime = Time::get()->elapsed().asMilliseconds() + pHarvestable->getPickingTime();

        m_action = RECOLT;
    } else {
        m_action = IDLE;
    }
}

void Entity::recolting( void )
{
    Harvestable * pHarvestable = m_game->m_tilemap->getHarvestable(m_recolt);

    if(!pHarvestable) {
        m_action = IDLE;
        return;
    }

    if(Time::get()->elapsed().asMilliseconds() > m_waitTime) {
        m_bag = pHarvestable->getQuantityOf(m_ressource);

        if(m_game && m_game->m_tilemap) {
            m_game->m_tilemap->removeElement(m_recolt);
        }
        // Add tronc ?

        m_action = IDLE;
        pHarvestable = NULL;
    }
}

void Entity::giveResource( void )
{
    if(isNearHome()) {
        m_game->addRessource(m_ressource, m_bag);
        m_bag = 0;
    }
    /*
        Home proche ?
            donner ressource
        Sinon RIEN
    */
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
        lua_pushnumber(Entity::state, HUNTER);
        lua_setglobal(Entity::state, "HUNTER");
        lua_pushnumber(Entity::state, WILD_ANIMAL);
        lua_setglobal(Entity::state, "WILD_ANIMAL");
        lua_pushnumber(Entity::state, PEACEFUL_ANIMAL);
        lua_setglobal(Entity::state, "PEACEFUL_ANIMAL");
        lua_pushnumber(Entity::state, DEFAULT_ENTITY);
        lua_setglobal(Entity::state, "DEFAULT_ENTITY");

        // Init Variable global pour LUA
        lua_pushnumber(Entity::state, GOOD);
        lua_setglobal(Entity::state, "GOOD");
        lua_pushnumber(Entity::state, NORMAL);
        lua_setglobal(Entity::state, "NORMAL");
        lua_pushnumber(Entity::state, WEAK);
        lua_setglobal(Entity::state, "WEAK");
        lua_pushnumber(Entity::state, VERY_WEAK);
        lua_setglobal(Entity::state, "VERY_WEAK");
        lua_pushnumber(Entity::state, DEAD);
        lua_setglobal(Entity::state, "DEAD");

        Entity::bLuaInit = true;
    }
}


bool Entity::nearEntity( const Entity * e )
{
    /// RECODE : 32 (taille entity)
    return distance(this->getPosition(), e->getPosition()) < 32;
}

void Entity::isAttackedBy( Entity * e )
{
    m_isAttacked = true;

    int hit = rand() % 100;
    if(hit > 50) {

        switch(m_health) {
        case GOOD :
            m_health = NORMAL;
            break;

        case NORMAL :
            m_health = WEAK;
            break;

        case WEAK :
            m_health = VERY_WEAK;
            break;

        case VERY_WEAK :
            m_health = DEAD;
            break;

        default :
            m_health = DEAD;
            break;
        }
    }

    if(m_target) {
        m_target->m_isAttacked = false;
    }
}

bool Entity::isDead() const
{
    return m_health == DEAD;
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


void Entity::updateGiveTime(float t)
{
    m_giveTime=t;
    switch(m_health)
    {
    case GOOD:
        m_giveTime+=TEMPS_PI+rand()%10000;
        break;

    case NORMAL:
        m_giveTime+=TEMPS_PI+rand()%10000+2000;
        break;

    case WEAK:
        m_giveTime+=TEMPS_PI+rand()%10000+6000;
        break;

    case VERY_WEAK:
        m_giveTime+=TEMPS_PI+rand()%10000+10000;
        break;

        //default
    }
}

float Entity::getGiveTime()
{
    return m_giveTime;
}

int Entity::getGiveQuantity()
{
    return m_giveQuantity;
}

void Entity::updateGiveQuantity()
{
    switch(m_health)
    {
    case GOOD:
        m_giveQuantity=2;
        break;

    case NORMAL:
        m_giveQuantity=2;
        break;

    case WEAK:
        m_giveQuantity=1;
        break;

    case VERY_WEAK:
        m_giveQuantity=1;
        break;
    }
}



