#include "element.hpp"

Element::Element(int type, int groundType, std::string name, TileBehavior behavior, bool passable, float pickingTime, std::vector<Ressource> ressources, sf::Vertex* quad_down, sf::Vertex* quad_up) : Harvestable(pickingTime, ressources)
{
	m_type = type;
	m_groundType = groundType;
    m_name = name;
	m_behavior = behavior;
	m_passable = passable;
	m_quad_down = quad_down;
	m_quad_up = quad_up;
}

Element::~Element() {
	
	delete *m_quad_down;
	delete *m_quad_up;
	
}

int Element::getType() const {

	return m_type;

}

int Element::getGroundType() const {

	return m_groundType;

}

std::string Element::getName() const {

	return m_name;

}

TileBehavior Element::getBehavior() const {

	return m_behavior;

}

bool Element::isPassable() const {

	return m_passable;

}

sf::Vertex* Element::getQuadDown() const {

	return m_quad_down;

}

sf::Vertex* Element::getQuadUp() const {

	return m_quad_up;

}

bool Element::isHarvestable( void )
{
    return true;
}

void Element::havested( void )
{
    //m_removed = true;
}
