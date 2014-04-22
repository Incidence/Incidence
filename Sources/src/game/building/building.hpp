#ifndef _BUILDING_
#define _BUILDING_

// FAIRE LES INCLUDES

class Building : public Harvestable
{

public :
    Building( void );
    Building( sf::Vector2i & position,const std::string path );
    ~Building( void );
    
    void setPosition( int x,int y );
    void setPosition( const sf::Vector2i & position );

    void load( const std::string path );

    void drawTop( sf::RenderTarget & target );
    void drawBottom( sf::RenderTarget & target );
    void action( Entity * e );

    virtual bool isHarvestable( void );
    virtual void havested( void );

private :
    Animation m_animation;

    sf::Vector2i m_position; // BAS-GAUCHE
    sf::Vector2i m_size; // Pour collision, vers HAUT-DROITE

    std::vector< RessourceType > m_ressourceStorage;

    unsigned int m_productDay;

    unsigned int m_currentPrepare;
    bool m_alreadyPrepare;

    friend class TileMap;

};

#endif // _BUILDING_
