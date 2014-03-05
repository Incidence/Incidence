#include "Carte.hpp"

Carte::Carte() {
	//TODO
}

Carte::Carte(TileSet tileset) { m_tileset = tileset; }

Carte::Carte(TileSet tileset, sf::Vector2u dimensions) {

	m_tileset = tileset;
	m_dimensions = dimensions;

}

Carte::~Carte() {
	//TODO
}

sf::Vector2u Carte::getDimensions() { return m_dimensions; }

void Carte::setDimensions(sf::Vector2u dimensions) { dimensions = m_dimensions; }

void Carte::setTileSet(TileSet tileset) { m_tileset = tileset; }

Case Carte::getSol(sf::Vector2f position) {

	sf::Vector2u tilesize = m_tileset.getTileSize();
	int ligne = (int)(position.y/tilesize.y);
	int colonne = (int)(position.x/tilesize.x);

	return m_cases[ligne*m_dimensions.x+colonne];

}

Case Carte::getObjet(sf::Vector2f position) {

	sf::Vector2u tilesize = m_tileset.getTileSize();
	int ligne = (int)(position.y/tilesize.y);
	int colonne = (int)(position.x/tilesize.x);

	return m_cases[m_dimensions.x*m_dimensions.y + ligne*m_dimensions.x+colonne];

}

Case Carte::getEntite(sf::Vector2f position) {

	sf::Vector2u tilesize = m_tileset.getTileSize();
	int ligne = (int)(position.y/tilesize.y);
	int colonne = (int)(position.x/tilesize.x);

	return m_cases[2*m_dimensions.x*m_dimensions.y + ligne*m_dimensions.x+colonne];

}

void Carte::ajouterObjet(int type, sf::Vector2f position) {

	sf::Vector2u tilesize = m_tileset.getTileSize();
	int ligne = (int)(position.y/tilesize.y);
	int colonne = (int)(position.x/tilesize.x);

	m_cases[m_dimensions.x*m_dimensions.y + ligne*m_dimensions.x+colonne].setType(type);

}

void Carte::supprimerObjet(sf::Vector2f position) {

	ajouterObjet(AUCUN, position);

}

void Carte::changerSol(int type, sf::Vector2f position) {

	sf::Vector2u tilesize = m_tileset.getTileSize();
	int ligne = (int)(position.y/tilesize.y);
	int colonne = (int)(position.x/tilesize.x);

	m_cases[ligne*m_dimensions.x+colonne].setType(type);

}

void Carte::ajouterEntite(int type, sf::Vector2f position) {

	sf::Vector2u tilesize = m_tileset.getTileSize();
	int ligne = (int)(position.y/tilesize.y);
	int colonne = (int)(position.x/tilesize.x);

	m_cases[2*m_dimensions.x*m_dimensions.y + ligne*m_dimensions.x+colonne].setType(type);

}

void Carte::supprimerEntite(sf::Vector2f position) {

	ajouterEntite(AUCUN, position);

}

void Carte::loadSol(const int* sol) {
	//TODO
}

void Carte::loadObjets(const int* objets) {
	//TODO
}

void Carte::loadEntites(const int* entites) {
	//TODO
}

void Carte::generate() {
	//TODO
}

bool Carte::charger(std::string path) {
	//TODO
}

bool Carte::sauver(std::string path) {
	//TODO
}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	drawSol(target, states);
	drawObjets(target, states);
	drawEntites(target, states);

}

void Carte::drawSol(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_sol);

}

void Carte::drawObjets(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_objets);

}

/* Cette fonction dessine les entités et si besoin les parties hautes 
 * des arbres qui devraient cacher les entités correspondantes.
 */
void Carte::drawEntites(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_entites);

	int longueur = m_dimensions.x, hauteur = m_dimensions.y;

	for(int i(longueur*hauteur) ; i<2*longueur*hauteur ; ++i) {
		if(m_cases[i + longueur*hauteur].getType() != AUCUN) {
			if(m_cases[i].getType() == ARBRE_HAUT || m_cases[i].getType() == ARBRE_FRUITIER_HAUT) {
				//TODO : target.draw(cases[i]) avec VertexArray
			}
		}
	}

}
