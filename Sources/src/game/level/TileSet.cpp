#include "TileSet.hpp"
#include <iostream>
#include <fstream>

#define MAX_INT 65536  // 2^16

TileSet::TileSet() {
	
	m_tileset = sf::Texture();
	m_tilesize = sf::Vector2u(0,0);
	m_nombreSol = 0;
	m_nombreElement = 0;
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

sf::Vector2u TileSet::getTileSize() const { 
	
	return m_tilesize; 
	
}

int TileSet::getNombreSol() const {
	
	return m_nombreSol;
	
}

int TileSet::getNombreElement() const {
	
	return m_nombreElement;
	
}

/*
 *** Entree : un entier correspondant au type de sol et un tableau de 4 booléens indiquant ses bordures
 *** Sortie : un pointeur sur une instance constante du sol, NULL s'il n'existe pas
*/
Sol* TileSet::getSol(int type, bool* bordures) {
	
	bool result;
	
	for(int i(0) ; i < m_sols.size() ; ++i) {
		result = true;
		
		if(m_sols[i].getType() != type) {
			result = false;
		}
		else {
			for(int j(0) ; j < 4 ; ++j) {
				if((m_sols[i].getBordures())[j] != bordures[j]) {
					result = false;
				}
			}
			if(result) {
				return &m_sols[i];
			}
		}
	}
	
	return NULL;
	
}

/*
 *** Entree : deux entiers correspondant au type d'élément et au type de sol de la case
 *** Sortie : un pointeur sur une instance constante de l'élément, NULL s'il n'existe pas
*/
Element* TileSet::getElement(int type, int typeSol) {
	
	for(int i(0) ; i < m_elements.size() ; ++i) {
		if(m_elements[i].getType() == type && m_elements[i].getTypeSol() == typeSol) {
			return &m_elements[i];
		}
	}
	
	return NULL;
	
}

/*
 *** Description : cette fonction charge le tileset en fonction de tous les paramètres définis dans le fichier ini
 *                 normalement situé dans le même dossier que le tileset, avec le même nom.
 * 
 *** Entree : une chaîne de caractères contenant le chemin (absolu ou relatif) du fichier .png du tileset
 *** Sortie : un booléen indiquant si le chargement est complet.
*/
bool TileSet::load(const std::string& path) { 
	
	// === OUVERTURE DES FICHIERS ===
	
	std::string l_path = path;
	
	if(!m_tileset.loadFromFile(l_path)) {
		std::cout << "Ouverture du fichier png du tileset impossible." << std::endl;
		return false;
	}
	
	l_path.replace(l_path.find_last_of('.') + 1, l_path.size() - 1, "ini");
	
	std::ifstream config(l_path.c_str());
	if(!config) {
		std::cout << "Ouverture du fichier ini du tileset impossible." << std::endl;
		return false;
	}
		
	std::string motClef;
	config >> motClef;
	
	
	// === LECTURE DU FICHIER INI ===
	
	int currentX = 0, currentY = 0;
	int nbColonneSol = 0, nbColonneElement = 0;
	m_nombreSol = m_nombreElement = 0;
	
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
			
			int SOL_type;
			std::string SOL_nom;
			bool SOL_franchissable;
			std::vector<int> SOL_bords;
			
			std::string tmp;
			config >> SOL_type >> SOL_nom >> tmp;
			SOL_franchissable = (tmp.compare("true") == 0);
			config >> tmp;
			if(tmp.compare("<") != 0) {
				std::cout << "Mauvais format de ressource dans le fichier ini du tileset." << std::endl;
				return false;
			}
			config >> tmp;
			
			while(tmp.compare(">") != 0) {
				SOL_bords.push_back(atoi(tmp.c_str()));
				config >> tmp;
			}
			
			for(int i(0) ; i < nbColonneSol ; ++i) {
				
				bool* SOL_bordures = new bool[4];
				sf::Vertex* SOL_quad = new sf::Vertex[4];
				
				SOL_bordures[0] = ((i & 8) > 0);
				SOL_bordures[1] = ((i & 4) > 0);
				SOL_bordures[2] = ((i & 2) > 0);
				SOL_bordures[3] = ((i & 1) > 0);
				
				SOL_quad[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, currentY * m_tilesize.y);
				SOL_quad[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, currentY * m_tilesize.y);
				SOL_quad[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
				SOL_quad[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y); 
				
				m_sols.push_back(Sol(SOL_type, SOL_nom, SOL_franchissable, SOL_bords, SOL_bordures, SOL_quad));
				
				++ currentX;
				
			}
			
			currentX = 0;
			++ currentY;
			++m_nombreSol;
			
		}
		else if(motClef.compare("element") == 0) {
			
			int ELEMENT_type;
			int ELEMENT_hauteur;
			int ELEMENT_typeSol;
			std::string ELEMENT_nom;
			bool ELEMENT_franchissable;
			int ELEMENT_tempsRecolte;
			std::vector<Ressource> ELEMENT_ressources;
			
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
				
				sf::Vertex* ELEMENT_quad_bas = new sf::Vertex[4];
				sf::Vertex* ELEMENT_quad_haut = new sf::Vertex[4];
				
				config >> ELEMENT_typeSol;
				
				if(ELEMENT_hauteur == 1) {
					
					ELEMENT_quad_bas[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, currentY * m_tilesize.y);
					ELEMENT_quad_bas[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, currentY * m_tilesize.y);
					ELEMENT_quad_bas[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
					ELEMENT_quad_bas[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y); 
					
//FIXME : codé en dur (texture transparente)
					ELEMENT_quad_haut[0].texCoords = sf::Vector2f(480,384);
					ELEMENT_quad_haut[1].texCoords = sf::Vector2f(512,384);
					ELEMENT_quad_haut[2].texCoords = sf::Vector2f(512,416);
					ELEMENT_quad_haut[3].texCoords = sf::Vector2f(480,416); 
					
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
					
					++ currentX;
			}
			
			currentX = 0;
			currentY += ELEMENT_hauteur;
			++m_nombreElement;
			
			config >> tmp;
			
		}
		else {
			// Ignorer la ligne complète
			config.ignore(MAX_INT, '\n');
		}
		
		config >> motClef;
	}
	
	config.close();
	
	return true;
	
}

/*
 *** Description : cette fonction affiche tout le contenu du tileset. Utile pour vérifier le chargement.
 * 
 *** Entree : void
 *** Sortie : void
*/
void TileSet::TEST() {
	std::cout << "===== TILESET =====" << std::endl << "tilesize : " << m_tilesize.x << " x " << m_tilesize.y << std::endl;
	std::cout << std::endl << m_nombreSol << " Sols :" << std::endl;
	for(int i(0) ; i < m_sols.size() ; ++i) {
		std::cout << "  " << m_sols[i].getType() << " " << m_sols[i].getNom() << " " << m_sols[i].isFranchissable() << " ";
		for(int j(0) ; j < 4 ; ++j) {
			std::cout << (m_sols[i].getBordures())[j];
		}
		std::cout << " < ";
		for(int j(0) ; j < m_sols.size() ; ++j) {
			if(m_sols[i].isBord(j)) {
				std::cout << j << " ";
			}
		}
		std::cout << ">" << std::endl;
		
		std::cout << "    Quad : ";
		for(int j(0) ; j < 4 ; ++j) {
			std::cout << "[" << (m_sols[i].getQuad())[j].texCoords.x << "," << (m_sols[i].getQuad())[j].texCoords.y << "] ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << m_nombreElement << " Elements :" << std::endl;
	for(int i(0) ; i < m_elements.size() ; ++i) {
		std::cout << "  " << m_elements[i].getType() << " " << m_elements[i].getTypeSol() << " " << m_elements[i].getNom() << " " << m_elements[i].isFranchissable() << " " << m_elements[i].getTempsRecolte().asSeconds() << " ";
		for(int j(0) ; j < (m_elements[i].getRessources()).size() ; ++j) {
			std::cout << (m_elements[i].getRessources())[j].type << (m_elements[i].getRessources())[j].quantite;
		}
		std::cout << std::endl;
		
		std::cout << "    Quad_Haut : ";
		for(int j(0) ; j < 4 ; ++j) {
			std::cout << "[" << (m_elements[i].getQuadHaut())[j].texCoords.x << "," << (m_elements[i].getQuadHaut())[j].texCoords.y << "] ";
		}
		std::cout << std::endl;
		
		std::cout << "    Quad_Bas : ";
		for(int j(0) ; j < 4 ; ++j) {
			std::cout << "[" << (m_elements[i].getQuadBas())[j].texCoords.x << "," << (m_elements[i].getQuadBas())[j].texCoords.y << "] ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
