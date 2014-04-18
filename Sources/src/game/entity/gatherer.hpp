#ifndef _LUMBERJACK_
#define _LUMBERJACK_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class Gatherer : public Entity
{

public :
    Gatherer( EntityType t, Game * game );
    Gatherer(lua_State * L);
    virtual ~Gatherer( void );

    virtual void init( void );

    virtual void callScript( void );


private :
    friend class Lunar<Gatherer>;
	static const char className[];
	static Lunar<Gatherer>::RegType methods[];

};

#endif // _LUMBERJACK_

