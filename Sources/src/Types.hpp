/*******************************************************
** Description :                                      **
** Fichier de définition des différents types de case **
** (sol, objets et entités) et de ressource.          **
**                                                    **
** Création : 04/03/14                                **
** Modification : 05/03/14                            **
*******************************************************/

#ifndef TYPES_HPP
#define TYPES_HPP

// Type vide
#define AUCUN -1


#define OFFSET_SOL 0
// Types de sol
#define TERRE_ARIDE 0
#define TERRE_DEFAUT 1
#define TERRE_FERTILE 2
#define TERRE_INNONDEE 3
#define EAU 4
#define FALAISE 5
#define CHAMP 6


#define OFFSET_OBJET 10
// Types d'objet
#define ARBRE_HAUT 10
#define ARBRE_BAS 11
#define ARBRE_FRUITIER_HAUT 12
#define ARBRE_FRUITIER_BAS 13
#define BUISSON 14
#define ROCHER 15


#define OFFSET_ENTITE 20
// Types d'entités
#define CITOYEN 20


#define OFFSET_RESSOURCE 30
// Types de ressources
#define BOIS 30
#define PIERRE 31
#define NOURRITURE 32

#endif
