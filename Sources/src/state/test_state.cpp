#include "test_state.hpp"

#include "../engine/state_manager.hpp"

#include "../game/game.hpp"
#include "../game/entity/lumberjack.hpp"
#include "../game/entity/enemy_citizen.hpp"

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
    m_game->update();
}

void TestState::handleEvent( sf::Event & e )
{
    if( e.type == sf::Event::KeyPressed )
    {
        switch(e.key.code)
        {
            case sf::Keyboard::A :
            {
                m_game->addEntity(new Lumberjack(ALLY_CITIZEN, m_game));
            } break;

            case sf::Keyboard::E :
            {
                m_game->addEntity(new EnemyCitizen(ENEMY_CITIZEN, m_game));
            } break;

            case sf::Keyboard::Escape :
            {
                StateManager::get()->popState();
            } break;

            default :
                break;

        }
    }

    m_game->handleEvent(e);
}
