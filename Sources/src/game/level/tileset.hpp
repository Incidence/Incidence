/*******************************************************************
** Description :                                                  **
** Fichier d'en-tête de la classe TileSet, contenant les textures **
** des cases de la carte (sol et objets).                         **
*******************************************************************/

#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
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


	public:

		TileSet();
		TileSet(const std::string path);
		~TileSet();

		const sf::Texture* getTileset() const;
		sf::Vector2u getTileSize() const;
		int getGroundCount() const;
		int getElementCount() const;

		Ground* getGround(int type, bool* borders);
		Element* getElement(int type, int groundType);

		bool load(const std::string& path);
		
		void TEST();

};

#endif
