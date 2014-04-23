#include "building.hpp"

#include <fstream>
#include "../../engine/animation.hpp"

Building::Building( void ) : Harvestable( )
{
    this->m_position = sf::Vector2i(0,0);
    this->m_size = sf::Vector2i(0,0);
    this->m_productDay = 0;
    this->m_animation = new Animation();
    this->m_currentPrepare = 0;
    this->m_alreadyPrepare = false;
}

Building::Building( sf::Vector2i & position,const std::string path ) : Harvestable( )
{
    this->m_animation = new Animation();
    this->load(path);
    this->m_position = position;
    this->m_currentPrepare = 0;
    this->m_alreadyPrepare = false;
}

Building::~Building( void )
{
    //delete this->m_animation; ->Error in `_build/Incidence': double free or corruption (fasttop)
}

sf::Vector2i Building::getPosition( void )
{
    return m_position;
}

void Building::setPosition( int x,int y )
{
    this->m_position = sf::Vector2i(x,y);
}

void Building::setPosition( const sf::Vector2i & position )
{
    this->m_position = position;
}

void Building::load( const std::string path )
{
    int sizeX,sizeY,nbR;
    std::string resource,animationPath;

    std::ifstream ifs(path.c_str());

    ifs >> this->m_pickingTime;
    ifs >> nbR;
    for (int i(0);i<nbR;i++)
    {
        int qt;
        ifs >> resource >> qt;
        Ressource r;
        r.quantity = qt;
        if (resource == "FOOD")
        {
            r.type = FOOD;
        }
        else if (resource == "WOOD")
        {
            r.type = WOOD;
        }
        else if (resource == "STONE")
        {
            r.type = STONE;
        }
        else
        {
            r.type = NOTHING;
        }

        m_ressources.push_back(r);
    }
    ifs >> this->m_productDay;
    ifs >> nbR;
    for (int i(0);i<nbR;i++)
    {
        ifs >> resource;
        if (resource == "FOOD")
        {
            this->m_ressourceStorage.push_back(FOOD);
        }
        else if (resource == "WOOD")
        {
            this->m_ressourceStorage.push_back(WOOD);
        }
        else if (resource == "STONE")
        {
            this->m_ressourceStorage.push_back(STONE);
        }
        else
        {
            this->m_ressourceStorage.push_back(NOTHING);
        }
    }
    ifs >> animationPath;
    ifs >> sizeX;
    ifs >> sizeY;

    ifs.close();

    this->m_size = sf::Vector2i(sizeX,sizeY);
    this->m_animation->load(animationPath);
}

void Building::drawTop( sf::RenderTarget & target )
{
    sf::Sprite s(*(this->m_animation->update()));
    sf::IntRect ir(0,0,(this->m_size.x*32),32);
    s.setTextureRect(ir);
    s.setPosition((this->m_position.x*32),((this->m_position.y-1)*32));
    target.draw(s);
}

void Building::drawBottom( sf::RenderTarget & target )
{
    sf::Sprite s(*(this->m_animation->update()));
    sf::IntRect ir(0,32,(this->m_size.x*32),32);
    s.setTextureRect(ir);
    s.setPosition((this->m_position.x*32),(this->m_position.y*32));
    target.draw(s);
}

bool Building::isHarvestable( void )
{
    return (this->m_ressources.size() > 0);
}

void Building::havested( void )
{

}
