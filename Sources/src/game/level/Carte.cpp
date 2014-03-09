#include "Carte.hpp"

#include <stdlib.h>
#include <iostream>

#include "pathfinding.hpp"

#define POURCENTAGE_ELEMENT 40

Carte::Carte(TileSet tileset, sf::Vector2u dimensions) {

	m_tileset = tileset;
	m_dimensions = dimensions;
	//m_sols = std::vector<Sol*>(); // Useless. C'est automatique
	//m_elements = std::vector<Element*>(); // C'est pas du JAVA
	//m_VertexSols = sf::VertexArray(); // C'est pas des pointeurs donc pas besoin
	//m_VertexElementsBas = sf::VertexArray();
	//m_VertexElementsHaut = sf::VertexArray();

}

Carte::~Carte() {
	//TODO
}

void Carte::setTileSet(TileSet tileset) {

	m_tileset = tileset;

}

sf::Vector2u Carte::getDimensions() const {

	return m_dimensions;

}

void Carte::setDimensions(sf::Vector2u dimensions) {

	m_dimensions = dimensions;

}

int Carte::getX(sf::Vector2f position) const {

	return (int)(position.x/m_tileset.getTileSize().x);

}

int Carte::getY(sf::Vector2f position) const {

	return (int)(position.y/m_tileset.getTileSize().y);

}

sf::Vector2i Carte::getXY(sf::Vector2f position) const {

	return sf::Vector2i(getX(position), getY(position));

}

int Carte::getId(sf::Vector2i position) const {

	return position.x + position.y * m_dimensions.x;

}

Sol* Carte::getSol(sf::Vector2i position) const {

	int id = getId(position);
	if(id < m_sols.size()) {
		return m_sols[id];
	}
	else {
		return NULL;
	}

}

Element* Carte::getElement(sf::Vector2i position) const {

	int id = getId(position);
	if(id < m_elements.size()) {
		return m_elements[id];
	}
	else {
		return NULL;
	}

}

