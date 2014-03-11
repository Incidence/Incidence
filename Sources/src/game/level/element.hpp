/*****************************************************************
** Description :                                                **
** Fichier d'en-tête de la classe Element, définissant une      **
** unique case élément de la carte. Ne contient aucune texture. **
**                                                              **
** Création : 06/03/14                                          **
** Modification : 07/03/14                                      **
*****************************************************************/

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>
#include "ressource.hpp"

class Element {

	private:

		int m_type;
		int m_groundType;
		std::string m_name;
		TileBehavior m_behavior;
		bool m_passable;
		sf::Time m_pickingTime;
		std::vector<Ressource> m_ressources;
		sf::Vertex* m_quad_down;
		sf::Vertex* m_quad_up;


	public:

		Element(int type, int groundType, std::string name, TileBehavior behavior, bool passable, sf::Time pickingTime, std::vector<Ressource> ressources, sf::Vertex* quad_down, sf::Vertex* quad_up);
		~Element();

		int getType() const;
		int getGroundType() const;
		std::string getName() const;
		TileBehavior getBehavior() const;
		bool isPassable() const;
		sf::Time getPickingTime() const;
		std::vector<Ressource> getRessources() const;
		sf::Vertex* getQuadDown() const;
		sf::Vertex* getQuadUp() const;

		bool containResource( RessourceType t ) const;
		int getQuantityOf( RessourceType t ) const;

};

#endif
