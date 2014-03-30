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
    for(std::list< Node * >::iterator it = nodeList.begin(); it != nodeList.end(); ++it, ++pos)
    {
        if( (*it)->dist > n->dist ) {
            break;
        }
    }
    nodeList.insert(pos, n);

}

bool containNode( std::list< Node * > & nodeList, Node * n )
{
    for(std::list< Node * >::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
    {
        if( (*it)->pos.x == n->pos.x && (*it)->pos.y == n->pos.y ) {
            return true;
        }
    }

    return false;
}

void addNeighbor( std::list< Node * > & open, std::list< Node * > & close, Node * n, TileMap * tilemap, sf::Vector2i to, sf::Vector2i from, int perception )
{
    Node * tmp = NULL;
    bool l = false, r = false, u = false, d = false;
    bool bClose;

    // Right
    tmp = new Node;
    sf::Vector2i neighborPos = n->pos;
    neighborPos.x += 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    r = tilemap->isPassable(neighborPos);
    if(distance(from, tmp->pos) <= perception && (r || neighborPos == to) && ! containNode(open, tmp) && (bClose = ! containNode(close, tmp))) {
        tmp->dist = distance(to, tmp->pos);
        tmp->height = n->height + 1; // Une case de plus
        tmp->distTotal = tmp->dist + tmp->height;

        addNode(open, tmp);
    } else {
        if(bClose) {
            delete tmp;
        } else {
            close.push_back(tmp);
        }
    }

    // Left
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x -= 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    l = tilemap->isPassable(neighborPos);
    if(distance(from, tmp->pos) <= perception && (l || neighborPos == to) && ! containNode(open, tmp) && (bClose = ! containNode(close, tmp))) {
        tmp->dist = distance(to, tmp->pos);
        tmp->height = n->height + 1; // Une case de plus
        tmp->distTotal = tmp->dist + tmp->height;

        addNode(open, tmp);
    } else {
        if(bClose) {
            delete tmp;
        } else {
            close.push_back(tmp);
        }
    }

    // Up
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.y += 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    u = tilemap->isPassable(neighborPos);
    if(distance(from, tmp->pos) <= perception && (u || neighborPos == to) && ! containNode(open, tmp) && (bClose = ! containNode(close, tmp))) {
        tmp->dist = distance(to, tmp->pos);
        tmp->height = n->height + 1; // Une case de plus
        tmp->distTotal = tmp->dist + tmp->height;

        addNode(open, tmp);
        u = true;
    } else {
        if(bClose) {
            delete tmp;
        } else {
            close.push_back(tmp);
        }
    }

    // Down
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.y -= 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    d = tilemap->isPassable(neighborPos);
    if(distance(from, tmp->pos) <= perception && (d || neighborPos == to) && ! containNode(open, tmp) && (bClose = ! containNode(close, tmp))) {
        tmp->dist = distance(to, tmp->pos);
        tmp->height = n->height + 1; // Une case de plus
        tmp->distTotal = tmp->dist + tmp->height;

        addNode(open, tmp);
        d = true;
    } else {
        if(bClose) {
            delete tmp;
        } else {
            close.push_back(tmp);
        }
    }

    // Up-Droite
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x += 1;
    neighborPos.y += 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    if(distance(from, tmp->pos) <= perception && u && r && (tilemap->isPassable(neighborPos)) && ! containNode(open, tmp) && (bClose = ! containNode(close, tmp))) {
        tmp->dist = distance(to, tmp->pos);
        tmp->height = n->height + 1.14; // Une case de plus
        tmp->distTotal = tmp->dist + tmp->height;

        addNode(open, tmp);
    } else {
        if(bClose) {
            delete tmp;
        } else {
            close.push_back(tmp);
        }
    }

    // Up-Gauche
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x -= 1;
    neighborPos.y += 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    if(distance(from, tmp->pos) <= perception && u && l && (tilemap->isPassable(neighborPos)) && ! containNode(open, tmp) && (bClose = ! containNode(close, tmp))) {
        tmp->dist = distance(to, tmp->pos);
        tmp->height = n->height + 1.14; // Une case de plus
        tmp->distTotal = tmp->dist + tmp->height;

        addNode(open, tmp);
    } else {
        if(bClose) {
            delete tmp;
        } else {
            close.push_back(tmp);
        }
    }

    // Down-Droite
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x += 1;
    neighborPos.y -= 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    if(distance(from, tmp->pos) <= perception && d && r && (tilemap->isPassable(neighborPos)) && ! containNode(open, tmp) && (bClose = ! containNode(close, tmp))) {
        tmp->dist = distance(to, tmp->pos);
        tmp->height = n->height + 1.14; // Une case de plus
        tmp->distTotal = tmp->dist + tmp->height;

        addNode(open, tmp);
    } else {
        if(bClose) {
            delete tmp;
        } else {
            close.push_back(tmp);
        }
    }

    // Down-Gauche
    tmp = new Node;
    neighborPos = n->pos;
    neighborPos.x -= 1;
    neighborPos.y -= 1;

    tmp->pos = neighborPos;
    tmp->parent = n;

    if(distance(from, tmp->pos) <= perception && d && l && (tilemap->isPassable(neighborPos)) && ! containNode(open, tmp) && (bClose = ! containNode(close, tmp))) {
        tmp->dist = distance(to, tmp->pos);
        tmp->height = n->height + 1.14; // Une case de plus
        tmp->distTotal = tmp->dist + tmp->height;

        addNode(open, tmp);
    } else {
        if(bClose) {
            delete tmp;
        } else {
            close.push_back(tmp);
        }
    }


}

std::list< sf::Vector2i > pathfinding( TileMap * tilemap, sf::Vector2i from, sf::Vector2i to, int entityWidth, int perception)
{
    std::list< Node * > openList, closeList;

    Node * current = new Node;
    current->pos = from;
    current->parent = NULL;
    current->dist = distance(from, to);
    current->distTotal = distance(from, to);
    current->height = 0;

    openList.push_front(current);

    while( !openList.empty() && current->pos != to ) {
        /// TODO : Ajouter : Si chemin direct, créér le node correspondant et break;

        removeNode( openList, closeList, current );
        addNeighbor( openList, closeList, current, tilemap, to, from, perception );

        current = *(openList.begin()); // Liste ordonné donc begin() tjs le plus petit

        //std::cout << "hello" << std::endl;
    }

    std::list< sf::Vector2i > way;
    if( !openList.empty() ) {
        way.push_front(current->pos);
        while(current->parent) {
            current = current->parent;
            way.push_front(current->pos); /// TODO : Passer la position en pixel
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
