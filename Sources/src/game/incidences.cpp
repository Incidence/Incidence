#include "incidences.hpp"

void doIncidences() {
	
	//TODO
	
}

/*
 *** Description : cette fonction met à jour les cases environnantes, et si besoin harmonise les types compatibles.
 *
 *** Entree : la carte (tilemap), le type souhaité (type), la position (position).
 *** Sortie : void
*/
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
				if(tilemap->areCompatibleGrounds(position, sf::Vector2i(i - 1, j)) == 0) {
					spreadGround(tilemap, oldType, sf::Vector2i(i - 1, j));
				}
			}
			if(j > 0) {
				if(tilemap->areCompatibleGrounds(position, sf::Vector2i(i, j - 1)) == 0) {
					spreadGround(tilemap, oldType, sf::Vector2i(i, j - 1));
				}
			}
			if(i < width-1) {
				if(tilemap->areCompatibleGrounds(position, sf::Vector2i(i + 1, j)) == 0) {
					spreadGround(tilemap, oldType, sf::Vector2i(i + 1, j));
				}
			}
			if(j < height-1) {
				if(tilemap->areCompatibleGrounds(position, sf::Vector2i(i, j + 1)) == 0) {
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

/*
 *** Description : cette fonction dilate les zones ayant le comportement passé en paramètre.
 *
 *** Entree : la carte (tilemap), le comportement souhaité (behavior).
 *** Sortie : void
*/
void dilateGround(TileMap* tilemap, TileBehavior behavior) {
	
	srand(time(NULL));
	
	std::vector<sf::Vector2i> positions;
	std::vector<int> types;
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	Ground* l_ground;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			l_ground = tilemap->getGround(sf::Vector2i(i, j));
			
			if(l_ground != NULL && l_ground->getBehavior() == behavior) {
				
				int GROUND_type = l_ground->getType();
				
				if(i > 0 && rand()%ALEATOIRE == 0) {
					positions.push_back(sf::Vector2i(i - 1, j));
					types.push_back(GROUND_type);
				}
				if(j > 0 && rand()%ALEATOIRE == 0) {
					positions.push_back(sf::Vector2i(i, j - 1));
					types.push_back(GROUND_type);
				}
				if(i < width-1 && rand()%ALEATOIRE == 0) {
					positions.push_back(sf::Vector2i(i + 1, j));
					types.push_back(GROUND_type);
				}
				if(j < height-1 && rand()%ALEATOIRE == 0) {
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

/*
 *** Description : cette fonction érode les zones ayant le comportement passé en paramètre.
 *
 *** Entree : la carte (tilemap), le comportement souhaité (behavior).
 *** Sortie : void
*/
void erodeGround(TileMap* tilemap, TileBehavior behavior) {
	
	srand(time(NULL));
	
	std::vector<sf::Vector2i> positions;
	std::vector<int> types;
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	Ground* l_ground;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			l_ground = tilemap->getGround(sf::Vector2i(i, j));
			
			if(l_ground != NULL && l_ground->getBehavior() == behavior) {
				
				std::vector<int> GROUND_type;
				
				if(i > 0) {
					l_ground = tilemap->getGround(sf::Vector2i(i - 1, j));
					if(l_ground != NULL && l_ground->getBehavior() != behavior) {
						GROUND_type.push_back(l_ground->getType());
					}
				}
				if(j > 0) {
					l_ground = tilemap->getGround(sf::Vector2i(i, j - 1));
					if(l_ground != NULL && l_ground->getBehavior() != behavior) {
						GROUND_type.push_back(l_ground->getType());
					}
				}
				if(i < width-1) {
					l_ground = tilemap->getGround(sf::Vector2i(i + 1, j));
					if(l_ground != NULL && l_ground->getBehavior() != behavior) {
						GROUND_type.push_back(l_ground->getType());
					}
				}
				if(j < height-1) {
					l_ground = tilemap->getGround(sf::Vector2i(i, j + 1));
					if(l_ground != NULL && l_ground->getBehavior() != behavior) {
						GROUND_type.push_back(l_ground->getType());
					}
				}
				
				if(GROUND_type.size() != 0 && rand()%ALEATOIRE == 0) {
					positions.push_back(sf::Vector2i(i, j));
					types.push_back(GROUND_type[rand()%GROUND_type.size()]);
				}
			}
		}
	}
	
	for(int p(0) ; p < positions.size() ; ++p) {
		spreadGround(tilemap, types[p], positions[p]);
	}
	
}

/*
 *** Description : cette fonction dilate les zones d'éléments ayant le comportement passé en paramètre.
 *
 *** Entree : la carte (tilemap), le comportement souhaité (behavior).
 *** Sortie : void
*/
void dilateElement(TileMap* tilemap, TileBehavior behavior) {
	
	srand(time(NULL));
	
	std::vector<sf::Vector2i> positions;
	std::vector<int> types;
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	Element* l_element;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			l_element = tilemap->getElement(sf::Vector2i(i, j));
			
			if(l_element != NULL && l_element->getBehavior() == behavior) {
				
				int ELEMENT_type = l_element->getType();
				
				if(i > 0 && rand()%ALEATOIRE == 0 && tilemap->getElement(sf::Vector2i(i - 1, j)) == NULL) {
					positions.push_back(sf::Vector2i(i - 1, j));
					types.push_back(ELEMENT_type);
				}
				if(j > 0 && rand()%ALEATOIRE == 0 && tilemap->getElement(sf::Vector2i(i, j - 1)) == NULL) {
					positions.push_back(sf::Vector2i(i, j - 1));
					types.push_back(ELEMENT_type);
				}
				if(i < width-1 && rand()%ALEATOIRE == 0 && tilemap->getElement(sf::Vector2i(i + 1, j)) == NULL) {
					positions.push_back(sf::Vector2i(i + 1, j));
					types.push_back(ELEMENT_type);
				}
				if(j < height-1 && rand()%ALEATOIRE == 0 && tilemap->getElement(sf::Vector2i(i, j + 1)) == NULL) {
					positions.push_back(sf::Vector2i(i, j + 1));
					types.push_back(ELEMENT_type);
				}
			}
		}
	}
	
	for(int p(0) ; p < positions.size() ; ++p) {
		tilemap->addElement(types[p], positions[p]);
	}
	
}

/*
 *** Description : cette fonction érode les zones d'éléments ayant le comportement passé en paramètre.
 *
 *** Entree : la carte (tilemap), le comportement souhaité (behavior).
 *** Sortie : void
*/
void erodeElement(TileMap* tilemap, TileBehavior behavior) {
	
	srand(time(NULL));
	
	std::vector<sf::Vector2i> positions;
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	Element* l_element;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			l_element = tilemap->getElement(sf::Vector2i(i, j));
			
			if(l_element != NULL && l_element->getBehavior() == behavior) {
				
				if(i > 0 && rand()%ALEATOIRE == 0) {
					l_element = tilemap->getElement(sf::Vector2i(i - 1, j));
					if(l_element == NULL || l_element->getBehavior() != behavior) {
						positions.push_back(sf::Vector2i(i, j));
					}
				}
				if(j > 0 && rand()%ALEATOIRE == 0) {
					l_element = tilemap->getElement(sf::Vector2i(i, j - 1));
					if(l_element == NULL || l_element->getBehavior() != behavior) {
						positions.push_back(sf::Vector2i(i, j));
					}
				}
				if(i < width-1 && rand()%ALEATOIRE == 0) {
					l_element = tilemap->getElement(sf::Vector2i(i + 1, j));
					if(l_element == NULL || l_element->getBehavior() != behavior) {
						positions.push_back(sf::Vector2i(i, j));
					}
				}
				if(j < height-1 && rand()%ALEATOIRE == 0) {
					l_element = tilemap->getElement(sf::Vector2i(i, j + 1));
					if(l_element == NULL || l_element->getBehavior() != behavior) {
						positions.push_back(sf::Vector2i(i, j));
					}
				}
			}
		}
	}
	
	for(int p(0) ; p < positions.size() ; ++p) {
		tilemap->removeElement(positions[p]);
	}
	
}

void dilateFluids(TileMap* tilemap) {
	
	dilateGround(tilemap, FLUID);
	
}

void erodeFluids(TileMap* tilemap) {
	
	erodeGround(tilemap, FLUID);
	
}

void dilateCliffs(TileMap* tilemap) {
	
	dilateGround(tilemap, CLIFF);
	
}

void erodeCliffs(TileMap* tilemap) {
	
	erodeGround(tilemap, CLIFF);
	
}

void mixGround(TileMap* tilemap) {
	
	srand(time(NULL));
	
	if(rand()%2 == 0) {
		erodeGround(tilemap, DEFAULT);
	}
	else {
		dilateGround(tilemap, DEFAULT);
	}
	
}

void dilateForests(TileMap* tilemap) {
	
	dilateElement(tilemap, FOREST);
	
}

void erodeForests(TileMap* tilemap) {
	
	erodeElement(tilemap, FOREST);
	
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
