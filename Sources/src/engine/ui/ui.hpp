#ifndef _CORE_UI_
#define _CORE_UI_

#include <SFML/Graphics.hpp>
#include <list>
#include <string>

class Widget;
class State;

class UI
{

public :
    UI( State * parent );
    virtual ~UI( void );

    // Methods :

    void loadFromFile( const std::string path );

    void addWidget( Widget * w );

    void draw( sf::RenderTarget & window );
    void handleEvent( sf::Event & e, std::list< Widget* > * c = NULL);

    Widget * getWidget( std::string name );

private :

    // Attributes :

    std::list< Widget* > contents;
    State * parentState;

};


#endif // _CORE_UI_
