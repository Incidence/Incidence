/*******************************************************************
** Description :                                                  **
** Fichier d'en-tête de la classe Carte, s'occupant de la gestion **
** complète de la carte (sol et objets) et des affichages.        **
**                                                                **
** Création : 04/03/14                                            **
** Modification : 07/03/14                                        **
*******************************************************************/

#ifndef CARTE_HPP
#define CARTE_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "Sol.hpp"
#include "Element.hpp"
#include "TileSet.hpp"

class Carte {

	private:

		TileSet m_tileset;
		sf::Vector2u m_dimensions; // { x = largeur , y = hauteur }
		std::vector<Sol*> m_sols;
		std::vector<Element*> m_elements;
		sf::VertexArray m_VertexSols;
		sf::VertexArray m_VertexElementsBas;
		sf::VertexArray m_VertexElementsHaut;

	public:

		Carte(TileSet tileset, sf::Vector2u dimensions);
		~Carte();

		void setTileSet(TileSet tileset);
		sf::Vector2u getDimensions() const;
		void setDimensions(sf::Vector2u dimensions);

		int getX(sf::Vector2f position) const;
		int getY(sf::Vector2f position) const;
		sf::Vector2i getXY(sf::Vector2f position) const;
		int getId(sf::Vector2i position) const;

		Sol * getSol(sf::Vector2i position) const;
		Element * getElement(sf::Vector2i position) const;

		void changerSol(int type, sf::Vector2i position);
		void ajouterElement(int type, sf::Vector2i position);
		void supprimerElement(sf::Vector2i position);

		void generate();

		bool charger(std::string path);
		bool sauver(std::string path) const;

		void drawSols(sf::RenderTarget& target) const;
		void drawElementsBas(sf::RenderTarget& target) const;
		void drawElementsHaut(sf::RenderTarget& target) const;

        bool isPassable( sf::Vector2i pos ) const;
        std::list< sf::Vector2f > findWay( sf::Vector2f from, sf::Vector2f to, int entityWidth );
};

#endif
