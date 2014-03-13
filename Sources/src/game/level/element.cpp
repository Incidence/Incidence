#include "element.hpp"

Element::Element(int type, int groundType, std::string name, TileBehavior behavior, bool passable, sf::Time pickingTime, std::vector<Ressource> ressources, sf::Vertex* quad_down, sf::Vertex* quad_up) {

	m_type = type;
	m_groundType = groundType;
	m_name = name;
	m_behavior = behavior;
	m_passable = passable;
	m_pickingTime = pickingTime;
	m_ressources = ressources;
	m_quad_down = quad_down;
	m_quad_up = quad_up;

}

Element::~Element() {
	//TODO
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

sf::Time Element::getPickingTime() const {

	return m_pickingTime;

}

std::vector<Ressource> Element::getRessources() const {

	return m_ressources;

}

sf::Vertex* Element::getQuadDown() const {

	return m_quad_down;

}

sf::Vertex* Element::getQuadUp() const {

	return m_quad_up;

}

bool Element::containResource( RessourceType t ) const
{
    for(unsigned int i = 0; i < m_ressources.size(); ++i) {
        if(m_ressources[i].type == t) {
            return true;
        }
    }

    return false;
}

int Element::getQuantityOf( RessourceType t ) const
{
    for(unsigned int i = 0; i < m_ressources.size(); ++i) {
        if(m_ressources[i].type == t) {
            return m_ressources[i].quantity;
        }
    }

    return 0;
}
