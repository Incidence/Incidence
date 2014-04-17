/*******************************************************************
** Description :                                                  **
** Fichier d'en-tête de la classe TileSet, contenant les textures **
** des cases de la carte (sol et objets).                         **
*******************************************************************/

#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "ground.hpp"
#include "element.hpp"

class TileSet {

	private:

		sf::Texture m_tileset;
		sf::Vector2u m_tilesize;
		int m_groundCount;
		int m_elementCount;
		std::vector<Ground> m_grounds;
		std::vector<Element> m_elements;
		sf::Vector2u m_ashes;


	public:

		TileSet();
		TileSet(const std::string path);
		~TileSet();

		const sf::Texture* getTileset() const;
		const sf::Vector2u getAshes() const;
		sf::Vector2u getTileSize() const;
		int getGroundCount() const;
		int getElementCount() const;

		Ground* getGround(int type, bool* tileBorders);
		Element* getElement(int type, int groundType);
		
		std::vector<int> getGroundsByBehavior(TileBehavior behavior) const;
		std::vector<int> getElementsByBehavior(TileBehavior behavior) const;

		bool load(const std::string& path);
		
		void TEST();

};

#endif
