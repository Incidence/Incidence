#ifndef _GATHERER_
#define _GATHERER_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class Gatherer : public Entity
{

public :
    Gatherer( EntityType t, Game * game, Entity * e = NULL );
    Gatherer(lua_State * L);
    virtual ~Gatherer( void );

    virtual void init( void );

    virtual void callScript( void );

    void initAnimations();


private :
    friend class Lunar<Gatherer>;
	static const char className[];
	static Lunar<Gatherer>::RegType methods[];

};

#endif // _GATHERER_

