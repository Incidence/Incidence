#ifndef _SCRIPT_STATE_
#define _SCRIPT_STATE_

#include "../engine/state.hpp"
#include "../game/entity/lumberjack.hpp"

class ScriptState : public State
{

public :
    ScriptState( void );
    ~ScriptState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );

private :

    Lumberjack e;
};

#endif // _SCRIPT_STATE_

