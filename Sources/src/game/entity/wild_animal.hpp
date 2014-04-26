#ifndef _WILD_ANIMAL_
#define _WILD_ANIMAL_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class WildAnimal : public Entity
{

public :
    WildAnimal( EntityType t, Game * game );
    WildAnimal(lua_State * L);
    virtual ~WildAnimal( void );

    virtual void init( void );

    virtual void callScript( void );

    void initAnimations();


private :
    friend class Lunar<WildAnimal>;
	static const char className[];
	static Lunar<WildAnimal>::RegType methods[];

};

#endif // _WILD_ANIMAL_

