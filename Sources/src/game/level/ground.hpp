/******************************************************************
** Description :                                                 **
** Fichier d'en-tête de la classe Ground, définissant une unique **
** case du sol de la carte. Ne contient aucune texture.          **
******************************************************************/

#ifndef GROUND_HPP
#define GROUND_HPP

#include <SFML/Graphics.hpp>
#include "ressource.hpp"

class Ground {

	private:

		int m_type;
		std::string m_name;
		TileBehavior m_behavior;
		bool m_passable;
		std::vector<int> m_borders;
		bool* m_tileBorders;
		sf::Vertex* m_quad;
		int m_cost;


	public:

		Ground(const int type, const std::string name, const TileBehavior behavior, const bool passable, std::vector<int> borders, bool* tileBorders, sf::Vertex* quad, int cost);
		~Ground();

		int getType() const ;
		std::string getName() const;
		TileBehavior getBehavior() const;
		bool isPassable() const;
		std::vector<int> getBorders() const;
		bool* getTileBorders() const;
		sf::Vertex* getQuad() const;
		int getCost() const;
		
		bool hasBorderWith(int type) const;

};

#endif
