#include "harvestable.hpp"


Harvestable::Harvestable( float pickingTime, std::vector<Ressource> ressources )
{
	m_pickingTime = pickingTime;
	m_ressources = ressources;
}

Harvestable::~Harvestable( void )
{

}

float Harvestable::getPickingTime() const
{
	return m_pickingTime;
}

std::vector<Ressource> Harvestable::getRessources() const
{
	return m_ressources;
}

bool Harvestable::containRessource( RessourceType t ) const
{
    for(unsigned int i = 0; i < m_ressources.size(); ++i) {
        if(m_ressources[i].type == t) {
            return true;
        }
    }

    return false;
}

int Harvestable::getQuantityOf( RessourceType t ) const
{
    for(unsigned int i = 0; i < m_ressources.size(); ++i) {
        if(m_ressources[i].type == t) {
            return m_ressources[i].quantity;
        }
    }

    return 0;
}
