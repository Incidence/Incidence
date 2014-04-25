#include "widget_content.hpp"

#include <iostream>
#include <cmath>

#include "../data_manager.hpp"

WidgetContent::WidgetContent( std::string type, std::string val )
{
    if(type == "SPRITE")
    {
        this->type = TYPE_SPRITE;
        this->s = DataManager::get()->getSprite( val );
    }
    else
    {
        this->type = TYPE_NONE;
    }
}


WidgetContent::WidgetContent( std::string type, std::string val, sf::FloatRect r )
{
    if(type == "SPRITE")
    {
        this->type = TYPE_SPRITE;
        this->s = DataManager::get()->getSprite( val, r );
    }
    else
    {
        this->type = TYPE_NONE;
    }
}


WidgetContent::WidgetContent( std::string type, std::string val, sf::Color c )
{
    this->type = TYPE_TEXT;
    this->t = new sf::Text;
    sf::Font * f = DataManager::get()->getFont( "data/font/font1.ttf" );
    if(f)
    {
        this->t->setFont( *f );
    }
    this->t->setColor( c );
    this->t->setCharacterSize( 18 );
    this->t->setString( val );
}

WidgetContent::~WidgetContent( void )
{
    if( this->type == TYPE_TEXT )
    {
        delete this->t;
    }
}

sf::Drawable * WidgetContent::getContentDraw( void )
{
    sf::Drawable * d = NULL;
    if( this->type == TYPE_TEXT )
    {
        this->t->setPosition(position);
        d = this->t;
    }
    else if( this->type == TYPE_SPRITE )
    {
        this->s->setPosition(position);
        d = this->s;
    }

    return d;
}


sf::FloatRect WidgetContent::getContentBounds( void )
{
    sf::FloatRect r(0, 0, 0, 0);
    if( this->type == TYPE_TEXT )
    {
        r = (this->t)->getGlobalBounds();
    }
    else if( this->type == TYPE_SPRITE )
    {
        r = (this->s)->getGlobalBounds();
    }

    return r;
}

void WidgetContent::setContentPosition( sf::Vector2f p )
{
    p.x = ceil( p.x );
    p.y = ceil( p.y );

    position = p;
}

void WidgetContent::setText( std::string text )
{
    if(this->type == TYPE_TEXT)
    {
        this->t->setString( text );
    }
}
