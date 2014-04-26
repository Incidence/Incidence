#ifndef _ENEMY_CITIZEN_
#define _ENEMY_CITIZEN_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class EnemyCitizen : public Entity
{

public :
    EnemyCitizen( EntityType t, Game * game );
    EnemyCitizen(lua_State * L);
    virtual ~EnemyCitizen( void );

    virtual void init( void );

    virtual void callScript( void );

    void initAnimations();


private :
    friend class Lunar<EnemyCitizen>;
	static const char className[];
	static Lunar<EnemyCitizen>::RegType methods[];

};

#endif // _ENEMY_CITIZEN_


