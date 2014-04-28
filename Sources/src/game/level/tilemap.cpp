#include "tilemap.hpp"

#include <stdlib.h>
#include <cmath>
#include <iostream>

#include "pathfinding.hpp"
#include "../../engine/foo.hpp"
#include "../incidences.hpp"

#define ELEMENT_PROPORTION 10
#define ELEMENT_AREASIZE 5

TileMap::TileMap(TileSet tileset, sf::Vector2u dimensions) {

	m_tileset = tileset;
	m_dimensions = dimensions;

}

TileMap::~TileMap() {

}

TileSet* TileMap::getTileSet() {

	return &m_tileset;

}

void TileMap::setTileSet(TileSet tileset) {

	m_tileset = tileset;

}

sf::Vector2u TileMap::getDimensions() const {

	return m_dimensions;

}

void TileMap::setDimensions(sf::Vector2u dimensions) {

	m_dimensions = dimensions;

}

int TileMap::getX(sf::Vector2f position) const {

	return (int)(position.x/m_tileset.getTileSize().x);

}

int TileMap::getY(sf::Vector2f position) const {

	return (int)(position.y/m_tileset.getTileSize().y);

}

sf::Vector2i TileMap::getXY(sf::Vector2f position) const {

	return sf::Vector2i(getX(position), getY(position));

}

sf::Vector2f TileMap::getAbs(sf::Vector2i position) const
{
    return sf::Vector2f(position.x * m_tileset.getTileSize().x + m_tileset.getTileSize().x/2 , position.y * m_tileset.getTileSize().y + m_tileset.getTileSize().y/2);
}

int TileMap::getId(sf::Vector2i position) const {

	if(position.x < (int)m_dimensions.x && position.x >= 0 && position.y < (int)m_dimensions.y && position.y >= 0) {
		return position.x + position.y * m_dimensions.x;
	}
	else {
		return -1;
	}

}

int TileMap::getId(sf::Vector2f position) const {

	return getId(getXY(position));

}

Ground* TileMap::getGround(sf::Vector2i position) const {

	int id = getId(position);
	if(id != -1) {
		return m_grounds[id];
	}
	else {
		return NULL;
	}

}

Element* TileMap::getElement(sf::Vector2i position) const {

	int id = getId(position);
	if(id != -1) {
		return m_elements[id];
	}
	else {
		return NULL;
	}

}

int TileMap::getGroundCost(int type) const {
	
	return m_tileset.getGroundCost(type);
	
}

int TileMap::getElementCost(int type) const {
	
	return m_tileset.getElementCost(type);
	
}

Harvestable * TileMap::getHarvestable(sf::Vector2i position) const {

	int id = getId(position);
	if(id != -1 && m_elements[id] && m_elements[id]->isHarvestable()) {
		return m_elements[id];
	}
	else {
		return NULL;
	}

}

/*
 *** Description : cette fonction teste la compatibilité entre deux sols.
 *
 *** Entree : deux positions de sol
 *** Sortie : -1 si un sol est NULL, 1 si compatibles, 0 sinon.
*/
int TileMap::areCompatibleGrounds(sf::Vector2i position_1, sf::Vector2i position_2) {

	Ground* l_ground_1 = this->getGround(position_1);
	Ground* l_ground_2 = this->getGround(position_2);

	if(l_ground_1 == NULL || l_ground_2 == NULL) {
		return -1;
	}
	else {
		return (l_ground_1->hasBorderWith(l_ground_2->getType()) ||
				l_ground_2->hasBorderWith(l_ground_1->getType()) ||
				l_ground_1->getType() == l_ground_2->getType())?1:0;
	}

}

/*
 *** Description : cette fonction teste la compatibilité entre deux sols.
 *
 *** Entree : deux positions de sol
 *** Sortie : -1 si un sol est NULL, 1 si compatibles, 0 sinon.
*/
int TileMap::areCompatibleGrounds(int type_1, int type_2) {

	bool tileBorders[4] = {false, false, false, false};
	Ground* l_ground_1 = m_tileset.getGround(type_1, tileBorders);
	Ground* l_ground_2 = m_tileset.getGround(type_2, tileBorders);

	if(l_ground_1 == NULL || l_ground_2 == NULL) {
		return -1;
	}
	else {
		return (l_ground_1->hasBorderWith(l_ground_2->getType()) ||
				l_ground_2->hasBorderWith(l_ground_1->getType()) ||
				l_ground_1->getType() == l_ground_2->getType())?1:0;
	}

}

