/*****************************************************************
** Description :                                                **
** Fichier d'en-tête de la classe Element, définissant une      **
** unique case élément de la carte. Ne contient aucune texture. **
*****************************************************************/

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

#include "harvestable.hpp"
#include "ressource.hpp"

class Element : public Harvestable {

	private:

		int m_type;
		int m_groundType;
		std::string m_name;
		TileBehavior m_behavior;
		bool m_passable;
		sf::Vertex* m_quad_down;
		sf::Vertex* m_quad_up;

	public:

		Element(int type, int groundType, std::string name, TileBehavior behavior, bool passable, float pickingTime, std::vector<Ressource> ressources, sf::Vertex* quad_down, sf::Vertex* quad_up);
		virtual ~Element();

		int getType() const;
		int getGroundType() const;
		std::string getName() const;
		TileBehavior getBehavior() const;
		bool isPassable() const;
		sf::Vertex* getQuadDown() const;
		sf::Vertex* getQuadUp() const;

        virtual bool isHarvestable( void );
        virtual void havested( void );

};

#endif
