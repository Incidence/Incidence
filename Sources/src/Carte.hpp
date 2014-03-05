/*******************************************************************
** Description :                                                  **
** Fichier d'en-tête de la classe Carte, s'occupant de la gestion **
** complète de la carte (sol et objets) et des affichages.        **
**                                                                **
** Création : 04/03/14                                            **
** Modification : 05/03/14                                        **
*******************************************************************/

#ifndef CARTE_HPP
#define CARTE_HPP

#include <SFML/Graphics.hpp>
#include "TileSet.hpp"
#include "Case.hpp"

class Carte : public sf::Drawable, public sf::Transformable {

	private:

		TileSet m_tileset;
		sf::Vector2u m_dimensions;
		std::vector<Case> m_cases;
		sf::VertexArray m_sol;
		sf::VertexArray m_objets;
		sf::VertexArray m_entites;

	public:

		Carte();
		Carte(TileSet tileset);
		Carte(TileSet tileset, sf::Vector2u dimensions);
		~Carte();

		virtual sf::Vector2u getDimensions();
		virtual void setDimensions(sf::Vector2u dimensions);
		virtual void setTileSet(TileSet tileset);

		virtual Case getSol(sf::Vector2f position);
		virtual Case getObjet(sf::Vector2f position);
		virtual Case getEntite(sf::Vector2f position);

		virtual void ajouterObjet(int type, sf::Vector2f position);
		virtual void supprimerObjet(sf::Vector2f position);
		virtual void changerSol(int type, sf::Vector2f position);
		virtual void ajouterEntite(int type, sf::Vector2f position);
		virtual void supprimerEntite(sf::Vector2f position);

		virtual void loadSol(const int* sol);
		virtual void loadObjets(const int* objets);
		virtual void loadEntites(const int* entites);

		virtual void generate();

		virtual bool charger(std::string path);
		virtual bool sauver(std::string path);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:

		virtual void drawSol(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawObjets(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawEntites(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
