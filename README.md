Incidence
=========

Incidence est un god game basé sur une structure multi-agent.


Installation
============

Sous Linux :

 - installer la bibliothèque SFML 2.1 : http://www.sfml-dev.org/download.php.
 
 - installer lua 5.2.1 : récupérez la version compatible avec votre système à http://sourceforge.net/projects/luabinaries/files/5.2.1/Linux%20Libraries/
 
 Copiez le contenu du dossier include/ récupéré avec les fichiers lua dans /usr/include/.
 Copiez également les deux fichiers liblua52.a et liblua52.so dans le dossier /usr/lib/

Ensuite, il suffit de taper en ligne de commande depuis le répertoire principal de votre copie locale :

$ cd Sources/ && make

$ cd _build/ && ./Incidence
