#include "incidences.hpp"

void doIncidences() {
	
	//TODO
	
}

void erodeFluids(TileMap* tilemap) {
	
	std::vector<sf::Vector2i> positions;
	std::vector<int> types;
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			Ground* ground = tilemap->getGround(sf::Vector2i(i, j));
			
			if(ground->getBehavior() == FLUID) {
				int GROUND_type = ground->getType();
				
				if(i > 0) {
					ground = tilemap->getGround(sf::Vector2i(i - 1, j));
					if(ground->getBehavior() == DEFAULT) {
						GROUND_type = ground->getType();
					}
				}
				if(j > 0) {
					ground = tilemap->getGround(sf::Vector2i(i, j - 1));
					if(ground->getBehavior() == DEFAULT) {
						GROUND_type = ground->getType();
					}
				}
				if(i < width-1) {
					ground = tilemap->getGround(sf::Vector2i(i + 1, j));
					if(ground->getBehavior() == DEFAULT) {
						GROUND_type = ground->getType();
					}
				}
				if(j < height-1) {
					ground = tilemap->getGround(sf::Vector2i(i, j + 1));
					if(ground->getBehavior() == DEFAULT) {
						GROUND_type = ground->getType();
					}
				}
				
				positions.push_back(sf::Vector2i(i, j));
				types.push_back(GROUND_type);
			}
		}
	}
	
	for(int i(0) ; i < positions.size() ; ++i) {
		tilemap->changeGround(types[i], positions[i]);
	}
	
}

void dilateFluids(TileMap* tilemap) {
	
	std::vector<sf::Vector2i> positions;
	std::vector<int> types;
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			Ground* ground = tilemap->getGround(sf::Vector2i(i, j));
			
			if(ground->getBehavior() == FLUID) {
				int GROUND_type = ground->getType();
				
				if(i > 0) {
					positions.push_back(sf::Vector2i(i - 1, j));
					types.push_back(GROUND_type);
				}
				if(j > 0) {
					positions.push_back(sf::Vector2i(i, j - 1));
					types.push_back(GROUND_type);
				}
				if(i < width-1) {
					positions.push_back(sf::Vector2i(i + 1, j));
					types.push_back(GROUND_type);
				}
				if(j < height-1) {
					positions.push_back(sf::Vector2i(i, j + 1));
					types.push_back(GROUND_type);
				}
			}
		}
	}
	
	for(int i(0) ; i < positions.size() ; ++i) {
		tilemap->changeGround(types[i], positions[i]);
	}
	
}

void expandForests(TileMap* tilemap) {
	
	//TODO
	
}

void burnForests(TileMap* tilemap) {
	
	//TODO
	
}

void spawnRessources(TileMap* tilemap) {
	
	//TODO
	
}

void burnRessources(TileMap* tilemap) {
	
	//TODO
	
}

void spawnEntities(TileMap* tilemap) {
	
	//TODO
	
}

void killEntities(TileMap* tilemap) {
	
	//TODO
	
}

void citizenFeeding(TileMap* tilemap) {
	
	//TODO
	
}

void citizenSicken(TileMap* tilemap) {
	
	//TODO
	
}

void citizenBirth(TileMap* tilemap) {
	
	//TODO
	
}

void citizenJobUpdate(TileMap* tilemap) {
	
	//TODO
	
}

void bonusPI(TileMap* tilemap) {
	
	//TODO
	
}
