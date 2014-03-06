/***************************************************
** Description :                                  **
** Fichier de définission des types de ressource  **
** et de la structure définissant une ressource.  **
**                                                **
** Création : 06/03/14                            **
** Modification : 06/03/14                        **
***************************************************/

#ifndef RESSOURCE_HPP
#define RESSOURCE_HPP

typedef enum TypeRessource {
	BOIS, PIERRE, NOURRITURE
} TypeRessource;

typedef struct Ressource {
	
	TypeRessource type;
	int quantite;
	
} Ressource;

#endif
