#include "sol.hpp"

Sol::Sol(const int type, const std::string nom, const bool franchissable, std::vector<int> bords, bool* bordures, sf::Vertex* quad) {

	m_type = type;
	m_nom = nom;
	m_franchissable = franchissable;
	m_bords = bords;
	m_bordures = bordures;
	m_quad = quad;

}

Sol::~Sol() {
	//TODO
}

int Sol::getType() const {

	return m_type;

}

std::string Sol::getNom() const {

	return m_nom;

}

bool Sol::isFranchissable() const {

	return m_franchissable;

}

bool* Sol::getBordures() const {

	return m_bordures;

}

sf::Vertex* Sol::getQuad() const {

	return m_quad;

}

bool Sol::isBord(int type) const {

	for(unsigned int i(0) ; i < m_bords.size() ; ++i) {
		if(m_bords[i] == type) {
			return true;
		}
	}

	return false;

}
