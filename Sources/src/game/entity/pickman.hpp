#ifndef _PICKMAN_
#define _PICKMAN_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class Pickman : public Entity
{

public :
    Pickman( EntityType t, Game * game, Entity * e = NULL );
    Pickman(lua_State * L);
    virtual ~Pickman( void );

    virtual void init( void );

    virtual void callScript( void );

    void initAnimations();


private :
    friend class Lunar<Pickman>;
	static const char className[];
	static Lunar<Pickman>::RegType methods[];

};

#endif // _PICKMAN_

