/*******************************************************************
** Description :                                                  **
** Fichier d'en-tête de la classe TileSet, contenant les textures **
** des cases de la carte (sol, objets et entités).                **
**                                                                **
** Création : 04/03/14                                            **
** Modification : 05/03/14                                        **
*******************************************************************/

#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
#include "Types.hpp"

class TileSet {

	private:

		sf::Texture m_tileset_sol;
		sf::Texture m_tileset_obj;
		sf::Texture m_tileset_ent;
		sf::Vector2u m_tilesize;


	public:

		TileSet();
		TileSet(sf::Vector2u tilesize);
		~TileSet();

		virtual sf::Vector2u getTileSize();
		virtual void setTileSize(sf::Vector2u tilesize);

		virtual sf::Texture getTile(int type, int colonne);

		virtual bool loadTilesetSol(const std::string& path);
		virtual bool loadTilesetObj(const std::string& path);
		virtual bool loadTilesetEnt(const std::string& path);

};

#endif
