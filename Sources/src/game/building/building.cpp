#include "building.hpp"

Building::Building( void )
{
    this->m_pickingTime = 0;

    this->m_position = sf::Vector2i(0,0);
    this->m_size = sf::Vector2i(0,0);
    this->m_productDay = 0;
    this->m_animation = new Animation();
    this->m_currentPrepare = 0;
    this->m_alreadyPrepare = false;
}

Building::Building( sf::Vector2i & position,const std::string path )
{
    this->m_animation = new Animation();
    this->load(path);
    this->m_position = position;
    this->m_currentPrepare = 0;
    this->m_alreadyPrepare = false;
}

Building::~Building( void )
{
    delete this->m_animation;
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
        ifs >> resource;
        if (resource == "FOOD")
        {
            this->m_ressources.push_back(FOOD);
        }
        else if (resource == "WOOD")
        {
            this->m_ressources.push_back(WOOD);
        }
        else if (resource == "STONE")
        {
            this->m_ressources.push_back(STONE);
        }
        else
        {
            this->m_ressources.push_back(NOTHING);
        }
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
    this->m_animation.load(animationPath);
}

void Building::drawTop( sf::RenderTarget & target )
{
    sf::Sprite s(*(this->m_animation.update()));
    sf::IntRect ir(0,0,(this->m_size.x*32),32);
    s.setTextureRect(ir);
    s.setPosition((this->m_position.x*32),((this->m_position.y-1)*32));
    target.draw(s);
}

void Building::drawBottom( sf::RenderTarget & target )
{
    sf::Sprite s(*(this->m_animation.update()));
    sf::IntRect ir(0,32,(this->m_size.x*32),32);
    s.setTextureRect(ir);
    s.setPosition((this->m_position.x*32),(this->m_position.y*32));
    target.draw(s);
}

virtual bool Building::isHarvestable( void )
{
    return (this->m_ressources.size() > 0);
}
