/*******************************************************************
** Description :                                                  **
** Fichier d'en-tête de la classe TileSet, contenant les textures **
** des cases de la carte (sol, objets et entités).                **
**                                                                **
** Création : 04/03/14                                            **
** Modification : 06/03/14                                        **
*******************************************************************/

#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
#include "Sol.hpp"
#include "Element.hpp"

class TileSet {

	private:

		sf::Texture m_tileset;
		sf::Vector2u m_tilesize;
		std::vector<Sol> m_sols;
		std::vector<Element> m_elements;


	public:

		TileSet();
		TileSet(const std::string path);
		~TileSet();

		const sf::Texture* getTileset() const;
		sf::Vector2u getTileSize();

		Sol* getSol(int type, bool* bordures);
		Element* getElement(int type, int typeSol);

		bool load(const std::string& path);
		
		void TEST();

};

#endif
