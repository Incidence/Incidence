/*********************************************************************
** Description :                                                    **
** Fichier d'en-tête de la classe TileMap, s'occupant de la gestion **
** complète de la carte (sol et objets) et des affichages.          **
*********************************************************************/

#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <queue>

#include "ground.hpp"
#include "element.hpp"
#include "tileset.hpp"

template<typename T> bool contains(std::vector<T> vec, T val) {
	for(unsigned int i(0);i<vec.size();++i) { if(vec[i] == val) { return true; } } return false;
}

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

	public:

		TileMap(TileSet tileset, sf::Vector2u dimensions);
		~TileMap();

		TileSet* getTileSet();
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
		int getGroundCost(int type, sf::Vector2i position);
		int getElementCost(int type, sf::Vector2i position);
		Harvestable * getHarvestable(sf::Vector2i position) const;

		int areCompatibleGrounds(sf::Vector2i position_1, sf::Vector2i position_2);
		int areCompatibleGrounds(int type_1, int type_2);

		void changeGround(int type, sf::Vector2i position);
		void updateBorders(sf::Vector2i position);
		void updateAllBorders(sf::Vector2i position);
		void addElement(int type, sf::Vector2i position);
		void removeElement(sf::Vector2i position);
		void burnElement(sf::Vector2i position);

		int bestLinkType(int startType, int goalType);
		void userSetGround(int type, sf::Vector2i position);
		void freePlace(sf::Vector2i position);

		void generate();

		bool load(std::string path);
		bool save(std::string path) const;

		void drawGrounds(sf::RenderTarget& target) const;
		void drawElementsDown(sf::RenderTarget& target) const;
		void drawElementsUp(sf::RenderTarget& target);

		bool isPassable( sf::Vector2i pos ) const;
		std::list< sf::Vector2f > findWay( sf::Vector2f from, sf::Vector2f to, int entityWidth, int perception );
        bool isShortcut(sf::Vector2f u, sf::Vector2f v);

		std::list<sf::Vector2f> m_cut;

    friend class Game;
};

#endif
