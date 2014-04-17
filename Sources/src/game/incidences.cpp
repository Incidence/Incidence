#include "incidences.hpp"

template<typename T> bool contains(std::vector<T> vec, T val) {
	for(int i(0);i<vec.size();++i) { if(vec[i] == val) { return true; } } return false;
}

/*
 *** Description : Fonction du cycle jour nuit, applique toutes les incidences de la journée.
 *
 *** Entree : la carte (tilemap).
 *** Sortie : void
*/
void doIncidences(TileMap* tilemap) {
	
	//TODO : gérer la météo
	
	// Si 3 jours de pluie consécutifs
	dilateFluids(tilemap);
	
	// Si 5 jours de soleil consécutifs
	erodeFluids(tilemap);
	
	// Si 1 jour de pluie
	erodeNearCliffs(tilemap);
	dilateNearFluids(tilemap);
	
	// Si 1 jour de soleil
	erodeNearFluids(tilemap);
	dilateNearCliffs(tilemap);
	
	// Si 2 ou 3 jours de pluie parmi les 5 derniers jours
	dilateForests(tilemap);
	spawnRessources(tilemap);
	
	// Si 5 jours de soleil ou 5 jours de pluie consécutifs
	erodeForests(tilemap);
	burnRessources(tilemap);
	
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
			
			if(l_ground->getBehavior() == CLIFF) {
				oldType = type;
			}
			else {
				tilemap->changeGround(type, position);
			}
			
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
					
				for(int k(0) ; k < 4 ; ++k) {
					
					l_ground = NULL;
					
					if(k == 0 && i > 0) {
						l_ground = tilemap->getGround(sf::Vector2i(i - 1, j));
					}
					else if(k == 1 && j > 0) {
						l_ground = tilemap->getGround(sf::Vector2i(i, j - 1));
					}
					else if(k == 2 && i < width-1) {
						l_ground = tilemap->getGround(sf::Vector2i(i + 1, j));
					}
					else if(k == 3 && j < height-1) {
						l_ground = tilemap->getGround(sf::Vector2i(i, j + 1));
					}
					
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
 *** Description : cette fonction dilate les zones ayant le premier comportement passé en paramètre
 *                 et étant compatibles avec le second comportement passé en paramètre.
 *
 *** Entree : la carte (tilemap), le comportement souhaité (behavior), le comportement de compatibilité (behaviorNear).
 *** Sortie : void
*/
void dilateNearGround(TileMap* tilemap, TileBehavior behavior, TileBehavior behaviorNear) {
	
	std::vector<int> nears = (tilemap->getTileSet())->getGroundsByBehavior(behaviorNear);
	std::vector<int> nearCompatibles;
	
	for(int k(0) ; k < (tilemap->getTileSet())->getGroundCount() ; ++k) {
		bool add = true;
		for(int l(0) ; l < nears.size() ; ++l) {
			if(k == nears[l]) {
				add = false;
			}
		}
		if(add) {
			add = false;
			for(int l(0) ; l < nears.size() ; ++l) {
				if(tilemap->areCompatibleGrounds(k, nears[l]) == 1) {
					add = true;
				}
			}
			if(add) {
				nearCompatibles.push_back(k);
			}
		}
	}
	
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
				
				if(rand()%ALEATOIRE == 0 && contains(nearCompatibles, GROUND_type)) {
					
					if(i > 0 && rand()%ALEATOIRE == 0 && !contains(nears, (tilemap->getGround(sf::Vector2i(i - 1, j)))->getType())) {
						positions.push_back(sf::Vector2i(i - 1, j));
						types.push_back(GROUND_type);
					}
					if(j > 0 && rand()%ALEATOIRE == 0 && !contains(nears, (tilemap->getGround(sf::Vector2i(i, j - 1)))->getType())) {
						positions.push_back(sf::Vector2i(i, j - 1));
						types.push_back(GROUND_type);
					}
					if(i < width-1 && rand()%ALEATOIRE == 0 && !contains(nears, (tilemap->getGround(sf::Vector2i(i + 1, j)))->getType())) {
						positions.push_back(sf::Vector2i(i + 1, j));
						types.push_back(GROUND_type);
					}
					if(j < height-1 && rand()%ALEATOIRE == 0 && !contains(nears, (tilemap->getGround(sf::Vector2i(i, j + 1)))->getType())) {
						positions.push_back(sf::Vector2i(i, j + 1));
						types.push_back(GROUND_type);
					}
				}
			}
		}
	}
	
	for(int p(0) ; p < positions.size() ; ++p) {
		spreadGround(tilemap, types[p], positions[p]);
	}
	
}

