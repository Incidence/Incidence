#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/engine/state_manager.hpp"
#include "src/state/main_state.hpp"
#include "src/engine/time.hpp"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Engine TEST !");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    StateManager::get()->addState(new MainState());

    while (window.isOpen() && !StateManager::get()->isEmpty())
    {
        StateManager::get()->setCurrent();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            StateManager::get()->handleEvent( event );
        }

        StateManager::get()->update();

        window.clear();
            StateManager::get()->draw( window );
        window.display();

        Time::get()->update();
    }

    return 0;
}
