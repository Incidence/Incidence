#include "tileset.hpp"
#include <iostream>
#include <fstream>

#define MAX_INT 65536  // 2^16

TileSet::TileSet() {

	m_tileset = sf::Texture();
	m_tilesize = sf::Vector2u(0,0);
	m_groundCount = 0;
	m_elementCount = 0;
	m_grounds = std::vector<Ground>();
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

int TileSet::getGroundCount() const {

	return m_groundCount;

}

int TileSet::getElementCount() const {

	return m_elementCount;

}

/*
 *** Entree : un entier correspondant au type de sol et un tableau de 4 booléens indiquant ses bordures
 *** Sortie : un pointeur sur une instance constante du sol, NULL s'il n'existe pas
*/
Ground* TileSet::getGround(int type, bool* borders) {

	bool result;

	for(unsigned int i(0) ; i < m_grounds.size() ; ++i) {
		result = true;

		if(m_grounds[i].getType() != type) {
			result = false;
		}
		else {
			for(int j(0) ; j < 4 ; ++j) {
				if((m_grounds[i].getTileBorders())[j] != borders[j]) {
					result = false;
				}
			}
			if(result) {
				return &m_grounds[i];
			}
		}
	}

	return NULL;

}

/*
 *** Entree : deux entiers correspondant au type d'élément et au type de sol de la case
 *** Sortie : un pointeur sur une instance constante de l'élément, NULL s'il n'existe pas
*/
Element* TileSet::getElement(int type, int groundType) {

	for(unsigned int i(0) ; i < m_elements.size() ; ++i) {
		if(m_elements[i].getType() == type && m_elements[i].getGroundType() == groundType) {
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

	std::string keyWord;
	config >> keyWord;


	// === LECTURE DU FICHIER INI ===

	int currentX = 0, currentY = 0;
	int groundColumnCount = 0, elementColumnCount = 0;
	m_groundCount = m_elementCount = 0;

	while(!config.eof()) {

		if(keyWord.compare("tilesize") == 0) {

			config >> m_tilesize.x;
			config >> m_tilesize.y;

		}
		else if(keyWord.compare("groundColumnCount") == 0) {

			config >> groundColumnCount;

		}
		if(keyWord.compare("elementColumnCount") == 0) {

			config >> elementColumnCount;

		}
		else if(keyWord.compare("ground") == 0) {

			int GROUND_type;
			std::string GROUND_name;
			TileBehavior GROUND_behavior;
			bool GROUND_passable;
			std::vector<int> GROUND_borders;

			std::string tmp;
			config >> GROUND_type >> GROUND_name >> tmp;
			if(tmp.compare("default") == 0) {
				GROUND_behavior = DEFAULT;
			}
			else if(tmp.compare("fluid") == 0) {
				GROUND_behavior = FLUID;
			}
			else if(tmp.compare("cliff") == 0) {
				GROUND_behavior = CLIFF;
			}
			else {
				std::cout << "Mauvais format de comportement sol dans le fichier ini du tileset." << std::endl;
				return false;
			}
			config >> tmp;
			GROUND_passable = (tmp.compare("true") == 0);
			config >> tmp;
			if(tmp.compare("<") != 0) {
				std::cout << "Mauvais format de ressource dans le fichier ini du tileset." << std::endl;
				return false;
			}
			config >> tmp;

			while(tmp.compare(">") != 0) {
				GROUND_borders.push_back(atoi(tmp.c_str()));
				config >> tmp;
			}

			for(int i(0) ; i < groundColumnCount ; ++i) {

				bool* GROUND_tileBorders = new bool[4];
				sf::Vertex* GROUND_quad = new sf::Vertex[4];

				GROUND_tileBorders[0] = ((i & 8) > 0);
				GROUND_tileBorders[1] = ((i & 4) > 0);
				GROUND_tileBorders[3] = ((i & 2) > 0);
				GROUND_tileBorders[2] = ((i & 1) > 0);

				GROUND_quad[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, currentY * m_tilesize.y);
				GROUND_quad[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, currentY * m_tilesize.y);
				GROUND_quad[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
				GROUND_quad[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y);

				m_grounds.push_back(Ground(GROUND_type, GROUND_name, GROUND_behavior, GROUND_passable, GROUND_borders, GROUND_tileBorders, GROUND_quad));

				++ currentX;

			}

			currentX = 0;
			++ currentY;
			++m_groundCount;

		}
		else if(keyWord.compare("element") == 0) {

			int ELEMENT_type;
			int ELEMENT_height;
			int ELEMENT_groundType;
			std::string ELEMENT_name;
			TileBehavior ELEMENT_behavior;
			bool ELEMENT_passable;
			int ELEMENT_pickingTime;
			std::vector<Ressource> ELEMENT_ressources;

			std::string tmp;
			config >> ELEMENT_type >> ELEMENT_height >> ELEMENT_name >> tmp;
			if(tmp.compare("default") == 0) {
				ELEMENT_behavior = DEFAULT;
			}
			else if(tmp.compare("forest") == 0) {
				ELEMENT_behavior = FOREST;
			}
			else {
				std::cout << "Mauvais format de comportement element dans le fichier ini du tileset." << std::endl;
				return false;
			}
			config >> tmp;
			ELEMENT_passable = (tmp.compare("true") == 0)? true : false;
			config >> ELEMENT_pickingTime >> tmp >> tmp;

			while(tmp.compare(">") != 0) {
				Ressource r;
				if(tmp.compare("food") == 0) {
					r.type = FOOD;
				}
				else if(tmp.compare("wood") == 0) {
					r.type = WOOD;
				}
				else if(tmp.compare("stone") == 0) {
					r.type = STONE;
				}
				else {
					std::cout << "Mauvais format de ressource dans le fichier ini du tileset." << std::endl;
					return false;
				}

				config >> r.quantity >> tmp;
				ELEMENT_ressources.push_back(r);
			}

			config >> tmp;

			for(int i(0) ; i < elementColumnCount ; ++i) {

				sf::Vertex* ELEMENT_quad_down = new sf::Vertex[4];
				sf::Vertex* ELEMENT_quad_up = new sf::Vertex[4];

				config >> ELEMENT_groundType;

				if(ELEMENT_height == 1) {

					ELEMENT_quad_down[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, currentY * m_tilesize.y);
					ELEMENT_quad_down[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, currentY * m_tilesize.y);
					ELEMENT_quad_down[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
					ELEMENT_quad_down[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y);

					ELEMENT_quad_up[0].texCoords = sf::Vector2f(m_tileset.getSize().x - m_tilesize.x, m_tileset.getSize().y - m_tilesize.y);
					ELEMENT_quad_up[1].texCoords = sf::Vector2f(m_tileset.getSize().x, m_tileset.getSize().y - m_tilesize.y);
					ELEMENT_quad_up[2].texCoords = sf::Vector2f(m_tileset.getSize().x, m_tileset.getSize().y);
					ELEMENT_quad_up[3].texCoords = sf::Vector2f(m_tileset.getSize().x - m_tilesize.x, m_tileset.getSize().y);

				}

				else if(ELEMENT_height == 2) {

						ELEMENT_quad_down[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y);
						ELEMENT_quad_down[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
						ELEMENT_quad_down[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 2) * m_tilesize.y);
						ELEMENT_quad_down[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 2) * m_tilesize.y);

						ELEMENT_quad_up[0].texCoords = sf::Vector2f(currentX * m_tilesize.x, currentY * m_tilesize.y);
						ELEMENT_quad_up[1].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, currentY * m_tilesize.y);
						ELEMENT_quad_up[2].texCoords = sf::Vector2f((currentX + 1) * m_tilesize.x, (currentY + 1) * m_tilesize.y);
						ELEMENT_quad_up[3].texCoords = sf::Vector2f(currentX * m_tilesize.x, (currentY + 1) * m_tilesize.y);

				}

				else {
					std::cout << "Mauvais format de height dans le fichier ini du tileset." << std::endl;
					return false;
				}

					m_elements.push_back(Element(ELEMENT_type, ELEMENT_groundType, ELEMENT_name, ELEMENT_behavior, ELEMENT_passable, sf::seconds(ELEMENT_pickingTime), ELEMENT_ressources, ELEMENT_quad_down, ELEMENT_quad_up));

					++ currentX;
			}

			currentX = 0;
			currentY += ELEMENT_height;
			++m_elementCount;

			config >> tmp;

		}
		else {
			// Ignorer la ligne complète
			config.ignore(MAX_INT, '\n');
		}

		config >> keyWord;
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
	std::cout << std::endl << m_groundCount << " Grounds :" << std::endl;
	for(int i(0) ; i < (int)m_grounds.size() ; ++i) {
		std::cout << "  " << m_grounds[i].getType() << " " << m_grounds[i].getName() << " " << m_grounds[i].getBehavior() << " " << m_grounds[i].isPassable() << " ";
		for(int j(0) ; j < 4 ; ++j) {
			std::cout << (m_grounds[i].getTileBorders())[j];
		}
		std::cout << " < ";
		for(int j(0) ; j < (int)m_grounds.size() ; ++j) {
			if(m_grounds[i].hasTileBorderWith(j)) {
				std::cout << j << " ";
			}
		}
		std::cout << ">" << std::endl;

		std::cout << "    Quad : ";
		for(int j(0) ; j < 4 ; ++j) {
			std::cout << "[" << (m_grounds[i].getQuad())[j].texCoords.x << "," << (m_grounds[i].getQuad())[j].texCoords.y << "] ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << m_elementCount << " Elements :" << std::endl;
	for(int i(0) ; i < (int)m_elements.size() ; ++i) {
		std::cout << "  " << m_elements[i].getType() << " " << m_elements[i].getGroundType() << " " << m_elements[i].getName() << " " << m_elements[i].getBehavior() << " " << m_elements[i].isPassable() << " " << m_elements[i].getPickingTime().asSeconds() << " ";
		for(int j(0) ; j < (int)(m_elements[i].getRessources()).size() ; ++j) {
			std::cout << (m_elements[i].getRessources())[j].type << (m_elements[i].getRessources())[j].quantity;
		}
		std::cout << std::endl;

		std::cout << "    Quad_Haut : ";
		for(int j(0) ; j < 4 ; ++j) {
			std::cout << "[" << (m_elements[i].getQuadUp())[j].texCoords.x << "," << (m_elements[i].getQuadUp())[j].texCoords.y << "] ";
		}
		std::cout << std::endl;

		std::cout << "    Quad_Bas : ";
		for(int j(0) ; j < 4 ; ++j) {
			std::cout << "[" << (m_elements[i].getQuadDown())[j].texCoords.x << "," << (m_elements[i].getQuadDown())[j].texCoords.y << "] ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
