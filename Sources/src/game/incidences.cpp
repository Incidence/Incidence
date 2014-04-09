#include "incidences.hpp"

void doIncidences() {
	
	//TODO
	
}

void erodeFluids(TileMap* tilemap) {
	
	srand(time(NULL));
	
	std::vector<sf::Vector2i> positions;
	std::vector<int> types;
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	Ground* l_ground;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			l_ground = tilemap->getGround(sf::Vector2i(i, j));
			
			if(l_ground != NULL && l_ground->getBehavior() == FLUID) {
				
				std::vector<int> GROUND_type;
				GROUND_type.push_back(l_ground->getType());
				
				if(i > 0) {
					l_ground = tilemap->getGround(sf::Vector2i(i - 1, j));
					if(l_ground->getBehavior() == DEFAULT) {
						GROUND_type.push_back(l_ground->getType());
						GROUND_type.push_back(l_ground->getType());
					}
				}
				if(j > 0) {
					l_ground = tilemap->getGround(sf::Vector2i(i, j - 1));
					if(l_ground->getBehavior() == DEFAULT) {
						GROUND_type.push_back(l_ground->getType());
						GROUND_type.push_back(l_ground->getType());
					}
				}
				if(i < width-1) {
					l_ground = tilemap->getGround(sf::Vector2i(i + 1, j));
					if(l_ground->getBehavior() == DEFAULT) {
						GROUND_type.push_back(l_ground->getType());
						GROUND_type.push_back(l_ground->getType());
					}
				}
				if(j < height-1) {
					l_ground = tilemap->getGround(sf::Vector2i(i, j + 1));
					if(l_ground->getBehavior() == DEFAULT) {
						GROUND_type.push_back(l_ground->getType());
						GROUND_type.push_back(l_ground->getType());
					}
				}
				
				positions.push_back(sf::Vector2i(i, j));
				types.push_back(GROUND_type[rand()%GROUND_type.size()]);
			}
		}
	}
	
	for(int p(0) ; p < positions.size() ; ++p) {
		spreadGround(tilemap, types[p], positions[p]);
	}
	
}

void dilateFluids(TileMap* tilemap) {
	
	srand(time(NULL));
	
	std::vector<sf::Vector2i> positions;
	std::vector<int> types;
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	Ground* l_ground;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			l_ground = tilemap->getGround(sf::Vector2i(i, j));
			
			if(l_ground != NULL && l_ground->getBehavior() == FLUID) {
				
				int GROUND_type = l_ground->getType();
				
				if(i > 0 && rand()%3 == 0) {
					positions.push_back(sf::Vector2i(i - 1, j));
					types.push_back(GROUND_type);
				}
				if(j > 0 && rand()%3 == 0) {
					positions.push_back(sf::Vector2i(i, j - 1));
					types.push_back(GROUND_type);
				}
				if(i < width-1 && rand()%3 == 0) {
					positions.push_back(sf::Vector2i(i + 1, j));
					types.push_back(GROUND_type);
				}
				if(j < height-1 && rand()%3 == 0) {
					positions.push_back(sf::Vector2i(i, j + 1));
					types.push_back(GROUND_type);
				}
			}
		}
	}
	
	for(int p(0) ; p < positions.size() ; ++p) {
		spreadGround(tilemap, types[p], positions[p]);
	}
	
}

void spreadGround(TileMap* tilemap, int type, sf::Vector2i position) {
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	int i = position.x, j = position.y;
	
	Ground* l_ground = tilemap->getGround(position);
	
	if(l_ground != NULL) {
		
		// Changement du sol courant
		int oldType = l_ground->getType();
		if(type != oldType) {
			tilemap->changeGround(type, position);
			
			// Propagation
			if(i > 0) {
				l_ground = tilemap->getGround(sf::Vector2i(i - 1, j));
				if(l_ground != NULL && !(l_ground->hasBorderWith(type) || l_ground->getType() == type)) {
					spreadGround(tilemap, oldType, sf::Vector2i(i - 1, j));
				}
			}
			if(j > 0) {
				l_ground = tilemap->getGround(sf::Vector2i(i, j - 1));
				if(l_ground != NULL && !(l_ground->hasBorderWith(type) || l_ground->getType() == type)) {
					spreadGround(tilemap, oldType, sf::Vector2i(i, j - 1));
				}
			}
			if(i < width-1) {
				l_ground = tilemap->getGround(sf::Vector2i(i + 1, j));
				if(l_ground != NULL && !(l_ground->hasBorderWith(type) || l_ground->getType() == type)) {
					spreadGround(tilemap, oldType, sf::Vector2i(i + 1, j));
				}
			}
			if(j < height-1) {
				l_ground = tilemap->getGround(sf::Vector2i(i, j + 1));
				if(l_ground != NULL && !(l_ground->hasBorderWith(type) || l_ground->getType() == type)) {
					spreadGround(tilemap, oldType, sf::Vector2i(i, j + 1));
				}
			}
			
			// Mise à jour des bordures
			if(i > 0) {
				l_ground = tilemap->getGround(sf::Vector2i(i - 1, j));
				if(l_ground != NULL) {
					tilemap->changeGround(l_ground->getType(), sf::Vector2i(i - 1, j));
				}
			}
			if(j > 0) {
				l_ground = tilemap->getGround(sf::Vector2i(i, j - 1));
				if(l_ground != NULL) {
					tilemap->changeGround(l_ground->getType(), sf::Vector2i(i, j - 1));
				}
			}
			if(i < width-1) {
				l_ground = tilemap->getGround(sf::Vector2i(i + 1, j));
				if(l_ground != NULL) {
					tilemap->changeGround(l_ground->getType(), sf::Vector2i(i + 1, j));
				}
			}
			if(j < height-1) {
				l_ground = tilemap->getGround(sf::Vector2i(i, j + 1));
				if(l_ground != NULL) {
					tilemap->changeGround(l_ground->getType(), sf::Vector2i(i, j + 1));
				}
			}
		}
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
