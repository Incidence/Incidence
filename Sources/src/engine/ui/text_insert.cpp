#include "text_insert.hpp"

#include <fstream>

TextInsert::TextInsert( void ) : Widget('t')
{
    this->selected = false;
    this->text = "";
    this->content = new WidgetContent("TEXT", "", sf::Color::White);
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
        if(this->text.length() > 0)
        {
            this->text.erase(this->text.end() - 1);
        }
    }
    else if(this->text.length() < this->lenght)
    {
        if( (e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z') || (e >= '0' && e <= '9') || e == '_' )
        this->text.push_back(e);
    }

    this->content->setText(this->text);
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

std::string TextInsert::getText() const
{
    return this->text;
}

void TextInsert::setText( std::string s )
{
    this->text = s;
    this->content->setText(this->text);
    this->update();
}

void TextInsert::update( void )
{
    sf::FloatRect r(0, 0, 0, 0);
    if(this->content)
    {
        r = this->content->getContentBounds();
    }

    sf::Vector2f s1( r.width + this->padding.x*2, r.height + this->padding.y*2 );
    sf::Vector2f s2( this->size );
    sf::Vector2f sf;
    sf.x = std::max( s1.x, s2.x );
    sf.y = std::max( s1.y, s2.y );

    this->shape.setSize( sf );
    this->shape.setPosition( this->position );

    if(this->content)
    {
        int x = getAbsolutePosition( r, shape.getGlobalBounds(), LEFT).x;
        int y = getAbsolutePosition( r, shape.getGlobalBounds(), MIDDLE).y;
        x += 5;
        sf::Vector2f p(x, y);

        this->content->setContentPosition( p );
    }
}


void TextInsert::setLenght( unsigned int l )
{
    this->lenght = l;
}
