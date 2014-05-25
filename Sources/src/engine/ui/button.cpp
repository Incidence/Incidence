#include "button.hpp"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

Button::Button( void ) : Widget('b')
{
    this->event.type = EV_DEFAULT;
    this->event.number = 0;
    this->event.text = "";
}
Button::~Button( void ) { }

void Button::loadFromFile( const std::string & path, const std::string & name )
{
    Widget::loadFromFile(path, name);

    std::ifstream file;
    file.open( path.c_str() );

    std::string buffer = "";
    bool b = true;

    do {
        file >> buffer;

        if(buffer == "+Button")
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
        if( buffer == "BorderOver" )
        {
            int r, g, b;
            file >> r >> g >> b;
            this->setBorderOver( sf::Color(r, g, b) );
        }
        else if( buffer == "Event" )
        {
            int h;
            file >> h;
            this->event.type = static_cast<GameType>(h);
        }
        else if( buffer == "EventNumber" )
        {
            int l;
            file >> l;
            this->event.number = l;
        }

        else if( buffer == "EventText" )
        {
            std::string s;
            file >> s;
            this->event.text = s;
        }

        file >> buffer;
    }

    file.close();
}

void Button::setBorderOver( sf::Color c )
{
    this->border_over = c;
}

void Button::setTextOver( sf::Color c )
{
    this->cText_over = c;
}

void Button::setEvent( GameEvent e )
{
    this->event = e;
}

GameEvent Button::getEvent() const
{
    return this->event;
}

bool Button::isSetelected() const
{
    return this->selected;
}

void Button::select( bool b )
{
    if( b != this->selected )
    {
        this->selected = b;
        if(this->selected)
        {
            this->shape.setOutlineColor( this->border_over );
            this->text->setColor(cText_over);
        }
        else
        {
            this->shape.setOutlineColor( this->border );
            this->text->setColor(cText);
        }
    }
}

GameEvent Button::active() const
{
    return this->event;
}
