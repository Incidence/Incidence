#include "Case.hpp"

Case::Case() { 

	m_type = TERRE_DEFAUT;
	m_tempsRecolte = sf::seconds(0);
	m_ressources[0] = m_ressources[1] = AUCUN;
	m_franchissable = true;

}

Case::Case(int type) {

	m_type = type;

	setTempsRecolte();
	setRessources();
	setFranchissable();

}

Case::~Case() {
	//TODO
}

int Case::getType() const { return m_type; }

void Case::setType(int type) {

	m_type = type;

	setTempsRecolte();
	setRessources();
	setFranchissable();

}

sf::Time Case::getTempsRecolte() { return m_tempsRecolte; }

int Case::getRessource(int i) {

	if(i == 0 || i == 1) {
		return m_ressources[i];
	}
	else {
		return AUCUN;
	}

}

bool Case::getFranchissable() { return m_franchissable; }

void Case::setTempsRecolte() {

	switch(m_type) {
		//TODO
	}

}

void Case::setRessources() {

	switch(m_type) {
		//TODO
	}

}

void Case::setFranchissable() {

	switch(m_type) {
		//TODO
	}

}
