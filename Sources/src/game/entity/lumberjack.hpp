#ifndef _LUMBERJACK_
#define _LUMBERJACK_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class Lumberjack : public Entity
{

public :
    Lumberjack( EntityType t, Game * game );
    Lumberjack(lua_State * L);
    virtual ~Lumberjack( void );

    virtual void init( void );

    virtual void callScript( void );

    void initAnimations();


private :
    friend class Lunar<Lumberjack>;
	static const char className[];
	static Lunar<Lumberjack>::RegType methods[];

};

#endif // _LUMBERJACK_

