#include "Carte.hpp"

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

const Sol Carte::getSol(sf::Vector2f position) const {
	//TODO
}

const Element Carte::getElement(sf::Vector2f position) const {
	//TODO
}

void Carte::changerSol(int type, sf::Vector2f position) {
	//TODO
}

void Carte::ajouterElement(int type, sf::Vector2f position) {
	//TODO
}

void Carte::supprimerElement(sf::Vector2f position) {
	//TODO
}

void Carte::generate() {
	//TODO
}

bool Carte::charger(std::string path) {
	//TODO
}

bool Carte::sauver(std::string path) const {
	//TODO
}

void Carte::drawSols(sf::RenderTarget& target, sf::RenderStates states) const {

	states.texture = m_tileset.getTileset();
	target.draw(m_VertexSols);

}

void Carte::drawElementsBas(sf::RenderTarget& target, sf::RenderStates states) const {

	states.texture = m_tileset.getTileset();
	target.draw(m_VertexElementsBas);

}

void Carte::drawElementsHaut(sf::RenderTarget& target, sf::RenderStates states) const {

	states.texture = m_tileset.getTileset();
	target.draw(m_VertexElementsHaut);

}