void TileMap::changeGround(int type, sf::Vector2i position) {

	int i = position.x;
	int j = position.y;
	sf::Vector2u tileSize = m_tileset.getTileSize();
	int width = m_dimensions.x, height = m_dimensions.y;

	if(i >= 0 && i < width && j >= 0 && j < height) {

		//===== GROUND =====

		bool GROUND_tileBorders[4] = {false,false,false,false};
		Ground* l_ground = m_tileset.getGround(type, GROUND_tileBorders);

		if(l_ground != NULL) {

			GROUND_tileBorders[0] = (i > 0 && l_ground->hasBorderWith(m_grounds[i - 1 + j * width]->getType()));
			GROUND_tileBorders[1] = (j < height-1 && l_ground->hasBorderWith(m_grounds[i + (j + 1) * width]->getType()));
			GROUND_tileBorders[2] = (j > 0 && l_ground->hasBorderWith(m_grounds[i + (j - 1) * width]->getType()));
			GROUND_tileBorders[3] = (i < width-1 && l_ground->hasBorderWith(m_grounds[i + 1 + j * width]->getType()));

			l_ground = m_tileset.getGround(type, GROUND_tileBorders);

			if(l_ground != NULL) {

				m_grounds[i + j * width] = l_ground;
				sf::Vertex* quadGround = &m_VertexGrounds[(i + j * width) * 4];

				quadGround[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quadGround[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quadGround[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quadGround[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				for(int k(0) ; k < 4 ; ++k) {
					quadGround[k].texCoords = (l_ground->getQuad())[k].texCoords;
				}
			}
			else {
				std::cout << "Une erreur est survenue lors du changement d'un sol. (1)" << std::endl;
			}
		}
		else {
			std::cout << "Une erreur est survenue lors du changement d'un sol. (2)" << std::endl;
		}

		//===== ELEMENT =====

		if(m_elements[i + j * width] != NULL) {
			addElement(m_elements[i + j * width]->getType(), position);
		}
	}

}

void TileMap::updateBorders(sf::Vector2i position) {

	Ground* l_ground = getGround(position);

	if(l_ground != NULL) {
		changeGround(l_ground->getType(), position);
	}

}

void TileMap::addElement(int type, sf::Vector2i position) {

	unsigned int i = position.x;
	unsigned int j = position.y;

	if(i >= 0 && i < m_dimensions.x && j >= 0 && j < m_dimensions.y) {

		sf::Vector2u tileSize = m_tileset.getTileSize();
		int width = m_dimensions.x;

		//===== ELEMENT =====

		int GROUND_type = m_grounds[i + j * width]->getType();
		Element* l_element = m_tileset.getElement(type, GROUND_type);

		if(l_element != NULL) {

			m_elements[i + j * width] = l_element;
			sf::Vertex* quadElementDown = &m_VertexElementsDown[(i + j * width) * 4];
			sf::Vertex* quadElementUp = &m_VertexElementsUp[(i + j * width) * 4];

			quadElementDown[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quadElementDown[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quadElementDown[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quadElementDown[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			if(j > 0) {
				quadElementUp[0].position = sf::Vector2f(i * tileSize.x, (j-1) * tileSize.y);
				quadElementUp[1].position = sf::Vector2f((i + 1) * tileSize.x, (j-1) * tileSize.y);
				quadElementUp[2].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quadElementUp[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			}

			for(int k(0) ; k < 4 ; ++k) {
				quadElementDown[k].texCoords = (l_element->getQuadDown())[k].texCoords;
				quadElementUp[k].texCoords = (l_element->getQuadUp())[k].texCoords;
			}
		}
		else {
			removeElement(position);
	//		std::cout << "Une erreur est survenue lors de l'ajout d'un element." << std::endl;
		}
	}

}

void TileMap::removeElement(sf::Vector2i position) {

	unsigned int i = position.x;
	unsigned int j = position.y;

	if(i >= 0 && i < m_dimensions.x && j >= 0 && j < m_dimensions.y) {

		int width = m_dimensions.x;

		m_elements[i + j * width] = NULL;

		sf::Vertex* quadElementDown = &m_VertexElementsDown[(i + j * width) * 4];
		sf::Vertex* quadElementUp = &m_VertexElementsUp[(i + j * width) * 4];

		for(int k(0) ; k < 4 ; ++k) {
			quadElementDown[k].position = sf::Vector2f(0,0);
			quadElementUp[k].position = sf::Vector2f(0,0);
		}
	}
}

void TileMap::burnElement(sf::Vector2i position) {

	removeElement(position);

	unsigned int i = position.x;
	unsigned int j = position.y;

	if(i >= 0 && i < m_dimensions.x && j >= 0 && j < m_dimensions.y) {

		sf::Vector2u tileSize = m_tileset.getTileSize();
		sf::Vector2u tilesetSize = (m_tileset.getTileset())->getSize();
		sf::Vector2u ashes = m_tileset.getAshes();
		int width = m_dimensions.x;

		//===== ASHES =====

		sf::Vertex* quadElementDown = &m_VertexElementsDown[(i + j * width) * 4];
		sf::Vertex* quadElementUp = &m_VertexElementsUp[(i + j * width) * 4];

		quadElementDown[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
		quadElementDown[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
		quadElementDown[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
		quadElementDown[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

		if(j > 0) {
			quadElementUp[0].position = sf::Vector2f(i * tileSize.x, (j-1) * tileSize.y);
			quadElementUp[1].position = sf::Vector2f((i + 1) * tileSize.x, (j-1) * tileSize.y);
			quadElementUp[2].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quadElementUp[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
		}

		quadElementDown[0].texCoords = sf::Vector2f(ashes.x, ashes.y);
		quadElementDown[1].texCoords = sf::Vector2f(ashes.x + tileSize.x, ashes.y);
		quadElementDown[2].texCoords = sf::Vector2f(ashes.x + tileSize.x, ashes.y + tileSize.y);
		quadElementDown[3].texCoords = sf::Vector2f(ashes.x, ashes.y + tileSize.y);

		quadElementUp[0].texCoords = sf::Vector2f(tilesetSize.x - tileSize.x, tilesetSize.y - tileSize.y);
		quadElementUp[1].texCoords = sf::Vector2f(tilesetSize.x, tilesetSize.y - tileSize.y);
		quadElementUp[2].texCoords = sf::Vector2f(tilesetSize.x, tilesetSize.y);
		quadElementUp[3].texCoords = sf::Vector2f(tilesetSize.x - tileSize.x, tilesetSize.y);
	}
}
/*
int bestLinkType(std::vector<int> possibleTypes, int startType, int goalType) {
	
	std::vector<int> scores;
	
	for(unsigned int i(0) ; i < possibleTypes.size() ; ++i) {
		scores.push_back(bestLinkTypeRec(possibleTypes[i], startType, goalType));
	}
	
	int min = 2147483647;
	int result = -1;
	
	for(unsigned int i(0) ; i < possibleTypes.size() ; ++i) {
		if(scores[i] < min) {
			min = scores[i];
			result = possibleTypes[i];
		}
	}
	
}
*/
/*
 *** Description : cette fonction propage le sol posé par userSetGround.
 *
 *** Entree : le type de sol (type), la position à laquelle le poser (position).
 *** Sortie : void.
*/
void TileMap::userSetGroundRec(int type, sf::Vector2i position) {
	
	int i = position.x;
	int j = position.y;
	
	std::vector<int> groundCompatibles;
	
	for(int k(0) ; k < (this->getTileSet())->getGroundCount() ; ++k) {
		if(this->areCompatibleGrounds(k, type)) {
			groundCompatibles.push_back(k);
		}
	}
	if(groundCompatibles.size() == 0) {
		std::cout << "Erreur : aucun sol n'est compatible avec le sol posé." << std::endl;
	}
	else {
		changeGround(type, position);
		
		Ground* l_ground;
		int GROUND_type;
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
			
			l_ground = getGround(l_position);
			if(l_ground != NULL && !areCompatibleGrounds(l_ground->getType(), type)) {
				
				Ground* l_ground_tmp;
				sf::Vector2i l_position_tmp;
				int score;
				std::vector<int> compatibilityScores;
				int compatibilityMax = -1;
				
				for(unsigned int l(0) ; l < groundCompatibles.size() ; ++l) {
					
					score = 0;
					
					for(int m(0) ; m < 4 ; ++m) {
						if(m == 0) {
							l_position_tmp.x = l_position.x - 1;
							l_position_tmp.y = l_position.y;
						}
						else if(m == 1) {
							l_position_tmp.x = l_position.x;
							l_position_tmp.y = l_position.y - 1;
						}
						else if(m == 2) {
							l_position_tmp.x = l_position.x + 1;
							l_position_tmp.y = l_position.y;
						}
						else if(m == 3) {
							l_position_tmp.x = l_position.x;
							l_position_tmp.y = l_position.y + 1;
						}
						
						l_ground_tmp = getGround(l_position_tmp);
						if(l_ground_tmp != NULL && areCompatibleGrounds(groundCompatibles[l], l_ground_tmp->getType())) {
							score++;
						}
					}
					
					compatibilityScores.push_back(score);
				}
				
				for(unsigned int l(0) ; l < compatibilityScores.size() ; ++l) {
					if(compatibilityScores[l] > compatibilityMax) {
						compatibilityMax = compatibilityScores[l];
					}
				}
				if(compatibilityMax == -1) {
					std::cout<<"Erreur : incompatibilité de sols (userSetGround)"<<std::endl;
					GROUND_type = type;
				}
				
				std::vector<int> possibleTypes;
				for(unsigned int l(0) ; l < compatibilityScores.size() ; ++l) {
					if(compatibilityScores[l] == compatibilityMax) {
						possibleTypes.push_back(groundCompatibles[l]);
					}
				}
				
				//RECODE : choisir le meilleur type
				GROUND_type = possibleTypes[rand()%possibleTypes.size()];
				userSetGroundRec(GROUND_type, l_position);
			}
			
			updateBorders(l_position);
		}
		
		updateBorders(position);
	}
	
}

/*
 *** Description : cette fonction pose un sol à la position choisie par l'utilisateur et récpercute sur les sols alentours.
 *
 *** Entree : le type de sol (type), la position à laquelle le poser (position).
 *** Sortie : void.
*/
void TileMap::userSetGround(int type, sf::Vector2i position) {
	
	Ground* l_ground = getGround(position);
	
	if(areCompatibleGrounds(l_ground->getType(), type)) {
		spreadGround(this, type, position, false);
	}
	else {
		userSetGroundRec(type, position);
		userSetGroundRec(type, position); //à enlever après meilleur type
		
		updateBorders(position);
		updateBorders(sf::Vector2i(position.x - 1, position.y));
		updateBorders(sf::Vector2i(position.x, position.y - 1));
		updateBorders(sf::Vector2i(position.x + 1, position.y));
		updateBorders(sf::Vector2i(position.x, position.y + 1));
	}
	
}

/*
 *** Description : cette fonction libère une zone de cinq cases de diamètre de tout élément ou sol infranchissable.
 *
 *** Entree : le centre de la zone (position).
 *** Sortie : void.
*/
void TileMap::freePlace(sf::Vector2i position) {
	int i = position.x;
	int j = position.y;

	// === ELEMENT ===

	removeElement(position);

	removeElement(sf::Vector2i(i - 2, j));
	removeElement(sf::Vector2i(i - 1, j));
	removeElement(sf::Vector2i(i + 1, j));
	removeElement(sf::Vector2i(i + 2, j));

	removeElement(sf::Vector2i(i, j - 2));
	removeElement(sf::Vector2i(i, j - 1));
	removeElement(sf::Vector2i(i, j + 1));
	removeElement(sf::Vector2i(i, j + 2));

	removeElement(sf::Vector2i(i - 1, j - 1));
	removeElement(sf::Vector2i(i - 1, j + 1));
	removeElement(sf::Vector2i(i + 1, j + 1));
	removeElement(sf::Vector2i(i + 1, j - 1));
	
	
	// === GROUND ===

	std::vector<int> defaults = m_tileset.getGroundsByBehavior(DEFAULT);

	Ground * l_ground_1, * l_ground_2, * l_ground_3, * l_ground_4;
	std::vector<int> GROUND_types;
	sf::Vector2i l_position = position;

	for(int l(0) ; l < 13 ; ++l) {
		switch(l) {

			case 0 :
				l_position.x = i - 2;
				l_position.y = j;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = NULL;
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;

			case 1 :
				l_position.x = i;
				l_position.y = j - 2;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = NULL;
				break;

			case 2 :
				l_position.x = i + 2;
				l_position.y = j;

				l_ground_1 = NULL;
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;

			case 3 :
				l_position.x = i;
				l_position.y = j + 2;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = NULL;
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;

			case 4 :
				l_position.x = i - 1;
				l_position.y = j + 1;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = NULL;
				l_ground_3 = NULL;
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;

			case 5 :
				l_position.x = i - 1;
				l_position.y = j - 1;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = NULL;
				l_ground_4 = NULL;
				break;

			case 6 :
				l_position.x = i + 1;
				l_position.y = j - 1;

				l_ground_1 = NULL;
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = NULL;
				break;

			case 7 :
				l_position.x = i + 1;
				l_position.y = j + 1;

				l_ground_1 = NULL;
				l_ground_2 = NULL;
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;

			case 8 :
				l_position.x = i - 1;
				l_position.y = j;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = NULL;
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;

			case 9 :
				l_position.x = i;
				l_position.y = j - 1;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = NULL;
				break;

			case 10 :
				l_position.x = i + 1;
				l_position.y = j;

				l_ground_1 = NULL;
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;

			case 11 :
				l_position.x = i;
				l_position.y = j + 1;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = NULL;
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;

			case 12 :
				l_position.x = i;
				l_position.y = j;

				l_ground_1 = getGround(sf::Vector2i(l_position.x - 1, l_position.y));
				l_ground_2 = getGround(sf::Vector2i(l_position.x, l_position.y - 1));
				l_ground_3 = getGround(sf::Vector2i(l_position.x + 1, l_position.y));
				l_ground_4 = getGround(sf::Vector2i(l_position.x, l_position.y + 1));
				break;
		}

		for(unsigned int k(0) ; k < defaults.size() ; ++k) {
			if((l_ground_1 == NULL || areCompatibleGrounds(defaults[k], l_ground_1->getType()))
			&&
			(l_ground_2 == NULL || areCompatibleGrounds(defaults[k], l_ground_2->getType()))
			&&
			(l_ground_3 == NULL || areCompatibleGrounds(defaults[k], l_ground_3->getType()))
			&&
			(l_ground_4 == NULL || areCompatibleGrounds(defaults[k], l_ground_4->getType()))
			){
				GROUND_types.push_back(defaults[k]);
			}
		}

		if(GROUND_types.size() == 0) {
			int t = defaults[rand()%defaults.size()];
			spreadGround(this, t, position, true);
			spreadGround(this, t, sf::Vector2i(position.x - 1, position.y), true);
			spreadGround(this, t, sf::Vector2i(position.x, position.y - 1), true);
			spreadGround(this, t, sf::Vector2i(position.x + 1, position.y), true);
			spreadGround(this, t, sf::Vector2i(position.x, position.y + 1), true);
		}
		else {
			changeGround(GROUND_types[rand()%GROUND_types.size()], l_position);
			GROUND_types.clear();
		}

	}

	// Mise à jour des bordures

	updateBorders(position);

	updateBorders(sf::Vector2i(i - 2, j));
	updateBorders(sf::Vector2i(i - 1, j));
	updateBorders(sf::Vector2i(i + 1, j));
	updateBorders(sf::Vector2i(i + 2, j));

	updateBorders(sf::Vector2i(i, j - 2));
	updateBorders(sf::Vector2i(i, j - 1));
	updateBorders(sf::Vector2i(i, j + 1));
	updateBorders(sf::Vector2i(i, j + 2));

	updateBorders(sf::Vector2i(i - 1, j - 1));
	updateBorders(sf::Vector2i(i - 1, j + 1));
	updateBorders(sf::Vector2i(i + 1, j + 1));
	updateBorders(sf::Vector2i(i + 1, j - 1));

	updateBorders(sf::Vector2i(i - 3, j));
	updateBorders(sf::Vector2i(i + 3, j));
	updateBorders(sf::Vector2i(i, j - 3));
	updateBorders(sf::Vector2i(i, j + 3));

	updateBorders(sf::Vector2i(i - 2, j - 1));
	updateBorders(sf::Vector2i(i - 1, j - 2));
	updateBorders(sf::Vector2i(i + 1, j - 2));
	updateBorders(sf::Vector2i(i + 2, j - 1));

	updateBorders(sf::Vector2i(i - 2, j + 1));
	updateBorders(sf::Vector2i(i - 1, j + 2));
	updateBorders(sf::Vector2i(i + 1, j + 2));
	updateBorders(sf::Vector2i(i + 2, j + 1));
}

/*
 *** Description : cette fonction génère aléatoirement le contenu de la carte.
 *
 *** Entree : void
 *** Sortie : void
*/
void TileMap::generate() {

	int width = m_dimensions.x, height = m_dimensions.y;
	sf::Vector2u tileSize = m_tileset.getTileSize();

	m_grounds.resize(width * height, NULL);
	m_elements.resize(width * height, NULL);

	m_VertexGrounds.setPrimitiveType(sf::Quads);
	m_VertexGrounds.resize(width * height * 4);

	m_VertexElementsDown.setPrimitiveType(sf::Quads);
	m_VertexElementsDown.resize(width * height * 4);

	m_VertexElementsUp.setPrimitiveType(sf::Quads);
	m_VertexElementsUp.resize(width * height * 4);

	for(int j(0) ; j < height ; ++j) {
		for(int i(0) ; i < width ; ++i) {

			//===== GROUND : passe 1 (type) =====

			int GROUND_type = rand()%m_tileset.getGroundCount();
			bool GROUND_tileBorders[4] = {false,false,false,false};

			if(i != 0 || j != 0) {

				std::vector<int> l_borders;

				for(int k(0) ; k < m_tileset.getGroundCount() ; ++k) {
					Ground* l_ground_tmp = m_tileset.getGround(k, GROUND_tileBorders);
					if(l_ground_tmp != NULL) {
						bool add = true;
						if(i > 0) {
							if(!(m_grounds[i - 1 + j * width]->getType() == k
								|| m_grounds[i - 1 + j * width]->hasBorderWith(k)
								|| l_ground_tmp->hasBorderWith(m_grounds[i - 1 + j * width]->getType()))) {
								add = false;
							}
						}
						if(j > 0) {
							if(!(m_grounds[i + (j - 1) * width]->getType() == k
								|| m_grounds[i + (j - 1) * width]->hasBorderWith(k)
								|| l_ground_tmp->hasBorderWith(m_grounds[i + (j - 1) * width]->getType()))) {
								add = false;
							}
						}
						if(add) {
							if(i > 0 && m_grounds[i - 1 + j * width]->getType() == k && m_grounds[i - 1 + j * width]->getBehavior() != FLUID) {
								l_borders.push_back(k);
							}
							if(j > 0 && m_grounds[i + (j - 1) * width]->getType() == k && m_grounds[i + (j - 1) * width]->getBehavior() != FLUID) {
								l_borders.push_back(k);
							}
							l_borders.push_back(k);
						}
					}
					else {
						std::cout << "Une erreur est survenue lors de la génération d'un sol. (1)" << std::endl;
					}
				}

				GROUND_type = l_borders[rand()%l_borders.size()];

			}

			Ground* l_ground = m_tileset.getGround(GROUND_type, GROUND_tileBorders);

			if(l_ground != NULL) {

				m_grounds[i + j * width] = l_ground;

				sf::Vertex* quadGround = &m_VertexGrounds[(i + j * width) * 4];

				quadGround[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quadGround[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quadGround[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quadGround[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				for(int k(0) ; k < 4 ; ++k) {
					quadGround[k].texCoords = (l_ground->getQuad())[k].texCoords;
				}
			}
			else {
				std::cout << "Une erreur est survenue lors de la génération d'un sol. (2)" << std::endl;
			}

		}
	}

	for(int j(1) ; j < height-1 ; ++j) {
		for(int i(1) ; i < width-1 ; ++i) {

			//===== GROUND : passe 2 (homogénéisation des zones) =====

			Ground* current = m_grounds[i + j * width];
			Ground* round[4] = { m_grounds[i - 1 + j * width], m_grounds[i + (j + 1) * width], m_grounds[i + (j - 1) * width], m_grounds[i + 1 + j * width] };

			if(current->getBehavior() == DEFAULT) {

				if( ( current->hasBorderWith(round[0]->getType())
					&& current->hasBorderWith(round[1]->getType())
					&& current->hasBorderWith(round[2]->getType())
					&& current->hasBorderWith(round[3]->getType())
					) || (
					round[0]->hasBorderWith(current->getType())
					&& round[1]->hasBorderWith(current->getType())
					&& round[2]->hasBorderWith(current->getType())
					&& round[3]->hasBorderWith(current->getType())
					) ) {

					int k(0), random(rand());
					while(k < 4) {

						int GROUND_type = round[(k+random)%4]->getType();
						bool GROUND_tileBorders[4] = {false,false,false,false};

						Ground* l_ground = m_tileset.getGround(GROUND_type, GROUND_tileBorders);

						if(l_ground != NULL) {

							bool change = true;
							for(int l(0) ; l < 4 ; ++l) {
								if(!(round[l]->getType() == GROUND_type || l_ground->hasBorderWith(round[l]->getType()) || round[l]->hasBorderWith(GROUND_type))) {
									change = false;
								}
							}
							if(change) {
								m_grounds[i + j * width] = l_ground;
								k = 4;
							}

						}
						else {
							std::cout << "Une erreur est survenue lors de la génération d'un sol. (3)" << std::endl;
						}

						++k;
					}
				}

			}
			else if(current->getBehavior() == FLUID || current->getBehavior() == CLIFF) {

				int cpt(0);
				for(int k(0) ; k < 4 ; ++k) {
					if(current->getType() != round[k]->getType()) {
						++cpt;
					}
				}
				if(cpt > 2) {
					int k(0), random(rand());
					while(k < 4) {
						int GROUND_type = round[(k+random)%4]->getType();
						bool GROUND_tileBorders[4] = {false,false,false,false};

						Ground* l_ground = m_tileset.getGround(GROUND_type, GROUND_tileBorders);

						if(l_ground != NULL) {
							if(l_ground->getBehavior() != FLUID) {
								m_grounds[i + j * width] = l_ground;
								k = 4;
							}
						}
						else {
							std::cout << "Une erreur est survenue lors de la génération d'un sol. (4)" << std::endl;
						}
						++k;
					}
				}
			}
			else {
				std::cout << "Une erreur est survenue lors de la génération d'un sol. (6)" << std::endl;
			}
		}
	}

	for(int j(0) ; j < height ; ++j) {
		for(int i(0) ; i < width ; ++i) {

			//===== GROUND : passe 3 (tileBorders) =====

			int GROUND_type = m_grounds[i + j * width]->getType();
			bool GROUND_tileBorders[4] = {false,false,false,false};

			GROUND_tileBorders[0] = (i > 0 && m_grounds[i + j * width]->hasBorderWith(m_grounds[i - 1 + j * width]->getType()));
			GROUND_tileBorders[1] = (j < height-1 && m_grounds[i + j * width]->hasBorderWith(m_grounds[i + (j + 1) * width]->getType()));
			GROUND_tileBorders[2] = (j > 0 && m_grounds[i + j * width]->hasBorderWith(m_grounds[i + (j - 1) * width]->getType()));
			GROUND_tileBorders[3] = (i < width-1 && m_grounds[i + j * width]->hasBorderWith(m_grounds[i + 1 + j * width]->getType()));

			Ground* l_ground = m_tileset.getGround(GROUND_type, GROUND_tileBorders);

			if(l_ground != NULL) {

				m_grounds[i + j * width] = l_ground;

				sf::Vertex* quadGround = &m_VertexGrounds[(i + j * width) * 4];

				for(int k(0) ; k < 4 ; ++k) {
					quadGround[k].texCoords = (l_ground->getQuad())[k].texCoords;
				}
			}
			else {
				std::cout << "Une erreur est survenue lors de la génération d'un sol. (5)" << std::endl;
			}


			//===== ELEMENT =====


			int ELEMENT_type = rand()%m_tileset.getElementCount();

			Element* l_element = m_tileset.getElement(ELEMENT_type, GROUND_type);

			if(l_element != NULL) {

				if(l_element->getBehavior() == DEFAULT) {

					int proportion = 0;
					if(i > 0) {
						if(ELEMENT_type + 2 > m_tileset.getElementCount()) {
							ELEMENT_type = m_grounds[i - 1 + j * width]->getType();
							proportion = ELEMENT_PROPORTION + 10; //!\ Before : == && 50
						}
					}
					else if(j > 0) {
						if(ELEMENT_type + 2 > m_tileset.getElementCount()) {
							ELEMENT_type = m_grounds[i + (j - 1) * width]->getType();
							proportion = ELEMENT_PROPORTION + 10; //!\ Before : == && 50
						}
					}

					if(rand()%100 < ELEMENT_PROPORTION + proportion) {

						m_elements[i + j * width] = l_element;
						sf::Vertex*quadElementDown = &m_VertexElementsDown[(i + j * width) * 4];
						sf::Vertex*quadElementUp = &m_VertexElementsUp[(i + j * width) * 4];

						quadElementDown[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
						quadElementDown[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
						quadElementDown[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
						quadElementDown[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

						if(j > 0) {
							quadElementUp[0].position = sf::Vector2f(i * tileSize.x, (j-1) * tileSize.y);
							quadElementUp[1].position = sf::Vector2f((i + 1) * tileSize.x, (j-1) * tileSize.y);
							quadElementUp[2].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
							quadElementUp[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
						}

						for(int k(0) ; k < 4 ; ++k) {
							quadElementDown[k].texCoords = (l_element->getQuadDown())[k].texCoords;
							quadElementUp[k].texCoords = (l_element->getQuadUp())[k].texCoords;
						}
					}
				}
				else if(l_element->getBehavior() == FOREST) {

					if(rand()%100 < ELEMENT_PROPORTION / 3) {

						addElement(l_element->getType(), sf::Vector2i(i,j));

						int areaX(rand()%ELEMENT_AREASIZE), areaY(rand()%ELEMENT_AREASIZE);
						for(int k(-areaX) ; k <= areaX ; ++k) {
							for(int l(-areaY) ; l <= areaY ; ++l) {
								if(i + k >= 0 && i + k < width && j + l >= 0 && j + l < height) {

									l_element = m_tileset.getElement(ELEMENT_type, m_grounds[i + k + (j + l) * width]->getType());
									if(l_element != NULL && rand()%100 < ELEMENT_PROPORTION + 25) {
										m_elements[i + k + (j + l) * width] = l_element;
										sf::Vertex* quadElementDown = &m_VertexElementsDown[(i + k + (j + l) * width) * 4];
										sf::Vertex* quadElementUp = &m_VertexElementsUp[(i + k + (j + l) * width) * 4];

										quadElementDown[0].position = sf::Vector2f((i + k) * tileSize.x, (j + l) * tileSize.y);
										quadElementDown[1].position = sf::Vector2f((i + k + 1) * tileSize.x, (j + l) * tileSize.y);
										quadElementDown[2].position = sf::Vector2f((i + k + 1) * tileSize.x, (j + l + 1) * tileSize.y);
										quadElementDown[3].position = sf::Vector2f((i + k) * tileSize.x, (j + l + 1) * tileSize.y);

										if(j + l > 0) {
											quadElementUp[0].position = sf::Vector2f((i + k) * tileSize.x, (j + l - 1) * tileSize.y);
											quadElementUp[1].position = sf::Vector2f((i + k + 1) * tileSize.x, (j + l - 1) * tileSize.y);
											quadElementUp[2].position = sf::Vector2f((i + k + 1) * tileSize.x, (j + l) * tileSize.y);
											quadElementUp[3].position = sf::Vector2f((i + k) * tileSize.x, (j + l) * tileSize.y);
										}

										for(int k(0) ; k < 4 ; ++k) {
											quadElementDown[k].texCoords = (l_element->getQuadDown())[k].texCoords;
											quadElementUp[k].texCoords = (l_element->getQuadUp())[k].texCoords;
										}
									}
								}
							}
						}
					}
				}
				else {
					std::cout << "Une erreur est survenue lors de la génération d'un objet. (1)" << std::endl;
				}
			}
			else {
//					std::cout << "Une erreur est survenue lors de la génération d'un objet. (2)" << std::endl;
			}

		}
	}
}

bool TileMap::load(std::string path) {

	std::ifstream file(path.c_str());
	if(!file) {
		std::cout << "Ouverture du fichier de sauvegarde de carte impossible." << std::endl;
		return false;
	}

	std::string l_path;
	file >> l_path;
	if(!m_tileset.load(l_path)) {
		std::cout << "Chargement du tileset impossible." << std::endl;
		return false;
	}

	file >> m_dimensions.x >> m_dimensions.y;

	m_grounds.resize(m_dimensions.x * m_dimensions.y);
	m_elements.resize(m_dimensions.x * m_dimensions.y);

	int GROUND_type, ELEMENT_type;

	for(unsigned int j(0) ; j < m_dimensions.y ; ++j) {
		for(unsigned int i(0) ; i < m_dimensions.x ; ++i) {
			file >> GROUND_type;
			changeGround(GROUND_type, sf::Vector2i(i, j));
		}
	}
	for(unsigned int j(0) ; j < m_dimensions.y ; ++j) {
		for(unsigned int i(0) ; i < m_dimensions.x ; ++i) {
			file >> ELEMENT_type;
			if(ELEMENT_type == -1) {
				removeElement(sf::Vector2i(i, j));
			}
			else {
				addElement(ELEMENT_type, sf::Vector2i(i, j));
			}
		}
	}

	for(unsigned int i(0) ; i < m_dimensions.x ; ++i) {
		for(unsigned int j(0) ; j < m_dimensions.y ; ++j) {
			updateBorders(sf::Vector2i(i, j));
		}
	}

	m_tileset.TEST();

	return true;
}

bool TileMap::save(std::string path) const {

	std::ofstream file(path.c_str());
	if(!file) {
		std::cout << "Ecriture du fichier de sauvegarde de carte impossible." << std::endl;
		return false;
	}

	file << m_tileset.getPath() << std::endl;
	file << m_dimensions.x << " " << m_dimensions.y << std::endl;

	file << std::endl;
	for(unsigned int j(0) ; j < m_dimensions.y ; ++j) {
		for(unsigned int i(0) ; i < m_dimensions.x ; ++i) {
			file << " " << m_grounds[i + j * m_dimensions.x]->getType() << " ";
		}
		file << std::endl;
	}

	file << std::endl;
	for(unsigned int j(0) ; j < m_dimensions.y ; ++j) {
		for(unsigned int i(0) ; i < m_dimensions.x ; ++i) {
			if(m_elements[i + j * m_dimensions.x] == NULL) {
				file << -1 << " ";
			}
			else {
				file << " " << m_elements[i + j * m_dimensions.x]->getType() << " ";
			}
		}
		file << std::endl;
	}

	return true;
}

void TileMap::drawGrounds(sf::RenderTarget& target) const {

	sf::RenderStates states;
	states.texture = m_tileset.getTileset();
	target.draw(m_VertexGrounds, states);

}

void TileMap::drawElementsDown(sf::RenderTarget& target) const {

	sf::RenderStates states;
	states.texture = m_tileset.getTileset();
	target.draw(m_VertexElementsDown, states);

}

void TileMap::drawElementsUp(sf::RenderTarget& target) {

	sf::RenderStates states;
	states.texture = m_tileset.getTileset();
	target.draw(m_VertexElementsUp, states);

    sf::CircleShape c(10);
    c.setFillColor(sf::Color::Red);
    sf::Vector2i u;
    /*
    for(std::list< sf::Vector2i >::iterator it = m_way.begin(); it != m_way.end(); ++it) {
        u.x=(*it).x;
        u.y=(*it).y;
        c.setPosition(getAbs(u));
        target.draw(c);
    }
    */

    c.setRadius(5);
    c.setFillColor(sf::Color::Magenta);

    sf::Vector2f v;
    for(std::list< sf::Vector2f >::iterator it = m_cut.begin(); it != m_cut.end(); ++it) {
        v.x= (*it).x;
        v.y= (*it).y;
        c.setPosition(v);
        target.draw(c);
    }

}

bool TileMap::isPassable( sf::Vector2i pos ) const
{
	Ground * s = getGround(pos);
	Element * e = getElement(pos);
	if( s && e ) {
		return s->isPassable() && e->isPassable();
	} else if ( s ) {
		return s->isPassable();
	} else if ( e ) {
		return e->isPassable();
	}

	return false;
}

std::list< sf::Vector2f > TileMap::findWay( sf::Vector2f from, sf::Vector2f to, int entityWidth, int perception )
{
    /// RECODE : Optimizen

    std::list< sf::Vector2i > way = pathfinding(this, getXY(from), getXY(to), entityWidth, perception);
	std::list< sf::Vector2f > wayAbs;

	for(std::list< sf::Vector2i >::iterator it = way.begin(); it != way.end(); ++it) {
        wayAbs.push_back(getAbs(*it));
	}

    m_way = way;
	std::list< sf::Vector2f > cut;

	if(!wayAbs.empty()) {

        wayAbs.push_front(from);

        cut.push_back(wayAbs.front());
        std::list< sf::Vector2f >::iterator t = wayAbs.begin();
        t++;
        if(t != wayAbs.end())
        {
            sf::Vector2f current = *t;
            t++;
            for(std::list< sf::Vector2f >::iterator it = t; it != wayAbs.end(); ++it)
            {
                if(! ((isShortcut(*it, cut.back())) &&
                     (isShortcut(posLarg(true, *it, cut.back(), 15), posLarg(false, cut.back(), *it, 15))) &&
                     (isShortcut(posLarg(false, *it, cut.back(), 15), posLarg(true, cut.back(), *it, 15)))))
                {
                    cut.push_back(current);
                } else {

                }
                t++;
                current = (*it);
            }

            if(isPassable(getXY(current))) {
                cut.push_back(current);
            } else {
                t--;
                t--;
                cut.push_back(*t);
            }
        }

	}

	m_cut = cut;

	return cut;
}

bool TileMap::isShortcut(sf::Vector2f u, sf::Vector2f v)
{
    float x, y;

	if ( std::fabs(v.x - u.x) >= m_tileset.getTileSize().x / 1.2 || std::fabs(v.y - u.y) >= m_tileset.getTileSize().y / 1.2 )
	{
	    x = u.x + ( (v.x - u.x) / 2 );
	    y = u.y + ( (v.y - u.y) / 2 );

		return ( isShortcut(u, sf::Vector2f(x, y)) && isShortcut(sf::Vector2f(x, y), v) );
	}
	else
	{
        sf::Vector2i t = getXY(v);
	    return isPassable( t );
	}
}
