#include "data_manager.hpp"

#include "foo.hpp"

DataManager * DataManager::singleton = NULL;

DataManager * DataManager::get( void )
{
    if(DataManager::singleton == NULL)
    {
        DataManager::singleton = new DataManager;
    }

    return DataManager::singleton;
}

void DataManager::kill( void )
{
    if(DataManager::singleton)
    {
        delete DataManager::singleton;
        DataManager::singleton = NULL;
    }
}

DataManager::DataManager( void )
{

}

DataManager::~DataManager( void )
{

}

sf::Texture * DataManager::addTexture( const std::string path )
{
    sf::Texture * t = new sf::Texture;
    if( t->loadFromFile( path ) )
    {
        m_textures[path] = t;
        return t;
    }
    else
    {
        return NULL;
    }
}

sf::Texture * DataManager::getTexture( const std::string path )
{
    sf::Texture * t = NULL;
    std::map< std::string, sf::Texture * >::iterator i = m_textures.find( path );
    if( i == m_textures.end() )
    {
        t = addTexture( path );
    }
    else
    {
        t = (*i).second;
    }

    return t;
}

// *********************** FONTS ******

sf::Font * DataManager::addFont( const std::string path )
{
    sf::Font * f = new sf::Font;
    if( f->loadFromFile( path ) )
    {
        this->fonts[path] = f;
        return f;
    }
    else
    {
        return NULL;
    }
}

sf::Font * DataManager::getFont( const std::string path )
{
    sf::Font * f = NULL;
    std::map< std::string, sf::Font * >::iterator i = this->fonts.find( path );
    if( i == this->fonts.end() )
    {
        f = addFont( path );
    }
    else
    {
        f = (*i).second;
    }

    return f;
}


// *********************** SPRITES ******

sf::Sprite * DataManager::addSprite( const std::string path )
{
    sf::Sprite * s = new sf::Sprite;
    sf::Texture * t = getTexture( path );
    if( t )
    {
        s->setTexture(*t);
        m_sprites[path] = s;
        return s;
    }
    else
    {
        return NULL;
    }
}

sf::Sprite * DataManager::addSprite( const std::string path, sf::FloatRect r )
{
    sf::Sprite * s = new sf::Sprite;
    sf::Texture * t = this->getTexture( path );
    std::string p = path + "." + itos(r.left) + "." + itos(r.top) + "." + itos(r.width) + "." + itos(r.height);

    if( t )
    {
        s->setTexture(*t);
        s->setTextureRect(static_cast<sf::IntRect>(r));
        m_sprites[p] = s;
        return s;
    }
    else
    {
        return NULL;
    }
}

sf::Sprite * DataManager::getSprite( const std::string path )
{
    sf::Sprite * s = NULL;
    std::map< std::string, sf::Sprite * >::iterator i = m_sprites.find( path );
    if( i == m_sprites.end() )
    {
        s = addSprite( path );
    }
    else
    {
        s = (*i).second;
    }

    return s;
}



sf::Sprite * DataManager::getSprite( const std::string path, sf::FloatRect r )
{
    sf::Sprite * s = NULL;
    std::string p = path + "." + itos(r.left) + "." + itos(r.top) + "." + itos(r.width) + "." + itos(r.height);

    std::map< std::string, sf::Sprite * >::iterator i = m_sprites.find( p );
    if( i == m_sprites.end() )
    {
        s = addSprite( path, r );
    }
    else
    {
        s = (*i).second;
    }

    return s;
}

// ****** ****** *******


sf::SoundBuffer * DataManager::addSoundBuffer( const std::string path )
{
    sf::SoundBuffer * s = new sf::SoundBuffer;
    if( s->loadFromFile( path ) )
    {
        m_sounds[path] = s;
        return s;
    }
    else
    {
        return NULL;
    }
}

sf::SoundBuffer * DataManager::getSoundBuffer( const std::string path )
{
    sf::SoundBuffer * s = NULL;
    std::map< std::string, sf::SoundBuffer * >::iterator i = m_sounds.find( path );
    if( i == m_sounds.end() )
    {
        s = addSoundBuffer( path );
    }
    else
    {
        s = (*i).second;
    }

    return s;
}

