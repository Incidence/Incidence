#include "TileSet.hpp"
#include <iostream>
#include <fstream>
#include <limits>

TileSet::TileSet() {
	
	m_tileset = sf::Texture();
	m_tilesize = sf::Vector2u(0,0);
	m_sols = std::vector<Sol>();
	m_elements = std::vector<Element>();
	
}

TileSet::TileSet(const std::string path) { 
	
	this->load(path);
	
}

TileSet::~TileSet() {
	//TODO
}

const sf::Texture* TileSet::getTileset() const {
	
	return &m_tileset;
	
}

sf::Vector2u TileSet::getTileSize() { 
	
	return m_tilesize; 
	
}

Sol* TileSet::getSol(int type, bool* bordures) {
	
	for(int i(0) ; i < m_sols.size() ; ++i) {
		
	}
	
}

Element* TileSet::getElement(int type, int typeSol) {
	
	for(int i(0) ; i < m_elements.size() ; ++i) {
		
	}
	
}

bool TileSet::load(const std::string& path) { 
	
	std::string l_path = path;
	
	if(!m_tileset.loadFromFile(l_path)) {
		return false;
	}
	
	l_path.replace(l_path.find_last_of('.') + 1, l_path.size() - 1, "ini");
	
	std::ifstream config(l_path.c_str());
	if(!config) {
		return false;
	}
	
	int SOL_type;
	std::string SOL_nom;
	bool SOL_franchissable;
	std::vector<int> SOL_bords;
	bool SOL_bordures[4];
	sf::Vertex SOL_quad[4];
	
	int ELEMENT_type;
	int ELEMENT_hauteur;
	int ELEMENT_typeSol;
	std::string ELEMENT_nom;
	bool ELEMENT_franchissable;
	int ELEMENT_tempsRecolte;
	std::vector<Ressource> ELEMENT_ressources;
	sf::Vertex ELEMENT_quad_bas[4];
	sf::Vertex ELEMENT_quad_haut[4];
	
	std::string motClef;
	config >> motClef;
	
	int currentX = 0, currentY = 0;
	int nbColonneSol = 0, nbColonneElement = 0;
	
	while(!config.eof()) {
		
		if(motClef.compare("tilesize") == 0) {
			
			config >> m_tilesize.x;
			config >> m_tilesize.y;
			
		}
		else if(motClef.compare("nbColonneSol") == 0) {
			
			config >> nbColonneSol;
			
		}
		if(motClef.compare("nbColonneElement") == 0) {
			
			config >> nbColonneElement;
			
		}
		else if(motClef.compare("sol") == 0) {
			
			std::string tmp;
			config >> SOL_type >> SOL_nom >> tmp;
			SOL_franchissable = (tmp.compare("true") == 0)? true : false;
			config >> tmp >> tmp;
			
			while(tmp.compare(">") != 0) {
				SOL_bords.push_back(atoi(tmp.c_str()));
				config >> tmp;
			}
			
			for(int i(0) ; i < nbColonneSol ; ++i) {
				
				SOL_bordures[0] = ((i>>3) % 2 > 0);
				SOL_bordures[1] = ((i>>2) % 2 > 0);
				SOL_bordures[2] = ((i>>1) % 2 > 0);
				SOL_bordures[3] = ((i>>0) % 2 > 0);
				
				SOL_quad[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, currentY * m_tilesize.y);
				SOL_quad[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, currentY * m_tilesize.y);
				SOL_quad[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
				SOL_quad[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y); 
				
				m_sols.push_back(Sol(SOL_type, SOL_nom, SOL_franchissable, SOL_bords, SOL_bordures, SOL_quad));
				
				currentX += m_tilesize.x;
				
			}
			
			currentX = 0;
			currentY += m_tilesize.y;
			
		}
		else if(motClef.compare("element") == 0) {
			
			std::string tmp;
			config >> ELEMENT_type >> ELEMENT_hauteur >> ELEMENT_nom >> tmp;
			ELEMENT_franchissable = (tmp.compare("true") == 0)? true : false;
			config >> ELEMENT_tempsRecolte >> tmp >> tmp;
			
			while(tmp.compare(">") != 0) {
				Ressource r;
				if(tmp.compare("nourriture") == 0) {
					r.type = NOURRITURE;
				}
				else if(tmp.compare("bois") == 0) {
					r.type = BOIS;
				}
				else if(tmp.compare("pierre") == 0) {
					r.type = PIERRE;
				}
				else {
					std::cout << "Mauvais format de ressource dans le fichier ini du tileset." << std::endl;
					return false;
				}
				
				config >> r.quantite >> tmp;
				ELEMENT_ressources.push_back(r);
			}
			
			config >> tmp;
			
			for(int i(0) ; i < nbColonneElement ; ++i) {
				
				config >> ELEMENT_typeSol;
				
				if(ELEMENT_hauteur == 1) {
					
					ELEMENT_quad_bas[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, currentY * m_tilesize.y);
					ELEMENT_quad_bas[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, currentY * m_tilesize.y);
					ELEMENT_quad_bas[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
					ELEMENT_quad_bas[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y); 
					
				}
					
				else if(ELEMENT_hauteur == 2) {
						
						ELEMENT_quad_bas[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y);
						ELEMENT_quad_bas[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
						ELEMENT_quad_bas[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 2) * m_tilesize.y);
						ELEMENT_quad_bas[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 2) * m_tilesize.y); 
						
						ELEMENT_quad_haut[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, currentY * m_tilesize.y);
						ELEMENT_quad_haut[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, currentY * m_tilesize.y);
						ELEMENT_quad_haut[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
						ELEMENT_quad_haut[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y);
						
				}
				
				else {
					std::cout << "Mauvais format de hauteur dans le fichier ini du tileset." << std::endl;
					return false;
				}
					
					m_elements.push_back(Element(ELEMENT_type, ELEMENT_typeSol, ELEMENT_nom, ELEMENT_franchissable, sf::seconds(ELEMENT_tempsRecolte), ELEMENT_ressources, ELEMENT_quad_bas, ELEMENT_quad_haut));
					
					currentX += m_tilesize.x;
			}
			
			currentX = 0;
			currentY += (m_tilesize.y * (ELEMENT_hauteur + 1));
			
			config >> tmp;
			
		}
		else {
			config.ignore(1024, '\n');
		}
		
		config >> motClef;
	}
	
	config.close();
	
	return true;
	
}
