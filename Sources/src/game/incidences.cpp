#include "incidences.hpp"

#include "entity/entity.hpp"

//--------------------------------------------------------------------------------------------------------------------------

/*
 *** Description : Fonction du cycle jour nuit, applique toutes les incidences de la journée.
 *
 *** Entree : la carte (tilemap).
 *** Sortie : void
*/
void doIncidences(TileMap* tilemap, Weather* weather, sf::Vector2i posHome,std::vector< Entity * > entityList) {

    /**


        -1 : dilateNearFluids   4%
        -2 : erodeNearCliff     8%
        -3 : dilateFluids + dilateForest    16%
        -4 : spawnResource|caillou          32%
        -5 : dilateFluid        56%

        -1/0/1 : spawnRessources => 40%

        +1 : erodeNearFluid
        +2 :
        +3 : dilateNearCliff
        +4 : erodeFluid + burn  5%  / vitesse
        +5 :                    20% / vitesse

    **/

	//Incidences sur le territoire

	weather->updateWeather();
	int nb=weather->getWeatherGrade();
	if(nb==-5)
    {
        dilateFluids(tilemap);
    }
    if(nb<=-4)
    {
        spawnOnlyStone(tilemap);
    }
    if(nb<=-3)
    {
        dilateFluids(tilemap);
        dilateForests(tilemap);
    }
    if(nb<=-2)
    {
        erodeNearCliffs(tilemap);
    }
    if(nb<=-1)
    {
        dilateNearFluids(tilemap);
    }
    if(nb>=-1 && nb<=1)
    {
         //srand (time(NULL));
         if(rand()%100<=40)
         {
             spawnRessources(tilemap);
         }
    }
    if(nb>=1)
    {
        erodeNearFluids(tilemap);
    }
    if(nb>=3)
    {
        dilateNearCliffs(tilemap);
    }
    if(nb>=4)
    {
        erodeFluids(tilemap);
        burnRessources(tilemap);
    }

    //Incidences sur les entités

    //Meteo
    if(nb!=0)
    {
        weather->impactsOnEntities(entityList,nb);
    }


    tilemap->freePlace(posHome);

}

//--------------------------------------------------------------------------------------------------------------------------

/*
 *** Description : cette fonction prévoit le coût de la fonction spredGround.
 *
 *** Entree : la carte (tilemap), le type souhaité (type), la position (position), les positions déjà vues (calledPositions).
 *** Sortie : le coût de la fonction spreadGround si elle est appelée.
*/
int abstractSpreadGround(TileMap* tilemap, int type, sf::Vector2i position, std::vector<sf::Vector2i>& calledPositions) {

	int l_cost = 0;
	int i = position.x, j = position.y;

	Ground* l_ground = tilemap->getGround(position);

	if(l_ground != NULL) {

		// Changement du sol courant
		int oldType = l_ground->getType();
		if(type != oldType) {

			l_cost += (tilemap->getTileSet())->getGroundCost(type);
			sf::Vector2i l_position;
			
			for(int k(0) ; k < 4 ; ++k) {
				if(k == 0) {
					l_position.x = i - 1;
					l_position.y = j;
				}
				else if(k == 1) {
					l_position.x = i;
					l_position.y = j - 1;
				}
				else if(k == 2) {
					l_position.x = i + 1;
					l_position.y = j;
				}
				else if(k == 3) {
					l_position.x = i;
					l_position.y = j + 1;
				}
				
				// Propagation
				l_ground = tilemap->getGround(l_position);
				if(l_ground != NULL && !contains(calledPositions, l_position) && tilemap->areCompatibleGrounds(type, l_ground->getType()) == 0) {
					l_cost += abstractSpreadGround(tilemap, oldType, l_position, calledPositions);
				}
			}
		}
	}

	return l_cost;

}

void spreadGround(TileMap* tilemap, int type, sf::Vector2i position, bool fixCliffs) {

	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;

	spreadGroundRec(tilemap, type, position, sf::Vector2i(width, height), fixCliffs);

}

