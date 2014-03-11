/***************************************************************
** Description :                                              **
** Fichier d'en-tête de la classe Ground, définissant une unique **
** case du sol de la carte. Ne contient aucune texture.       **
**                                                            **
** Création : 06/03/14                                        **
** Modification : 07/03/14                                    **
***************************************************************/

#ifndef GROUND_HPP
#define GROUND_HPP

#include <SFML/Graphics.hpp>

class Ground {

	private:

		int m_type;
		std::string m_name;
		bool m_passable;
		std::vector<int> m_borders;
		bool* m_tileBorders;
		sf::Vertex* m_quad;


	public:

		Ground(const int type, const std::string name, const bool passable, std::vector<int> borders, bool* tileBorders, sf::Vertex* quad);
		~Ground();

		int getType() const ;
		std::string getName() const;
		bool isPassable() const;
		std::vector<int> getBorders() const;
		bool* getTileBorders() const;
		sf::Vertex* getQuad() const;
		
		bool hasTileBorderWith(int type) const;

};

#endif
