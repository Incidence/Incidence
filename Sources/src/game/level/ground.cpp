#include "ground.hpp"

Ground::Ground(const int type, const std::string name, const TileBehavior behavior, const bool passable, std::vector<int> borders, bool* tileBorders, sf::Vertex* quad) {

	m_type = type;
	m_name = name;
	m_behavior = behavior;
	m_passable = passable;
	m_borders = borders;
	m_tileBorders = tileBorders;
	m_quad = quad;

}

Ground::~Ground() {
	//TODO
}

int Ground::getType() const {

	return m_type;

}

std::string Ground::getName() const {

	return m_name;

}

TileBehavior Ground::getBehavior() const {
	
	return m_behavior;
	
}

bool Ground::isPassable() const {

	return m_passable;

}

std::vector<int> Ground::getBorders() const {

	return m_borders;

}

bool* Ground::getTileBorders() const {

	return m_tileBorders;

}

sf::Vertex* Ground::getQuad() const {

	return m_quad;

}

bool Ground::hasBorderWith(int type) const {

	for(unsigned int i(0) ; i < m_borders.size() ; ++i) {
		if(m_borders[i] == type) {
			return true;
		}
	}

	return false;

}
