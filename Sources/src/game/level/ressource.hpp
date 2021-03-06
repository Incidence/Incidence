/***************************************************
** Description :                                  **
** Fichier de définission des types de ressource  **
** et de la structure définissant une ressource.  **
***************************************************/

#ifndef RESSOURCE_HPP
#define RESSOURCE_HPP

typedef enum RessourceType {
	WOOD,
	STONE,
	FOOD,
	NOTHING
} RessourceType;

typedef struct Ressource {

	RessourceType type;
	int quantity;

} Ressource;

typedef enum TileBehavior {
	DEFAULT,
	FLUID,
	CLIFF,
	FOREST
} TileBehavior;

#endif
