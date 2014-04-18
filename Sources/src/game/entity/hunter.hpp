#ifndef _HUNTER_
#define _HUNTER_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class Hunter : public Entity
{

public :
    Hunter( EntityType t, Game * game );
    Hunter(lua_State * L);
    virtual ~Hunter( void );

    virtual void init( void );

    virtual void callScript( void );


private :
    friend class Lunar<Hunter>;
	static const char className[];
	static Lunar<Hunter>::RegType methods[];

};

#endif // _LUMBERJACK_

