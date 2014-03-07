/*******************************************************************
** Description :                                                  **
** Fichier d'en-tête de la classe Carte, s'occupant de la gestion **
** complète de la carte (sol et objets) et des affichages.        **
**                                                                **
** Création : 04/03/14                                            **
** Modification : 06/03/14                                        **
*******************************************************************/

#ifndef CARTE_HPP
#define CARTE_HPP

#include <SFML/Graphics.hpp>
#include "Sol.hpp"
#include "Element.hpp"
#include "TileSet.hpp"

class Carte {

	private:

		TileSet m_tileset;
		sf::Vector2u m_dimensions;
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

		Sol* getSol(sf::Vector2f position) const;
		Element* getElement(sf::Vector2f position) const;

		void changerSol(int type, sf::Vector2f position);
		void ajouterElement(int type, sf::Vector2f position);
		void supprimerElement(sf::Vector2f position);

		void generate();

		bool charger(std::string path);
		bool sauver(std::string path) const;

		void drawSols(sf::RenderTarget& target) const;
		void drawElementsBas(sf::RenderTarget& target) const;
		void drawElementsHaut(sf::RenderTarget& target) const;

};

#endif
