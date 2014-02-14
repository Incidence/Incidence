#ifndef _ANIMATION_
#define _ANIMATION_

#include <iostream>
#include <SFML/Graphics.hpp>

class Animation
{

public :
    Animation( void );
    Animation( const std::string path );
    ~Animation( void );

    void clean();
    bool load( const std::string path );

    sf::Sprite * update( void );

    void play( void );
    void stop( void );
    void pause( void );

    bool isPlay( void );
    bool isLoop( void );

    sf::Vector2f m_position;
    sf::Vector2f m_bounds;
    void draw(sf::RenderTarget& target);

    std::string getName( void );
    unsigned int getIdFrame( void );

private :
    std::string m_name;
    std::string m_pathTexture;

    std::vector<sf::Sprite*> m_sprites;
    std::vector<float> m_framesTime;

    float m_lastTime;
    unsigned int m_numFrame;

    bool m_loop;
    bool m_play;

};

#endif
