#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/engine/state_manager.hpp"
#include "src/state/main_state.hpp"
#include "src/state/test_state.hpp"
#include "src/engine/time.hpp"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine TEST !");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
	
	sf::View mainView(sf::Vector2f(400,300), sf::Vector2f(800,600));
	window.setView(mainView);

    StateManager::get()->addState(new TestState());

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
        
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mainView.getCenter().x > 400) {
			mainView.move(-32,0);
			window.setView(mainView);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mainView.getCenter().x < 150*32-400) {
			mainView.move(32,0);
			window.setView(mainView);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mainView.getCenter().y > 300) {
			mainView.move(0,-32);
			window.setView(mainView);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mainView.getCenter().y < 150*32-300) {
			mainView.move(0,32);
			window.setView(mainView);
		}

        StateManager::get()->update();

        window.clear();
            StateManager::get()->draw( window );
        window.display();

        Time::get()->update();
    }

    return 0;
}
