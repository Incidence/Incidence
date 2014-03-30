#ifndef _BUILDING_
#define _BUILDING_

class Building : public Harvestable
{

public :
    Building( void );
    ~Building( void );

    void load( std::string path );

    void draw( sf::RenderTarget & target );
    void action( Entity * e );

    virtual bool isHarvestable( void );
    virtual void havested( void );

private :
    Animation m_animation;

    sf::Vector2i m_position; // BAS-GAUCHE
    sf::Vector2i m_size; // Pour collision, vers HAUT-DROITE

    std::list< RessourceType > m_ressourceStorage;

    unsigned int m_productDay;

    unsigned int m_currentPrepare;
    bool m_alreadyPrepare;

    friend class TileMap;

};

#endif // _BUILDING_