/*
 *** Description : cette fonction met à jour les cases environnantes, et si besoin harmonise les types compatibles.
 *
 *** Entree : la carte (tilemap), le type souhaité (type), la position (position), fixer ou non les falaises (fixCliffs).
 *** Sortie : void
*/
void spreadGroundRec(TileMap* tilemap, int type, sf::Vector2i position, sf::Vector2i callPosition, bool fixCliffs) {

	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;

	int i = position.x, j = position.y;

	Ground* l_ground = tilemap->getGround(position);

	if(l_ground != NULL) {
std::cout<<i+j*width<<" "<<l_ground->getName()<<std::endl;
		// Changement du sol courant
		int oldType = l_ground->getType();
		if(type != oldType) {

			if(fixCliffs && l_ground->getBehavior() == CLIFF) {
				oldType = type;
			}
			else {
				tilemap->changeGround(type, position);
			}

			// Propagation
			if(i > 0) {
				sf::Vector2i tmp(i - 1, j);
				if(tmp != callPosition && tilemap->areCompatibleGrounds(position, tmp) == 0) {
					spreadGroundRec(tilemap, oldType, tmp, position, fixCliffs);
				}
			}
			if(j > 0) {
				sf::Vector2i tmp(i, j - 1);
				if(tmp != callPosition && tilemap->areCompatibleGrounds(position, tmp) == 0) {
					spreadGroundRec(tilemap, oldType, tmp, position, fixCliffs);
				}
			}
			if(i < width-1) {
				sf::Vector2i tmp(i + 1, j);
				if(tmp != callPosition && tilemap->areCompatibleGrounds(position, tmp) == 0) {
					spreadGroundRec(tilemap, oldType, tmp, position, fixCliffs);
				}
			}
			if(j < height-1) {
				sf::Vector2i tmp(i, j + 1);
				if(tmp != callPosition && tilemap->areCompatibleGrounds(position, tmp) == 0) {
					spreadGroundRec(tilemap, oldType, tmp, position, fixCliffs);
				}
			}

			// Mise à jour des bordures
			tilemap->updateBorders(sf::Vector2i(i - 1, j));
			tilemap->updateBorders(sf::Vector2i(i, j - 1));
			tilemap->updateBorders(sf::Vector2i(i + 1, j));
			tilemap->updateBorders(sf::Vector2i(i, j + 1));
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

	for(unsigned int p(0) ; p < positions.size() ; ++p) {
		spreadGround(tilemap, types[p], positions[p], true);
	}

}

/*
 *** Description : cette fonction érode les zones ayant le comportement passé en paramètre.
 *
 *** Entree : la carte (tilemap), le comportement souhaité (behavior).
 *** Sortie : void
*/
void erodeGround(TileMap* tilemap, TileBehavior behavior) {

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

	for(unsigned int p(0) ; p < positions.size() ; ++p) {
		spreadGround(tilemap, types[p], positions[p], true);
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
		for(unsigned int l(0) ; l < nears.size() ; ++l) {
			if(k == nears[l]) {
				add = false;
			}
		}
		if(add) {
			add = false;
			for(unsigned int l(0) ; l < nears.size() ; ++l) {
				if(tilemap->areCompatibleGrounds(k, nears[l]) == 1) {
					add = true;
				}
			}
			if(add) {
				nearCompatibles.push_back(k);
			}
		}
	}

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

	for(unsigned int p(0) ; p < positions.size() ; ++p) {
		spreadGround(tilemap, types[p], positions[p], true);
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
		for(unsigned int l(0) ; l < nears.size() ; ++l) {
			if(k == nears[l]) {
				add = false;
			}
		}
		if(add) {
			add = false;
			for(unsigned int l(0) ; l < nears.size() ; ++l) {
				if(tilemap->areCompatibleGrounds(k, nears[l]) == 1) {
					add = true;
				}
			}
			if(add) {
				nearCompatibles.push_back(k);
			}
		}
	}

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

	for(unsigned int p(0) ; p < positions.size() ; ++p) {
		spreadGround(tilemap, types[p], positions[p], true);
	}

}

/*
 *** Description : cette fonction dilate les zones d'éléments ayant le comportement passé en paramètre.
 *
 *** Entree : la carte (tilemap), le comportement souhaité (behavior).
 *** Sortie : void
*/
void dilateElement(TileMap* tilemap, TileBehavior behavior) {

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

	for(unsigned int p(0) ; p < positions.size() ; ++p) {
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

	for(unsigned int p(0) ; p < positions.size() ; ++p) {
		tilemap->removeElement(positions[p]);
	}

}

int spawnEntities(EntityType type, std::vector< Entity * > list) {

	int result = 0;

	for(unsigned int i(0) ; i < list.size() ; ++i) {
		if(list[i]->getType() == type && list[i]->getHealth() != DEAD) {

			result++;

			if(rand()%100 < 10) {
				result++;
			}
		}
	}

	return result;

}

int killEntities(EntityType type, std::vector< Entity * > list) {

	int result = 0;

	for(unsigned int i(0) ; i < list.size() ; ++i) {
		if(list[i]->getType() == type) {
			int sick = list[i]->isSick()?20:0;
			if(list[i]->getHealth() == WEAK && rand()%100 < 10 + sick) { // 10% de risque de mourir
				list[i]->setHealth(DEAD);
				result++;
			}
			else if(list[i]->getHealth() == VERY_WEAK && rand()%100 < 30 + sick) { // 30% de risque de mourir
				list[i]->setHealth(DEAD);
				result++;
			}
		}
	}

	return result;

}

//--------------------------------------------------------------------------------------------------------------------------

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

void spawnOnlyStone(TileMap* tilemap) {

	int elementCount = (tilemap->getTileSet())->getElementCount();
	std::vector<int> stoneElements;

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
		}
	}

	Ground* l_ground;

	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {

			if(rand()%ALEATOIRE == 0) {

				l_element = tilemap->getElement(sf::Vector2i(i, j));

				if(l_element == NULL && rand()%ALEATOIRE == 0) {

					bool addStone = false;

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
						}
						if(l_element != NULL) {
							if(rand()%ALEATOIRE == 0 && contains(stoneElements, l_element->getType())) {
								addStone = true;
							}
						}
					}

					if(addStone && stoneElements.size() > 0) {
						tilemap->addElement(stoneElements[rand()%stoneElements.size()], sf::Vector2i(i, j));
					}
				}
			}
		}
	}

}

