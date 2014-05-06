#include "text_insert.hpp"

#include <fstream>

#include "../animation.hpp"

TextInsert::TextInsert( void ) : Widget('t')
{
    this->selected = false;
    this->textEnter = "";
    this->setTextEnter("");
    this->lenght = 256;
}

TextInsert::~TextInsert( void )
{

}

void TextInsert::loadFromFile( const std::string & path, const std::string & name )
{
    Widget::loadFromFile(path, name);

    std::ifstream file;
    file.open( path.c_str() );

    std::string buffer = "";
    bool b = true;

    do {
        file >> buffer;

        if(buffer == "+TextInsert")
        {
            file >> buffer;
            if(buffer == name)
            {
                b = false;
            }
        }
    } while( b || file.eof());

    this->setName( buffer );

    while( buffer != "+End" && !file.eof() )
    {
        if( buffer == "Lenght" )
        {
            unsigned int l;
            file >> l;
            this->setLenght( l );
        }

        file >> buffer;
    }

    file.close();
}

void TextInsert::enter( char e )
{
    if(e == '\b')
    {
        if(this->textEnter.length() > 0)
        {
            this->textEnter.erase(this->textEnter.end() - 1);
        }
    }
    else if(this->textEnter.length() < this->lenght)
    {
        if( (e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z') || (e >= '0' && e <= '9') || e == '_' )
        this->textEnter.push_back(e);
    }

    this->setTextEnter(this->textEnter);
    this->update();
}

bool TextInsert::isSetelected() const
{
    return this->selected;
}

void TextInsert::select( bool b )
{
    if( b != this->selected )
    {
        this->selected = b;
        if(this->selected)
        {
            sf::Color c = this->border;
            c.r += 70;
            c.b += 70;
            c.g += 70;
            this->shape.setOutlineColor( c );
        }
        else
        {
            this->shape.setOutlineColor( this->border );
        }
    }
}

std::string TextInsert::getTextEnter() const
{
    return this->textEnter;
}

void TextInsert::setTextEnter( std::string s )
{
    this->textEnter = s;
    this->setText(this->textEnter);
    this->update();
}

void TextInsert::update( void )
{
    sf::FloatRect r(0, 0, 0, 0);

    if(this->sprite)
    {
        r.height = std::max(this->sprite->getLocalBounds().height, r.height);
        r.width = std::max(this->sprite->getLocalBounds().width, r.width);
        r.top = std::max(this->sprite->getLocalBounds().top, r.top);
        r.left = std::max(this->sprite->getLocalBounds().left, r.left);
    }

    if(this->text)
    {
        r.height = std::max(this->text->getLocalBounds().height, r.height);
        r.width = std::max(this->text->getLocalBounds().width, r.width);
        r.top = std::max(this->text->getLocalBounds().top, r.top);
        r.left = std::max(this->text->getLocalBounds().left, r.left);
    }

    if(this->animation)
    {
        r.height = std::max(this->animation->update()->getLocalBounds().height, r.height);
        r.width = std::max(this->animation->update()->getLocalBounds().width, r.width);
        r.top = std::max(this->animation->update()->getLocalBounds().top, r.top);
        r.left = std::max(this->animation->update()->getLocalBounds().left, r.left);
    }

    sf::Vector2f s1( r.width + this->padding.x*2, r.height + this->padding.y*2 );
    sf::Vector2f s2( this->size );
    sf::Vector2f sf;
    sf.x = std::max( s1.x, s2.x );
    sf.y = std::max( s1.y, s2.y );

    this->shape.setSize( sf );
    this->shape.setPosition( this->position );

    if(this->animation)
    {
        int x = getAbsolutePosition( r, shape.getGlobalBounds(), CENTER).x;
        int y = getAbsolutePosition( r, shape.getGlobalBounds(), MIDDLE).y;
        sf::Vector2f p(x, y);

        this->animation->m_position = p;
    }

    if(this->text)
    {
        int x = getAbsolutePosition( r, shape.getGlobalBounds(), CENTER).x;
        int y = getAbsolutePosition( r, shape.getGlobalBounds(), MIDDLE).y;
        sf::Vector2f p(x, y);

        this->text->setPosition( p );
    }

    if(this->sprite)
    {
        int x = getAbsolutePosition( r, shape.getGlobalBounds(), CENTER).x;
        int y = getAbsolutePosition( r, shape.getGlobalBounds(), MIDDLE).y;
        sf::Vector2f p(x, y);

        this->sprite->setPosition( p );
    }
}


void TextInsert::setLenght( unsigned int l )
{
    this->lenght = l;
}
