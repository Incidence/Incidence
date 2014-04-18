#ifndef _PEACEFUL_ANIMAL_
#define _PEACEFUL_ANIMAL_

#include "SFML/Graphics.hpp"

#include <cstdio>
#include <lua.hpp>
#include "lunar.h"

#include "../../engine/animation.hpp"
#include "entity.hpp"

class PeacefulAnimal : public Entity
{

public :
    PeacefulAnimal( EntityType t, Game * game );
    PeacefulAnimal(lua_State * L);
    virtual ~PeacefulAnimal( void );

    virtual void init( void );

    virtual void callScript( void );


private :
    friend class Lunar<PeacefulAnimal>;
	static const char className[];
	static Lunar<PeacefulAnimal>::RegType methods[];

};

#endif // _PEACEFUL_ANIMAL_

