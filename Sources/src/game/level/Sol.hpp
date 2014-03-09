/***************************************************************
** Description :                                              **
** Fichier d'en-tête de la classe Sol, définissant une unique **
** case du sol de la carte. Ne contient aucune texture.       **
**                                                            **
** Création : 06/03/14                                        **
** Modification : 07/03/14                                    **
***************************************************************/

#ifndef SOL_HPP
#define SOL_HPP

#include <SFML/Graphics.hpp>

class Sol {

	private:

		int m_type;
		std::string m_nom;
		bool m_franchissable;
		std::vector<int> m_bords;
		bool* m_bordures;
		sf::Vertex* m_quad;


	public:

		Sol(const int type, const std::string nom, const bool franchissable, std::vector<int> bords, bool* bordures, sf::Vertex* quad);
		~Sol();

		int getType() const ;
		std::string getNom() const;
		bool isFranchissable() const;
		std::vector<int> getBords() const;
		bool* getBordures() const;
		sf::Vertex* getQuad() const;
		
		bool isBord(int type) const;

};

#endif
