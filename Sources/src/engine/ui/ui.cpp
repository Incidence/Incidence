#include "ui.hpp"

#include <fstream>
#include <iostream>

#include "widget.hpp"
#include "button.hpp"
#include "text_insert.hpp"
#include "container.hpp"
#include "../state.hpp"

UI::UI( State * parent ) : parentState(parent) { }

UI::~UI( void ) { }

void UI::loadFromFile( const std::string path )
{
    std::ifstream file;
    file.open( path.c_str() );

    if( !file.is_open())
    {
        std::cerr << "Error UI : Can't open file \"" + path + "\"" << std::endl;
        return;
    }

    std::string buffer = "";
    bool b = true;

    do {
        file >> buffer;
        if(buffer == "+UI")
        {
            b = false;
        }
    } while( b || file.eof() );

    int k = 0;
    while( buffer != "+EndUI" && !file.eof() )
    {
        Widget * w = NULL;
        sf::FloatRect pb(0, 0, 800, 600); /// RECODE
        k = 0;

        if( buffer == "+Widget" )
        {
            file >> buffer;
            w = new Widget;
            w->setParentBounds(pb);
            w->loadFromFile( path, buffer );
            this->addWidget(w);
            k = 1;
        }
        else if( buffer == "+Button" )
        {
            file >> buffer;
            w = new Button;
            w->setParentBounds(pb);
            w->loadFromFile( path, buffer );
            this->addWidget(w);
            k = 1;
        }
        else if( buffer == "+TextInsert" )
        {
            file >> buffer;
            w = new TextInsert;
            w->setParentBounds(pb);
            w->loadFromFile( path, buffer );
            this->addWidget(w);
            k = 1;
        }
        else if( buffer == "+Container" )
        {
            file >> buffer;
            w = new Container;
            w->setParentBounds(pb);
            w->loadFromFile( path, buffer );
            this->addWidget(w);
            k = 1;
        }

        buffer = "";
        while(k > 0)
        {
            file >> buffer;
            if( buffer == "+Widget" || buffer == "+Button" || buffer == "+TextInsert" || buffer == "+Container" )
            {
                k++;
            }
            else if( buffer == "+End" )
            {
                k--;
            }
        }

        file >> buffer;
    }

    file.close();
}

void UI::addWidget( Widget * w )
{
    this->contents.push_back( w );
}

void UI::draw( sf::RenderTarget & window )
{
    for( std::list< Widget* >::iterator i = this->contents.begin(); i != this->contents.end(); i++ )
    {
        window.draw( * static_cast<sf::Drawable*>(*i) );
    }
}

bool UI::handleEvent( sf::Event & e, std::list< Widget* > * c )
{
    bool onUi = false;

    std::list< Widget* > * content = c;
    if(content == NULL)
    {
        content = &this->contents;
    }

    switch( e.type )
    {
        case sf::Event::MouseMoved :
        {
            for( std::list< Widget* >::iterator i = content->begin(); i != content->end(); i++ )
            {
                if( (*i)->isShow() )
                {
                    if( (*i)->wType == 'b' )
                    {
                        Button * w = static_cast<Button*>(*i);
                        w->select( w->isOver( sf::Vector2i( e.mouseMove.x, e.mouseMove.y ) ) );
                    }
                    else if( (*i)->wType == 'c' )
                    {
                        Container * w = static_cast<Container*>(*i);
                        this->handleEvent( e, w->getContents() );
                    }
                }
            }
        } break;

        case sf::Event::MouseButtonReleased :
        {
            for( std::list< Widget* >::iterator i = content->begin(); i != content->end(); i++ )
            {
                if( (*i)->isShow() )
                {
                    if( (*i)->wType == 'b' )
                    {
                        Button * w = static_cast<Button*>(*i);
                        if( w->isOver( sf::Vector2i( e.mouseButton.x, e.mouseButton.y ) ) && this->parentState )
                        {
                            this->parentState->addEvent( w->active() );
                        }
                    }
                    else if( (*i)->wType == 't' )
                    {
                        TextInsert * w = static_cast<TextInsert*>(*i);
                        w->select( w->isOver( sf::Vector2i( e.mouseButton.x, e.mouseButton.y ) ) );
                    }
                    else if( (*i)->wType == 'c' )
                    {
                        Container * w = static_cast<Container*>(*i);
                        this->handleEvent( e, w->getContents() );
                    }
                }
            }
        } break;


        case sf::Event::MouseButtonPressed :
        {
            for( std::list< Widget* >::iterator i = content->begin(); i != content->end(); i++ )
            {
                if( (*i)->isShow() && (*i)->isOver( sf::Vector2i(e.mouseButton.x, e.mouseButton.y)) )
                {
                    onUi = true;
                    break;
                }
            }
        } break;


        case sf::Event::TextEntered :
        {
            for( std::list< Widget* >::iterator i = content->begin(); i != content->end(); i++ )
            {
                if( (*i)->isShow() )
                {
                    if( (*i)->wType == 't' )
                    {
                        TextInsert * w = static_cast<TextInsert*>(*i);
                        if( w->isSetelected() )
                        {
                            w->enter( static_cast<char>(e.text.unicode) );
                        }
                    }
                    else if( (*i)->wType == 'c' )
                    {
                        Container * w = static_cast<Container*>(*i);
                        this->handleEvent( e, w->getContents() );
                    }
                }
            }
        } break;

        default :
            break;
    }

    return onUi;
}

Widget * UI::getWidget( std::string name )
{
    Widget * w = NULL;

    for( std::list< Widget* >::iterator i = this->contents.begin(); i != this->contents.end(); i++ )
    {
        if( (*i)->getName() == name )
        {
            w = (*i);
        }
        else if( (*i)->wType == 'c' )
        {
            Container * c = static_cast<Container*>(*i);
            Widget * r = c->getWidget( name );
            if(r)
            {
                w = r;
            }
        }
    }

    return w;
}