//FIXME : tester selon les types environnant -> hiérarchie
void Carte::changerSol(int type, sf::Vector2i position) {

	int i = position.x;
	int j = position.y;
	sf::Vector2u tileSize = m_tileset.getTileSize();
	int width = m_dimensions.x;

	//===== SOL =====

	bool* bordures = m_sols[i + j * width]->getBordures();
	Sol* l_sol = m_tileset.getSol(type, bordures);

	if(l_sol != NULL) {

		m_sols[i + j * width] = l_sol;
		sf::Vertex* quadSol = &m_VertexSols[(i + j * width) * 4];

		quadSol[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
		quadSol[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
		quadSol[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
		quadSol[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

		for(int k(0) ; k < 4 ; ++k) {
			quadSol[k].texCoords = (l_sol->getQuad())[k].texCoords;
		}
	}
	else {
		std::cout << "Une erreur est survenue lors du changement d'un sol." << std::endl;
	}

	//===== ELEMENT =====

	if(m_elements[i + j * width] != NULL) {
		ajouterElement(m_elements[i + j * m_dimensions.x]->getType(), position);
	}

}

void Carte::ajouterElement(int type, sf::Vector2i position) {

	int i = position.x;
	int j = position.y;
	sf::Vector2u tileSize = m_tileset.getTileSize();
	int width = m_dimensions.x;

	//===== ELEMENT =====

	int SOL_type = m_sols[i + j * width]->getType();
	Element* l_element = m_tileset.getElement(type, SOL_type);

	if(l_element != NULL) {

		m_elements[i + j * width] = l_element;
		sf::Vertex* quadElementBas = &m_VertexElementsBas[(i + j * width) * 4];
		sf::Vertex* quadElementHaut = &m_VertexElementsHaut[(i + j * width) * 4];

		quadElementBas[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
		quadElementBas[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
		quadElementBas[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
		quadElementBas[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

		if(j > 0) {
			quadElementHaut[0].position = sf::Vector2f(i * tileSize.x, (j-1) * tileSize.y);
			quadElementHaut[1].position = sf::Vector2f((i + 1) * tileSize.x, (j-1) * tileSize.y);
			quadElementHaut[2].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quadElementHaut[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
		}

		for(int k(0) ; k < 4 ; ++k) {
			quadElementBas[k].texCoords = (l_element->getQuadBas())[k].texCoords;
			quadElementHaut[k].texCoords = (l_element->getQuadHaut())[k].texCoords;
		}
	}
	else {
		supprimerElement(position);
//FIXME différencier sol incompatible et erreur
//		std::cout << "Une erreur est survenue lors de la génération d'un objet." << std::endl;
	}

}

void Carte::supprimerElement(sf::Vector2i position) {

	int i = position.x;
	int j = position.y;
	int width = m_dimensions.x;

	m_elements[i + j * width] = NULL;

	sf::Vertex* quadElementBas = &m_VertexElementsBas[(i + j * width) * 4];
	sf::Vertex* quadElementHaut = &m_VertexElementsHaut[(i + j * width) * 4];

	for(int k(0) ; k < 4 ; ++k) {
		quadElementBas[k].position = sf::Vector2f(0,0);
		quadElementHaut[k].position = sf::Vector2f(0,0);
	}

}

void Carte::generate() {
	
	srand(time(NULL));
	
	int width = m_dimensions.x, height = m_dimensions.y;
	sf::Vector2u tileSize = m_tileset.getTileSize();
	
	m_sols.resize(width * height);
	m_elements.resize(width * height);
	
	m_VertexSols.setPrimitiveType(sf::Quads);
	m_VertexSols.resize(width * height * 4);
	
	m_VertexElementsBas.setPrimitiveType(sf::Quads);
	m_VertexElementsBas.resize(width * height * 4);
	
	m_VertexElementsHaut.setPrimitiveType(sf::Quads);
	m_VertexElementsHaut.resize(width * height * 4);
	
	for(int j(0) ; j < height ; ++j) {
		for(int i(0) ; i < width ; ++i) {
			
			//===== SOL : passe 1 (type) =====
			
			int SOL_type = rand()%m_tileset.getNombreSol();
			bool SOL_bordures[4] = {false,false,false,false};
			
			if(i != 0 || j != 0) {
				
				std::vector<int> l_bords;
				if(i > 0 && j == 0) {
					l_bords.push_back(m_sols[i - 1 + j * width]->getType());
				}
				if(j > 0 && i == 0) {
					l_bords.push_back(m_sols[i + (j - 1) * width]->getType());
				}
				
				for(int k(0) ; k < m_tileset.getNombreSol() ; ++k) {
					Sol* l_sol_tmp = m_tileset.getSol(k, SOL_bordures);
					if(l_sol_tmp != NULL) {
						bool add = true;
						if(i > 0) {
							if(!(m_sols[i - 1 + j * width]->isBord(k) || l_sol_tmp->isBord(m_sols[i - 1 + j * width]->getType()))) {
								add = false;
							}
						}
						if(j > 0) {
							if(!(m_sols[i + (j - 1) * width]->isBord(k) || l_sol_tmp->isBord(m_sols[i + (j - 1) * width]->getType()))) {
								add = false;
							}
						}
						if(add) {
							l_bords.push_back(k);
						}
					}
					else {
						std::cout << "Une erreur est survenue lors de la génération d'un sol." << std::endl;
					}
				}
				
				SOL_type = l_bords[rand()%l_bords.size()];
				
			}
			
			Sol* l_sol = m_tileset.getSol(SOL_type, SOL_bordures);
			
			if(l_sol != NULL) {
				
				m_sols[i + j * width] = l_sol;
				
				sf::Vertex* quadSol = &m_VertexSols[(i + j * width) * 4];
				
				quadSol[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quadSol[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quadSol[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quadSol[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
				
				for(int k(0) ; k < 4 ; ++k) {
					quadSol[k].texCoords = (l_sol->getQuad())[k].texCoords;
				}
			}
			else {
				std::cout << "Une erreur est survenue lors de la génération d'un sol." << std::endl;
			}
			
			
			//===== ELEMENT =====
			
			if(rand()%100 < POURCENTAGE_ELEMENT) {
				
				int ELEMENT_type = rand()%m_tileset.getNombreElement();
				Element* l_element = m_tileset.getElement(ELEMENT_type, SOL_type);
				
				if(l_element != NULL) {
					
					m_elements[i + j * width] = l_element;
					sf::Vertex*quadElementBas = &m_VertexElementsBas[(i + j * width) * 4];
					sf::Vertex*quadElementHaut = &m_VertexElementsHaut[(i + j * width) * 4];
					
					quadElementBas[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					quadElementBas[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					quadElementBas[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					quadElementBas[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
					
					if(j > 0) {
						quadElementHaut[0].position = sf::Vector2f(i * tileSize.x, (j-1) * tileSize.y);
						quadElementHaut[1].position = sf::Vector2f((i + 1) * tileSize.x, (j-1) * tileSize.y);
						quadElementHaut[2].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
						quadElementHaut[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					}
					
					for(int k(0) ; k < 4 ; ++k) {
						quadElementBas[k].texCoords = (l_element->getQuadBas())[k].texCoords;
						quadElementHaut[k].texCoords = (l_element->getQuadHaut())[k].texCoords;
					}
				}
				else {
//FIXME différencier sol incompatible et erreur
//					std::cout << "Une erreur est survenue lors de la génération d'un objet." << std::endl;
				}
				
			}
			
		}
	}
	
	for(int j(0) ; j < height ; ++j) {
		for(int i(0) ; i < width ; ++i) {
			
			//===== SOL : passe 2 (bordures) =====
			
			int SOL_type = m_sols[i + j * width]->getType();
			bool SOL_bordures[4] = {false,false,false,false};
			
			SOL_bordures[0] = (i > 0 && SOL_type != m_sols[i - 1 + j * width]->getType());
			SOL_bordures[1] = (j < height-1 && SOL_type != m_sols[i + (j + 1) * width]->getType());
			SOL_bordures[2] = (j > 0 && SOL_type != m_sols[i + (j - 1) * width]->getType());
			SOL_bordures[3] = (i < width-1 && SOL_type != m_sols[i + 1 + j * width]->getType());
			
			Sol* l_sol = m_tileset.getSol(SOL_type, SOL_bordures);
			
			if(l_sol != NULL) {
				
				m_sols[i + j * width] = l_sol;
				
				sf::Vertex* quadSol = &m_VertexSols[(i + j * width) * 4];
				
				for(int k(0) ; k < 4 ; ++k) {
					quadSol[k].texCoords = (l_sol->getQuad())[k].texCoords;
				}
			}
			else {
				std::cout << "Une erreur est survenue lors de la génération d'un sol." << std::endl;
			}
			
		}
	}
	
}

bool Carte::charger(std::string path) {
	//TODO
	return false;
}

bool Carte::sauver(std::string path) const {
	//TODO
	return false;
}

void Carte::drawSols(sf::RenderTarget& target) const {

	sf::RenderStates states;
	states.texture = m_tileset.getTileset();
	target.draw(m_VertexSols, states);

}

void Carte::drawElementsBas(sf::RenderTarget& target) const {

	sf::RenderStates states;
	states.texture = m_tileset.getTileset();
	target.draw(m_VertexElementsBas, states);

}

void Carte::drawElementsHaut(sf::RenderTarget& target) const {

	sf::RenderStates states;
	states.texture = m_tileset.getTileset();
	target.draw(m_VertexElementsHaut, states);

}

bool Carte::isPassable( sf::Vector2i pos ) const
{
    return getSol(pos)->isFranchissable() && getElement(pos)->isFranchissable();
}

std::list< sf::Vector2f > Carte::findWay( sf::Vector2f from, sf::Vector2f to, int entityWidth )
{
    std::list< sf::Vector2i > way = pathfinding(this, getXY(from), getXY(to), entityWidth);
    std::list< sf::Vector2f > cut;

    /// TODO : Raccourcit + passage case->pixel
    // Add 1er, add 2em :
    // Pour chaque autre point :
    //      S'il existe un chemin entre le current et celui avant le top_list, pop le top
    //      add current to cut

    return cut;
}





























