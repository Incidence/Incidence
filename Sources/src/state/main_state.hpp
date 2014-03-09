#ifndef _MAIN_STATE_
#define _MAIN_STATE_

#include "../engine/state.hpp"
#include "../engine/animation.hpp"

#include <SFML/Audio.hpp>

class MainState : public State
{

public :
    MainState( void );
    ~MainState( void );

    void init( void );
    void draw( sf::RenderTarget & window );
    void update( void );
    void handleEvent( sf::Event & e );

private :
    Animation a_goku;
    Animation a_energy;
    Animation a_electricity;
    bool stay;

    sf::Sound s_goku;
    sf::Sound s_aura_up;
    sf::Sound s_aura_lp;
    sf::Sound s_electrik;
    bool b_aura_up;
    bool b_electik;
};

#endif // _MAIN_STATE_
