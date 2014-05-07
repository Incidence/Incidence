#include "container.hpp"

#include <fstream>

#include "widget.hpp"
#include "button.hpp"
#include "text_insert.hpp"


Container::Container( void ) : Widget('c') { }
Container::~Container( void ) { }

void Container::loadFromFile( const std::string & path, const std::string & name )
{
    Widget::loadFromFile(path, name);

    std::ifstream file;
    file.open( path.c_str() );

    std::string buffer = "";
    bool b = true;

    do {
        file >> buffer;

        if(buffer == "+Container")
        {
            file >> buffer;
            if(buffer == name)
            {
                b = false;
            }
        }
    } while( b || file.eof());

    int k = 0;

    while( buffer != "+End" && !file.eof() )
    {
        Widget * w = NULL;

        if( buffer == "+Widget" )
        {
            file >> buffer;
            w = new Widget;
            w->setParentBounds(this->shape.getGlobalBounds());
            w->loadFromFile( path, buffer );
            this->addWidget(w);
            k = 1;
        }
        else if( buffer == "+Button" )
        {
            file >> buffer;
            w = new Button;
            w->setParentBounds(this->shape.getGlobalBounds());
            w->loadFromFile( path, buffer );
            this->addWidget(w);
            k = 1;
        }
        else if( buffer == "+TextInsert" )
        {
            file >> buffer;
            w = new TextInsert;
            w->setParentBounds(this->shape.getGlobalBounds());
            w->loadFromFile( path, buffer );
            this->addWidget(w);
            k = 1;
        }
        else if( buffer == "+Container" )
        {
            file >> buffer;
            //w = new Container;
            w->setParentBounds(this->shape.getGlobalBounds());
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

std::list< Widget* > * Container::getContents( void )
{
    return & this->contents;
}


void Container::addWidget( Widget * w )
{
    this->contents.push_back( w );
}

void Container::setWidgetTextSize( int size )
{
	for( std::list< Widget* >::iterator i = this->contents.begin(); i != this->contents.end(); i++ )
    {
		(*i)->setTextSize(size);
	}
}

Widget * Container::getWidget( std::string name )
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


void Container::update( void )
{
    Widget::update();

    for( std::list< Widget* >::iterator i = this->contents.begin(); i != this->contents.end(); i++ )
    {
        (*i)->setParentBounds(this->shape.getGlobalBounds());
    }
}


void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Widget::draw(target, states);

    for( std::list< Widget* >::const_iterator i = this->contents.begin(); i != this->contents.end(); i++ )
    {
        target.draw( * static_cast<sf::Drawable*>(*i) );
    }
}

void Container::setShow( bool b )
{
    for( std::list< Widget* >::iterator i = this->contents.begin(); i != this->contents.end(); i++ )
    {
        (*i)->setShow(b);
    }
    this->show = b;
}
