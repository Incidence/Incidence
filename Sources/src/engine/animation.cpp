#include "animation.hpp"

#include <fstream>

#include "data_manager.hpp"
#include "time.hpp"


Animation::Animation( void ) : m_name(""), m_pathTexture(""), m_lastTime(0), m_numFrame(0), m_loop(false), m_play(false)
{
    m_position.x = 0;
    m_position.y = 0;
}

Animation::Animation( const std::string path ) : m_name(""), m_pathTexture(""), m_lastTime(0), m_numFrame(0), m_loop(false), m_play(false)
{
    m_position.x = 0;
    m_position.y = 0;

    load(path);
}

Animation::~Animation( void )
{

}

void Animation::clean( void )
{
    m_name = "";
    m_lastTime = 0;
    m_numFrame = 0;

    m_sprites.clear();
    m_framesTime.clear();
}

bool Animation::load( const std::string path )
{
    clean();
    m_name = path;

    std::ifstream file;
    file.open( path.c_str() );

    if( !file.is_open() )
    {
        std::cerr << "Error : Load - Can't open file \"" + path + "\"" << std::endl;
        return false;
    }

    std::string buffer;
    sf::Vector2i sizeFrame;
    file >> buffer >> sizeFrame.x >> sizeFrame.y >> m_play >> m_loop;
    m_bounds = (sf::Vector2f)sizeFrame;

    std::string texture = buffer;

    bool b = true;
    while( !file.eof() )
    {
        do {
            file >> buffer;

            if(buffer == "+Frame")
            {
                b = false;
            }
        } while( b && !file.eof() );

        if( file.eof() )
        {
            return true;
        }

        sf::Vector2i pos;
        float time = 0;
        file >> pos.x >> pos.y >> time;

        sf::Sprite * s = DataManager::get()->getSprite(texture, sf::FloatRect(pos.x, pos.y, sizeFrame.x, sizeFrame.y));

        m_sprites.push_back(s);
        m_framesTime.push_back(time);

        buffer == "";
    }

    return true;
}


sf::Sprite * Animation::update( void )
{
    if(m_sprites.empty())
    {
        return NULL;
    }

    if(m_play)
    {
        // TEST
        m_lastTime += Time::get()->deltaTime();
        while(m_lastTime > m_framesTime[m_numFrame])
        {
            m_lastTime -= m_framesTime[m_numFrame];

            if(m_loop)
            {
                m_numFrame = (m_numFrame + 1) % m_sprites.size();
            }
            else
            {
                if(m_numFrame < m_sprites.size() - 1)
                {
                    m_numFrame++;
                }
                else
                {
                    m_play = false;
                }
            }
        }
    }

    sf::Sprite * s = m_sprites[m_numFrame];
    s->setPosition(m_position);
    return s;
}

void Animation::draw(sf::RenderTarget& target)
{
    sf::Sprite * s = update();
    if(s)
    {
        s->setPosition(m_position);
        target.draw(*s);
    }
}


void Animation::play( void )
{
    m_play = true;
}

void Animation::stop( void )
{
    m_play = false;
    m_numFrame = 0;
}

void Animation::pause( void )
{
    m_play = false;
}

bool Animation::isPlay( void )
{
    return m_play;
}

bool Animation::isLoop( void )
{
    return m_loop;
}

std::string Animation::getName( void )
{
    return m_name;
}

unsigned int Animation::getIdFrame( void )
{
    return m_numFrame;
}
