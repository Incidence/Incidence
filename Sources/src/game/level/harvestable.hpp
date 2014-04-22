#ifndef _HARVESTABLE_
#define _HARVESTABLE_

#include <SFML/Graphics.hpp>
#include "ressource.hpp"

class Harvestable
{

public :
    Harvestable( void );
    Harvestable( float pickingTime, std::vector< Ressource > ressources );
    ~Harvestable( void );

    float getPickingTime( void ) const;
    std::vector<Ressource> getRessources( void ) const;
    bool containRessource( RessourceType t ) const;
    int getQuantityOf( RessourceType t ) const;

    virtual bool isHarvestable( void ) = 0;
    virtual void havested( void ) = 0; // Que faire quand on est recolté

protected :

    float m_pickingTime;
    std::vector<Ressource> m_ressources;

};

#endif // _HARVESTABLE_
