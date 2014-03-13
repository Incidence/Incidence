/*********************************************************************
** Description :                                                    **
** Fichier d'en-tête de la classe TileMap, s'occupant de la gestion **
** complète de la carte (sol et objets) et des affichages.          **
*********************************************************************/

#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "ground.hpp"
#include "element.hpp"
#include "tileset.hpp"

class TileMap {

	private:

		TileSet m_tileset;
		sf::Vector2u m_dimensions; // { x = width , y = height }
		std::vector<Ground*> m_grounds;
		std::vector<Element*> m_elements;
		sf::VertexArray m_VertexGrounds;
		sf::VertexArray m_VertexElementsDown;
		sf::VertexArray m_VertexElementsUp;

		std::list<sf::Vector2i> m_way;
		std::list<sf::Vector2f> m_cut;

	public:

		TileMap(TileSet tileset, sf::Vector2u dimensions);
		~TileMap();

		void setTileSet(TileSet tileset);
		sf::Vector2u getDimensions() const;
		void setDimensions(sf::Vector2u dimensions);

		int getX(sf::Vector2f position) const;
		int getY(sf::Vector2f position) const;
		sf::Vector2i getXY(sf::Vector2f position) const;
		sf::Vector2f getAbs(sf::Vector2i position) const;
		int getId(sf::Vector2i position) const;
		int getId(sf::Vector2f position) const;

		Ground * getGround(sf::Vector2i position) const;
		Element * getElement(sf::Vector2i position) const;

		void changeGround(int type, sf::Vector2i position);
		void addElement(int type, sf::Vector2i position);
		void removeElement(sf::Vector2i position);

		void generate();

		bool load(std::string path);
		bool save(std::string path) const;

		void drawGrounds(sf::RenderTarget& target) const;
		void drawElementsDown(sf::RenderTarget& target) const;
		void drawElementsUp(sf::RenderTarget& target);

		bool isPassable( sf::Vector2i pos ) const;
		std::list< sf::Vector2f > findWay( sf::Vector2f from, sf::Vector2f to, int entityWidth );
        bool isShortcut(sf::Vector2f u, sf::Vector2f v);
};

#endif