void burnRessources(TileMap* tilemap) {

	int elementCount = (tilemap->getTileSet())->getElementCount();
	std::vector<int> stoneElements;
	std::vector<int> woodElements;

	Element* l_element;
	int GROUND_type = ((tilemap->getTileSet())->getGroundsByBehavior(DEFAULT))[0];

	for(int k(0) ; k < elementCount ; ++k) {

		l_element = (tilemap->getTileSet())->getElement(k, GROUND_type);

		if(l_element != NULL) {

			if(l_element->containRessource(STONE)) {
				stoneElements.push_back(k);
			}
		}
	}

	int width = tilemap->getDimensions().x;
	int height = tilemap->getDimensions().y;

	for(int i(0) ; i < width ; ++i) {
		for(int j(0) ; j < height ; ++j) {

			if(rand()%ALEATOIRE == 0) {

				l_element = tilemap->getElement(sf::Vector2i(i, j));

				if(l_element != NULL && !contains(stoneElements, l_element->getType()) && rand()%ALEATOIRE == 0) {
					tilemap->burnElement(sf::Vector2i(i, j));
				}
			}
		}
	}

}

int allyCitizenBirth(Game* game) {

	return spawnEntities(ALLY_CITIZEN, game->getEntities()) + spawnEntities(HUNTER, game->getEntities());

}

int enemyCitizenBirth(Game* game) {

	return spawnEntities(ENEMY_CITIZEN, game->getEntities());

}

int wildAnimalBirth(Game* game) {

	return spawnEntities(WILD_ANIMAL, game->getEntities());

}

int peacefulAnimalBirth(Game* game) {

	return spawnEntities(PEACEFUL_ANIMAL, game->getEntities());

}

int allyCitizenDeath(Game* game) {

	return killEntities(ALLY_CITIZEN, game->getEntities()) + killEntities(HUNTER, game->getEntities());

}

int enemyCitizenDeath(Game* game) {

	return killEntities(ENEMY_CITIZEN, game->getEntities());

}

int wildAnimalDeath(Game* game) {

	return killEntities(WILD_ANIMAL, game->getEntities());

}

int peacefulAnimalDeath(Game* game) {

	return killEntities(PEACEFUL_ANIMAL, game->getEntities());

}

void updateRessources(Game* game) {

	std::vector< Entity * > list = game->getEntities();
	int number = 0;

	for(unsigned int i(0) ; i < list.size() ; ++i) {
		if(list[i]->getType() == ALLY_CITIZEN) {
			number++;
		}
	}

	game->setPI(game->getPI() + 10 * number);//BONUS PI
	game->addRessource(FOOD, -(number*3));
	if(game->getQtyFood() < 0) {
		// rendre malade chaque péon pas nourri ?
		game->addRessource(FOOD, -game->getQtyFood());
	}
	// utiliser aussi du bois et de la pierre ? genre pour faire du feu dans sa cahute...

}
