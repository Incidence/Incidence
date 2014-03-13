#include "script_state.hpp"

#include "../game/entity_test/entity.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/data_manager.hpp"


ScriptState::ScriptState( void ) : e(ALLY_CITIZEN, NULL)
{
    init();
}

ScriptState::~ScriptState( void ) { }

void ScriptState::init( void )
{
}

void ScriptState::draw( sf::RenderTarget & window )
{
    sf::Sprite * s = NULL;

    s = e.draw();
    if(s) { window.draw( * s ); }
}

void ScriptState::update( void )
{

}

void ScriptState::handleEvent( sf::Event & e )
{
    if( e.type == sf::Event::KeyPressed )
    {
        switch(e.key.code)
        {
            case sf::Keyboard::Space :
            {
                // Call script here
                this->e.callScript();
            } break;

            default :
                break;

        }

    }
}

