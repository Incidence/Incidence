#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/engine/state_manager.hpp"
#include "src/state/main_state.hpp"
#include "src/engine/time.hpp"
#include "src/Carte.hpp"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Incidence", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	
	TileSet tileset(sf::Vector2u(32,32));
	tileset.loadTilesetSol("Ressources/tileset_sol.png");
	tileset.loadTilesetObj("Ressources/tileset_obj.png");
	tileset.loadTilesetEnt("Ressources/tileset_ent.png");
	Carte carte(tileset, sf::Vector2u(10,10));
	carte.generate();
	
//    StateManager::get()->addState(new MainState());
	
	while (window.isOpen())// && !StateManager::get()->isEmpty())
    {
//        StateManager::get()->setCurrent();
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
//            StateManager::get()->handleEvent( event );
		}
		
//        StateManager::get()->update();

		window.clear();
//            StateManager::get()->draw( window );
		carte.draw(window, sf::RenderStates());
		window.display();

//        Time::get()->update();
	}
	
	return 0;
}
