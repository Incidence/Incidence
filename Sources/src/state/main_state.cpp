#include "main_state.hpp"

#include "../engine/animation.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/data_manager.hpp"

#include "SFML/Audio.hpp"

#include <cstdio>
#include <lua.hpp>

MainState::MainState( void )
{
    init();

        /// ////////////////////////////
    lua_State * state;
    // on créer un contexte d'exécution de Lua
    state = lua_open();
    // on charge les bibliothèques standards de Lua
    luaL_openlibs(state);

    // on vérifie si le script existe bien
    if(luaL_dofile(state,"lua/hello.lua") != 0)
    {
        // il y a eu une erreur dans le script
        fprintf(stderr,"%s\n",lua_tostring(state,-1));
        exit(0);
    }
        /// ///////////////////////////

}

MainState::~MainState( void ) { }

void MainState::init( void )
{
    a_goku.load( "data/goku_up.ani" );
    a_goku.m_position = sf::Vector2f( 80, 80 );
    stay = true;
    a_energy.m_position = sf::Vector2f(40, 0);
    a_electricity.m_position = sf::Vector2f(70, 70);

    s_goku.setBuffer( * DataManager::get()->getSoundBuffer( "data/sound/goku_haa.wav" ) );
    s_aura_up.setBuffer( * DataManager::get()->getSoundBuffer( "data/sound/aura_up.wav" ) );
    s_aura_lp.setBuffer( * DataManager::get()->getSoundBuffer( "data/sound/aura_loop.wav" ) );
    s_electrik.setBuffer( * DataManager::get()->getSoundBuffer( "data/sound/electrik.wav" ) );
    s_aura_lp.setLoop(true);
    b_aura_up = false;
    b_electik = false;
}

void MainState::draw( sf::RenderTarget & window )
{
    sf::Sprite * s = NULL;

    s = a_energy.update();
    if(s) { window.draw( * s ); }
    s = a_goku.update();
    if(s) { window.draw( * s ); }
    s = a_electricity.update();
    if(s) { window.draw( * s ); }
}

void MainState::update( void )
{
    if(!a_goku.isPlay()) {
        if(stay) {
            a_goku.load( "data/goku_stay.ani" );
            stay = false;
        } else {
            StateManager::get()->popState();
        }
    }

    if(a_goku.getName() == "data/goku_up.ani" ) {
            if( a_goku.getIdFrame() == 5 && a_energy.getName() != "data/energy.ani") {
                a_energy.load( "data/energy.ani" );
                s_aura_up.play();
                b_aura_up = true;
            }
            if( a_goku.getIdFrame() == 4 && a_electricity.getName() != "data/electricity.ani") {
                a_electricity.load( "data/electricity.ani" );
                s_goku.play();
            }
    }

    if(a_goku.getName() == "data/goku_down.ani" ) {
        if(a_goku.getIdFrame() == 2) {
            a_energy.clean();
            s_aura_lp.stop();
        }
        if(a_goku.getIdFrame() == 3) {
            a_electricity.clean();
        }
    }

    if(b_aura_up && s_aura_up.getPlayingOffset().asMilliseconds() > 1000.0f) {
        s_aura_lp.play();
        b_aura_up = false;
    }

    if(a_electricity.getIdFrame() % 2 == 1) {
        if(b_electik && s_electrik.getStatus() != sf::SoundSource::Playing) {
            s_electrik.play();
            b_electik = false;
        }
    } else {
            b_electik = true;
    }
}

void MainState::handleEvent( sf::Event & e )
{
    if( e.type == sf::Event::KeyPressed )
    {
        switch(e.key.code)
        {
            case sf::Keyboard::Space :
            {
                a_goku.load( "data/goku_down.ani" );
            } break;

            default :
                break;

        }

    }
}
