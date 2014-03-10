#include "element.hpp"

Element::Element(int type, int typeSol, std::string nom, bool franchissable, sf::Time tempsRecolte, std::vector<Ressource> ressources, sf::Vertex* quad_bas, sf::Vertex* quad_haut) {

	m_type = type;
	m_typeSol = typeSol;
	m_nom = nom;
	m_franchissable = franchissable;
	m_tempsRecolte = tempsRecolte;
	m_ressources = ressources;
	m_quad_bas = quad_bas;
	m_quad_haut = quad_haut;

}

Element::~Element() {
	//TODO
}

int Element::getType() const {

	return m_type;

}

int Element::getTypeSol() const {

	return m_typeSol;

}

std::string Element::getNom() const {

	return m_nom;

}

bool Element::isFranchissable() const {

	return m_franchissable;

}

sf::Time Element::getTempsRecolte() const {

	return m_tempsRecolte;

}

std::vector<Ressource> Element::getRessources() const {

	return m_ressources;

}

sf::Vertex* Element::getQuadBas() const {

	return m_quad_bas;

}

sf::Vertex* Element::getQuadHaut() const {

	return m_quad_haut;

}

bool Element::containResource( TypeRessource t ) const
{
    for(int i = 0; i < m_ressources.size(); ++i) {
        if(m_ressources[i].type == t) {
            return true;
        }
    }

    return false;
}

int Element::getQuantityOf( TypeRessource t ) const
{
    for(int i = 0; i < m_ressources.size(); ++i) {
        if(m_ressources[i].type == t) {
            return m_ressources[i].quantite;
        }
    }

    return 0;
}


