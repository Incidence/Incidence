#include "pathfinding.hpp"

#include "../../engine/foo.hpp"

void removeNode( std::list< Node * > & open, std::list< Node * > & close, Node * n )
{
    open.remove(n);
    close.push_back(n);
}

void addNode( std::list< Node * > & nodeList, Node * n )
{
    std::list< Node * >::iterator pos = nodeList.begin();
    for(std::list< Node * >::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
    {
        if( (*it)->distTotal > n->distTotal ) {
            break;
        }

        pos = it;
    }

    nodeList.insert(pos, n);
}

bool containNode( std::list< Node * > & nodeList, Node * n )
{
    for(std::list< Node * >::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
    {
        if( (*it)->pos == n->pos ) {
            return true;
        }
    }

    return false;
}

void addNeighbor( std::list< Node * > & open, std::list< Node * > & close, Node * n, Carte * carte, sf::Vector2i from )
{
    Node * tmp = NULL;
    bool l = false, r = false, u = false, d = false;

    // Right
    tmp = new Node;
    sf::Vector2i neighborPos = n->pos;
    neighborPos.x += 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    r = carte->isPassable(neighborPos);
    if( (r || neighborPos == from) && ! containNode(open, tmp) && ! containNode(close, tmp)) {
        tmp->dist = distance(from, tmp->pos);
        tmp->height = n->height + 1; // Une case de plus
        tmp->distTotal = n->distTotal + tmp->height;

        addNode(open, tmp);
    } else {
        delete tmp;
    }

    // Left
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x -= 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    l = carte->isPassable(neighborPos);
    if( (l || neighborPos == from) && ! containNode(open, tmp) && ! containNode(close, tmp)) {
        tmp->dist = distance(from, tmp->pos);
        tmp->height = n->height + 1; // Une case de plus
        tmp->distTotal = n->distTotal + tmp->height;

        addNode(open, tmp);
    } else {
        delete tmp;
    }

    // Up
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.y += 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    u = carte->isPassable(neighborPos);
    if( (u || neighborPos == from) && ! containNode(open, tmp) && ! containNode(close, tmp)) {
        tmp->dist = distance(from, tmp->pos);
        tmp->height = n->height + 1; // Une case de plus
        tmp->distTotal = n->distTotal + tmp->height;

        addNode(open, tmp);
        u = true;
    } else {
        delete tmp;
    }

    // Down
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.y -= 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    d = carte->isPassable(neighborPos);
    if( (d || neighborPos == from) && ! containNode(open, tmp) && ! containNode(close, tmp)) {
        tmp->dist = distance(from, tmp->pos);
        tmp->height = n->height + 1; // Une case de plus
        tmp->distTotal = n->distTotal + tmp->height;

        addNode(open, tmp);
        d = true;
    } else {
        delete tmp;
    }

    // Haut-Droite
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x += 1;
    neighborPos.y += 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    if(u && r && (carte->isPassable(neighborPos) ||  neighborPos == from) && ! containNode(open, tmp) && ! containNode(close, tmp)) {
        tmp->dist = distance(from, tmp->pos);
        tmp->height = n->height + 1.14; // Une case de plus
        tmp->distTotal = n->distTotal + tmp->height;

        addNode(open, tmp);
    } else {
        delete tmp;
    }

    // Haut-Gauche
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x += 1;
    neighborPos.y -= 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    if(u && l && (carte->isPassable(neighborPos) ||  neighborPos == from) && ! containNode(open, tmp) && ! containNode(close, tmp)) {
        tmp->dist = distance(from, tmp->pos);
        tmp->height = n->height + 1.14; // Une case de plus
        tmp->distTotal = n->distTotal + tmp->height;

        addNode(open, tmp);
    } else {
        delete tmp;
    }

    // Bas-Droite
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x -= 1;
    neighborPos.y += 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    if(d && r && (carte->isPassable(neighborPos) ||  neighborPos == from) && ! containNode(open, tmp) && ! containNode(close, tmp)) {
        tmp->dist = distance(from, tmp->pos);
        tmp->height = n->height + 1.14; // Une case de plus
        tmp->distTotal = n->distTotal + tmp->height;

        addNode(open, tmp);
    } else {
        delete tmp;
    }

    // Bas-Gauche
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x -= 1;
    neighborPos.y -= 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    if(d && l && (carte->isPassable(neighborPos) ||  neighborPos == from) && ! containNode(open, tmp) && ! containNode(close, tmp)) {
        tmp->dist = distance(from, tmp->pos);
        tmp->height = n->height + 1.14; // Une case de plus
        tmp->distTotal = n->distTotal + tmp->height;

        addNode(open, tmp);
    } else {
        delete tmp;
    }


}

std::list< sf::Vector2i > pathfinding( Carte * carte, sf::Vector2i from, sf::Vector2i to, int entityWidth)
{
    std::list< Node * > openList, closeList;

    Node * current = new Node;
    current->pos = to;
    current->parent = NULL;
    current->dist = distance(from, to);
    current->distTotal = distance(from, to);
    current->height = 0;

    openList.push_front(current);

    while( !openList.empty() && current->pos != from ) /// ADD : AND current->height < NB_MAX_CASE_A_PARCOURIR
    {
        /// TODO : Ajouter : Si chemin direct, créér le node correspondant et break;

        removeNode( openList, closeList, current );
        addNeighbor( openList, closeList, current, carte, from );

        current = *(openList.begin()); // Liste ordonné donc begin() tjs le plus petit
    }

    std::list< sf::Vector2i > way;

    if( !openList.empty() ) { /// ADD : AND current->height < NB_MAX_CASE_A_PARCOURIR
        while(current->parent) {
            current = current->parent;
            way.push_back(current->pos); /// TODO : Passer la position en pixel
        }
    }

    for(std::list< Node * >::iterator it = openList.begin(); it != openList.end(); ++it) {
        delete (*it);
    }
    for(std::list< Node * >::iterator it = closeList.begin(); it != closeList.end(); ++it)  {
        delete (*it);
    }

    return way;
}



























