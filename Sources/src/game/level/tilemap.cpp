#include "tilemap.hpp"

#include <stdlib.h>
#include <iostream>

#include "pathfinding.hpp"

#define ELEMENT_PROPORTION 10

TileMap::TileMap(TileSet tileset, sf::Vector2u dimensions) {

	m_tileset = tileset;
	m_dimensions = dimensions;

}

TileMap::~TileMap() {
	//TODO
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

//RECODE : renvoyer -1 si en dehors des limites
int TileMap::getId(sf::Vector2i position) const {

	return position.x + position.y * m_dimensions.x;

}

Ground* TileMap::getGround(sf::Vector2i position) const {

	int id = getId(position);
	if(id < m_grounds.size() || id > m_grounds.size()) {
		return m_grounds[id];
	}
	else {
		return NULL;
	}

}

Element* TileMap::getElement(sf::Vector2i position) const {

	int id = getId(position);
	if(id < m_elements.size() || id > m_grounds.size()) {
		return m_elements[id];
	}
	else {
		return NULL;
	}

}

//FIXME : tester selon les types environnant -> hiérarchie
void TileMap::changeGround(int type, sf::Vector2i position) {

	int i = position.x;
	int j = position.y;
	sf::Vector2u tileSize = m_tileset.getTileSize();
	int width = m_dimensions.x;

	//===== GROUND =====

//FIXME : regénérer les bordures
	bool* tileBorders = m_grounds[i + j * width]->getTileBorders();
	Ground* l_ground = m_tileset.getGround(type, tileBorders);

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
		std::cout << "Une erreur est survenue lors du changement d'un ground." << std::endl;
	}

	//===== ELEMENT =====

	if(m_elements[i + j * width] != NULL) {
		addElement(m_elements[i + j * m_dimensions.x]->getType(), position);
	}

}

void TileMap::addElement(int type, sf::Vector2i position) {

	int i = position.x;
	int j = position.y;
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
//FIXME différencier ground incompatible et erreur
//		std::cout << "Une erreur est survenue lors de la génération d'un objet." << std::endl;
	}

}

void TileMap::removeElement(sf::Vector2i position) {

	int i = position.x;
	int j = position.y;
	int width = m_dimensions.x;

	m_elements[i + j * width] = NULL;

	sf::Vertex* quadElementDown = &m_VertexElementsDown[(i + j * width) * 4];
	sf::Vertex* quadElementUp = &m_VertexElementsUp[(i + j * width) * 4];

	for(int k(0) ; k < 4 ; ++k) {
		quadElementDown[k].position = sf::Vector2f(0,0);
		quadElementUp[k].position = sf::Vector2f(0,0);
	}

}



void TileMap::generate() {
	
	srand(time(NULL));
	
	int width = m_dimensions.x, height = m_dimensions.y;
	sf::Vector2u tileSize = m_tileset.getTileSize();
	
	m_grounds.resize(width * height);
	m_elements.resize(width * height);
	
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
								|| m_grounds[i - 1 + j * width]->hasTileBorderWith(k) 
								|| l_ground_tmp->hasTileBorderWith(m_grounds[i - 1 + j * width]->getType()))) {
								add = false;
							}
						}
						if(j > 0) {
							if(!(m_grounds[i + (j - 1) * width]->getType() == k
								|| m_grounds[i + (j - 1) * width]->hasTileBorderWith(k) 
								|| l_ground_tmp->hasTileBorderWith(m_grounds[i + (j - 1) * width]->getType()))) {
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
				
				if( ( current->hasTileBorderWith(round[0]->getType()) 
					&& current->hasTileBorderWith(round[1]->getType()) 
					&& current->hasTileBorderWith(round[2]->getType()) 
					&& current->hasTileBorderWith(round[3]->getType()) 
					) || (
					round[0]->hasTileBorderWith(current->getType()) 
					&& round[1]->hasTileBorderWith(current->getType()) 
					&& round[2]->hasTileBorderWith(current->getType()) 
					&& round[3]->hasTileBorderWith(current->getType()) 
					) ) {
					
					int k(0), random(rand());
					while(k < 4) {
						
						int GROUND_type = round[(k+random)%4]->getType();
						bool GROUND_tileBorders[4] = {false,false,false,false};
						
						Ground* l_ground = m_tileset.getGround(GROUND_type, GROUND_tileBorders);
						
						if(l_ground != NULL) {
							
							bool change = true;
							for(int l(0) ; l < 4 ; ++l) {
								if(!(round[l]->getType() == GROUND_type || l_ground->hasTileBorderWith(round[l]->getType()) || round[l]->hasTileBorderWith(GROUND_type))) {
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
			
			GROUND_tileBorders[0] = (i > 0 && m_grounds[i + j * width]->hasTileBorderWith(m_grounds[i - 1 + j * width]->getType()));
			GROUND_tileBorders[1] = (j < height-1 && m_grounds[i + j * width]->hasTileBorderWith(m_grounds[i + (j + 1) * width]->getType()));
			GROUND_tileBorders[2] = (j > 0 && m_grounds[i + j * width]->hasTileBorderWith(m_grounds[i + (j - 1) * width]->getType()));
			GROUND_tileBorders[3] = (i < width-1 && m_grounds[i + j * width]->hasTileBorderWith(m_grounds[i + 1 + j * width]->getType()));
			
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
							proportion == ELEMENT_PROPORTION + 50;
						}
					}
					else if(j > 0) {
						if(ELEMENT_type + 2 > m_tileset.getElementCount()) {
							ELEMENT_type = m_grounds[i + (j - 1) * width]->getType();
							proportion == ELEMENT_PROPORTION + 50;
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
					//TODO
				}
				else {
					std::cout << "Une erreur est survenue lors de la génération d'un objet." << std::endl;
				}
			}
			else {
//FIXME différencier ground incompatible et erreur
//					std::cout << "Une erreur est survenue lors de la génération d'un objet." << std::endl;
			}
			
		}
	}
	
}

bool TileMap::load(std::string path) {
	//TODO
	return false;
}

bool TileMap::save(std::string path) const {
	//TODO
	return false;
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

void TileMap::drawElementsUp(sf::RenderTarget& target) const {

	sf::RenderStates states;
	states.texture = m_tileset.getTileset();
	target.draw(m_VertexElementsUp, states);

}

bool TileMap::isPassable( sf::Vector2i pos ) const
{
	return getGround(pos)->isPassable() && getElement(pos)->isPassable();
}

std::list< sf::Vector2f > TileMap::findWay( sf::Vector2f from, sf::Vector2f to, int entityWidth )
{
	//std::list< sf::Vector2i > way = pathfinding(this, getXY(from), getXY(to), entityWidth);
	std::list< sf::Vector2f > cut;
// TODO : Raccourcit + passage case->pixel
// Add 1er, add 2em :
// Pour chaque autre point :
//      S'il existe un chemin entre le current et celui avant le top_list, pop le top
//      add current to cut

	return cut;
}
