/*******************************************************************
** Description :                                                  **
** Fichier d'en-tête de la classe Case, définissant une unique    **
** case de la carte (sol ou objet). Ne contient aucune texture.   **
**                                                                **
** Création : 04/03/14                                            **
** Modification : 05/03/14                                        **
*******************************************************************/

#ifndef CASE_HPP
#define CASE_HPP

#include <SFML/Graphics.hpp>
#include "Types.hpp"

class Case {

	private:

		int m_type;
		sf::Time m_tempsRecolte;
		int m_ressources[2];
		bool m_franchissable;


	public:

		Case();
		Case(int type);
		~Case();

		virtual int getType() const ;
		virtual void setType(int type);
		virtual sf::Time getTempsRecolte();
		virtual int getRessource(int i);
		virtual bool getFranchissable();

	private:

		virtual void setTempsRecolte();
		virtual void setRessources();
		virtual void setFranchissable();

};

#endif
