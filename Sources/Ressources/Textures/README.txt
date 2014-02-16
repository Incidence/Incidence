=========================================================================
Format de nom pour les sprites :

<type de base>_<G><B><D><H>.png


Type de base : type d'origine de la case
Gauche (G) : 1 si type différent à gauche, 0 sinon.
Bas (B) : 1 si type différent en bas, 0 sinon.
Droite (D) : 1 si type différent à droite, 0 sinon.
Haut (H) : 1 si type différent en haut, 0 sinon.

=========================================================================

Exemples : 

 - case de type fertile, avec à gauche et en haut un type fertile, 
en bas et à droite un type défaut 
-> "terre-fertile_0110.png"

 - case de type aride avec un type aride tout autour (sans rebord)
-> "terre-aride_0000.png"
