#ifndef _DATA_MANAGER_
#define _DATA_MANAGER_

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class DataManager
{

public :
    static DataManager * get( void );
    static void kill( void );

    // Font :

    sf::Font * addFont( const std::string path );
    sf::Font * getFont( const std::string path );

    // Graphic :

    sf::Texture * getTexture( const std::string path );
    sf::Texture * addTexture( const std::string path );

    sf::Sprite * addSprite( const std::string path );
    sf::Sprite * addSprite( const std::string path, sf::FloatRect r );
    sf::Sprite * getSprite( const std::string path );
    sf::Sprite * getSprite( const std::string path, sf::FloatRect r );

    // Audio :

    sf::SoundBuffer * getSoundBuffer( const std::string path );
    sf::SoundBuffer * addSoundBuffer( const std::string path );

    sf::Music * getMusic( const std::string path );
    sf::Music * addMusic( const std::string path );


private :
    DataManager( void );
    ~DataManager( void );

    static DataManager * singleton;

    std::map<std::string, sf::Font *> fonts;
    std::map<std::string, sf::Texture*> m_textures;
    std::map<std::string, sf::Sprite*> m_sprites;
    std::map<std::string, sf::SoundBuffer*> m_sounds;
    std::map<std::string, sf::Music*> m_musics;

};

#endif // _DATA_MANAGER_
