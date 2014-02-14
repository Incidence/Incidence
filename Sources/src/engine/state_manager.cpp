#include "state_manager.hpp"

#include "state.hpp"

StateManager * StateManager::singleton = NULL;

StateManager * StateManager::get( void )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    return StateManager::singleton;
}

void StateManager::kill( void )
{
    if(StateManager::singleton)
    {
        delete StateManager::singleton;
        StateManager::singleton = NULL;
    }
}


StateManager::StateManager( void ) : m_pop(false) { }

StateManager::~StateManager( void )
{
    while( ! m_stateManaged.empty() )
    {
        State * s = m_stateManaged.top();
        delete s;
        s = NULL;
        m_stateManaged.pop();
    }
}


void StateManager::update( void )
{
    if(m_current) {
        m_current->update();
    }
}

void StateManager::draw( sf::RenderTarget & window )
{
    if(m_current) {
        m_current->draw( window );
    }
}

void StateManager::handleEvent( sf::Event & e )
{
    if(m_current) {
        m_current->handleEvent( e );
    }
}

void StateManager::addState( State * s )
{
    m_stateManaged.push( s );
}


void StateManager::popState( void )
{
    m_pop = true;
}

void StateManager::deleteState( void )
{
    if( m_pop )
    {
        m_pop = false;

        State * s = getCurrent();
        if(s)
        {
            delete s;
            s = NULL;
            m_stateManaged.pop();
        }
    }
}

State * StateManager::getCurrent( void )
{
    return m_current;
}

void StateManager::setCurrent( void )
{
    deleteState();

    if(!isEmpty())
    {
        m_current = m_stateManaged.top();
    }
    else
    {
        m_current = NULL;
    }
}

bool StateManager::isEmpty( void ) const
{
    return m_stateManaged.empty();
}

