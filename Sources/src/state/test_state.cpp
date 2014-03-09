#include "test_state.hpp"

#include "../game/game.hpp"

TestState::TestState( void ) : m_game(NULL)
{
    m_game = new Game();
}

TestState::~TestState( void )
{
    if(m_game) {
        delete m_game;
    }
}

void TestState::init( void )
{

}

void TestState::draw( sf::RenderTarget & window )
{
    m_game->draw(window);
}

void TestState::update( void )
{

}

void TestState::handleEvent( sf::Event & e )
{
    if( e.type == sf::Event::KeyPressed )
    {
        switch(e.key.code)
        {
            case sf::Keyboard::Space :
            {
                m_game->addEntity(new Lumberjack(ALLY_CITIZEN, m_game));
            } break;

            default :
                break;

        }

    }
}
