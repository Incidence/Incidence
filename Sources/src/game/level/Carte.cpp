#include "Carte.hpp"
#include <stdlib.h>
#include <iostream>

Carte::Carte(TileSet tileset, sf::Vector2u dimensions) {

	m_tileset = tileset;
	m_dimensions = dimensions;
	m_sols = std::vector<Sol*>();
	m_elements = std::vector<Element*>();
	m_VertexSols = sf::VertexArray();
	m_VertexElementsBas = sf::VertexArray();
	m_VertexElementsHaut = sf::VertexArray();

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

Sol* Carte::getSol(sf::Vector2f position) const {
	
	int i = (int)(position.x/m_tileset.getTileSize().x);
	int j = (int)(position.y/m_tileset.getTileSize().y);
	
	return m_sols[i + j * m_dimensions.x];
	
}

Element* Carte::getElement(sf::Vector2f position) const {
	
	int i = (int)(position.x/m_tileset.getTileSize().x);
	int j = (int)(position.y/m_tileset.getTileSize().y);
	
	return m_elements[i + j * m_dimensions.x];
	
}

void Carte::changerSol(int type, sf::Vector2f position) {
	
	int i = (int)(position.x/m_tileset.getTileSize().x);
	int j = (int)(position.y/m_tileset.getTileSize().y);
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

void Carte::ajouterElement(int type, sf::Vector2f position) {
	
	int i = (int)(position.x/m_tileset.getTileSize().x);
	int j = (int)(position.y/m_tileset.getTileSize().y);
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

void Carte::supprimerElement(sf::Vector2f position) {
	
	int i = (int)(position.x/m_tileset.getTileSize().x);
	int j = (int)(position.y/m_tileset.getTileSize().y);
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
			
			//===== SOL =====
			
			int SOL_type = rand()%m_tileset.getNombreSol();
			bool SOL_bordures[4] = {false,false,false,false};
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
			
			if(rand()%100 < 40) {
				
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
	
}

bool Carte::charger(std::string path) {
	//TODO
}

bool Carte::sauver(std::string path) const {
	//TODO
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
