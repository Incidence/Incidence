#ifndef _LUMBERJACK_
#define _LUMBERJACK_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class Pickman : public Entity
{

public :
    Pickman( EntityType t, Game * game );
    Pickman(lua_State * L);
    virtual ~Pickman( void );

    virtual void init( void );

    virtual void callScript( void );


private :
    friend class Lunar<Pickman>;
	static const char className[];
	static Lunar<Pickman>::RegType methods[];

};

#endif // _LUMBERJACK_

