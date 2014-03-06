/*****************************************************************
** Description :                                                **
** Fichier d'en-tête de la classe Element, définissant une      **
** unique case élément de la carte. Ne contient aucune texture. **
**                                                              **
** Création : 06/03/14                                          **
** Modification : 06/03/14                                      **
*****************************************************************/

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>
#include "Ressource.hpp"

class Element {

	private:

		int m_type;
		int m_typeSol;
		std::string m_nom;
		bool m_franchissable;
		sf::Time m_tempsRecolte;
		std::vector<Ressource> m_ressources;
		sf::Vertex* m_quad_bas;
		sf::Vertex* m_quad_haut;


	public:

		Element(int type, int typeSol, std::string nom, bool franchissable, sf::Time tempsRecolte, std::vector<Ressource> ressources, sf::Vertex* quad_bas, sf::Vertex* quad_haut);
		~Element();

		int getType() const;
		int getTypeSol() const;
		std::string getNom() const;
		bool isFranchissable() const;
		sf::Time getTempsRecolte() const;
		std::vector<Ressource> getRessources() const;

};

#endif