/*
 *** Description : cette fonction érode les zones ayant le premier comportement passé en paramètre
 *                 et étant compatibles avec le second comportement passé en paramètre.
 *
 *** Entree : la carte (tilemap), le comportement souhaité (behavior), le comportement de compatibilité (behaviorNear).
 *** Sortie : void
*/
void erodeNearGround(TileMap* tilemap, TileBehavior behavior, TileBehavior behaviorNear) {
	
	std::vector<int> nears = (tilemap->getTileSet())->getGroundsByBehavior(behaviorNear);
	std::vector<int> nearCompatibles;
	
	for(int k(0) ; k < (tilemap->getTileSet())->getGroundCount() ; ++k) {
		bool add = true;
		for(int l(0) ; l < nears.size() ; ++l) {
			if(k == nears[l]) {
				add = false;
			}
		}
		if(add) {
			add = false;
			for(int l(0) ; l < nears.size() ; ++l) {
				if(tilemap->areCompatibleGrounds(k, nears[l]) == 1) {
					add = true;
				}
			}
			if(add) {
				nearCompatibles.push_back(k);
			}
		}
	}
	
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
				
				std::vector<int> GROUND_types;
				
				if(contains(nearCompatibles, l_ground->getType())) {
					
					for(int k(0) ; k < 4 ; ++k) {
						
						l_ground = NULL;
						
						if(k == 0 && i > 0 && rand()%ALEATOIRE == 0) {
							l_ground = tilemap->getGround(sf::Vector2i(i - 1, j));
						}
						else if(k == 1 && j > 0 && rand()%ALEATOIRE == 0) {
							l_ground = tilemap->getGround(sf::Vector2i(i, j - 1));
						}
						else if(k == 2 && i < width-1 && rand()%ALEATOIRE == 0) {
							l_ground = tilemap->getGround(sf::Vector2i(i + 1, j));
						}
						else if(k == 3 && j < height-1 && rand()%ALEATOIRE == 0) {
							l_ground = tilemap->getGround(sf::Vector2i(i, j + 1));
						}
							
						if(l_ground != NULL && l_ground->getBehavior() == behavior) {
							
							if(!contains(nearCompatibles, l_ground->getType())) {
								GROUND_types.push_back(l_ground->getType());
							}
						}
					}
					
					if(GROUND_types.size() != 0 && rand()%ALEATOIRE == 0) {
						positions.push_back(sf::Vector2i(i, j));
						types.push_back(GROUND_types[rand()%GROUND_types.size()]);
					}
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
					
				for(int k(0) ; k < 4 ; ++k) {
					
					if(k == 0 && i > 0 && rand()%ALEATOIRE == 0) {
						l_element = tilemap->getElement(sf::Vector2i(i - 1, j));
					}
					else if(k == 1 && j > 0 && rand()%ALEATOIRE == 0) {
						l_element = tilemap->getElement(sf::Vector2i(i, j - 1));
					}
					else if(k == 2 && i < width-1 && rand()%ALEATOIRE == 0) {
						l_element = tilemap->getElement(sf::Vector2i(i + 1, j));
					}
					else if(k == 3 && j < height-1 && rand()%ALEATOIRE == 0) {
						l_element = tilemap->getElement(sf::Vector2i(i, j + 1));
					}
					
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

void dilateNearFluids(TileMap* tilemap) {
	
	dilateNearGround(tilemap, DEFAULT, FLUID);
	
}

void erodeNearFluids(TileMap* tilemap) {
	
	erodeNearGround(tilemap, DEFAULT, FLUID);
	
}

void dilateNearCliffs(TileMap* tilemap) {
	
	dilateNearGround(tilemap, DEFAULT, CLIFF);
	
}

void erodeNearCliffs(TileMap* tilemap) {
	
	erodeNearGround(tilemap, DEFAULT, CLIFF);
	
}

void dilateForests(TileMap* tilemap) {
	
	dilateElement(tilemap, FOREST);
	
}

void erodeForests(TileMap* tilemap) {
	
	erodeElement(tilemap, FOREST);
	
}

/*
 *** Description : cette fonction ajoute aléatoirement des éléments sur la carte, des rochers près des falaises ou d'autres rochers
 *                 et de la végétation autour des zones d'eau.
 *
 *** Entree : la carte (tilemap).
 *** Sortie : void
*/
void spawnRessources(TileMap* tilemap) {
	
	int elementCount = (tilemap->getTileSet())->getElementCount();
	std::vector<int> stoneElements;
	std::vector<int> woodElements;
	
	srand(time(NULL));
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	Element* l_element;
	int GROUND_type = ((tilemap->getTileSet())->getGroundsByBehavior(DEFAULT))[0]; 
	
	for(int k(0) ; k < elementCount ; ++k) {
		
		l_element = (tilemap->getTileSet())->getElement(k, GROUND_type);
		
		if(l_element != NULL) {
			
			if(l_element->containRessource(STONE)) {
				stoneElements.push_back(k);
			}
			if(l_element->containRessource(WOOD)) {
				woodElements.push_back(k);
			}
		}
	}
	
	Ground* l_ground;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			if(rand()%ALEATOIRE == 0) {
				
				l_element = tilemap->getElement(sf::Vector2i(i, j));
				
				if(l_element == NULL && rand()%ALEATOIRE == 0) {
					
					bool addStone = false, addWood = false;
					
					for(int k(0) ; k < 4 ; ++k) {
						
						l_ground = NULL;
						
						if(k == 0 && i > 0) {
							l_ground = tilemap->getGround(sf::Vector2i(i - 1, j));
							l_element = tilemap->getElement(sf::Vector2i(i - 1, j));
						}
						else if(k == 1 && j > 0) {
							l_ground = tilemap->getGround(sf::Vector2i(i, j - 1));
							l_element = tilemap->getElement(sf::Vector2i(i, j - 1));
						}
						else if(k == 2 && i < width - 1) {
							l_ground = tilemap->getGround(sf::Vector2i(i + 1, j));
							l_element = tilemap->getElement(sf::Vector2i(i + 1, j));
						}
						else if(k == 3 && j < height - 1) {
							l_ground = tilemap->getGround(sf::Vector2i(i, j + 1));
							l_element = tilemap->getElement(sf::Vector2i(i, j + 1));
						}
					
						if(l_ground != NULL) {
							if(l_ground->getBehavior() == CLIFF) {
								addStone = true;
							}
							if(l_ground->getBehavior() == FLUID) {
								addWood = true;
							}
						}
						if(l_element != NULL) {
							if(rand()%ALEATOIRE == 0 && contains(stoneElements, l_element->getType())) {
								addStone = true;
							}
						}
					}
					
					if(addWood && woodElements.size() > 0) {
						tilemap->addElement(woodElements[rand()%woodElements.size()], sf::Vector2i(i, j));
					}
					else if(addStone && stoneElements.size() > 0) {
						tilemap->addElement(stoneElements[rand()%stoneElements.size()], sf::Vector2i(i, j));
					}
					else {
						GROUND_type = rand()%elementCount;
						if(rand()%ALEATOIRE == 0 && !contains(stoneElements, GROUND_type)) {
							tilemap->addElement(GROUND_type, sf::Vector2i(i, j));
						}
					}
				}
			}
		}
	}
	
}

void burnRessources(TileMap* tilemap) {
	
	srand(time(NULL));
	
	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;
	
	Element* l_element;
	
	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {
			
			if(rand()%ALEATOIRE == 0) {
				
				l_element = tilemap->getElement(sf::Vector2i(i, j));
				
				if(l_element != NULL && rand()%ALEATOIRE == 0) {
					tilemap->burnElement(sf::Vector2i(i, j));
				}
			}
		}
	}
	
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
