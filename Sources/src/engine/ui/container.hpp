#ifndef _CORE_CONTAINER_
#define _CORE_CONTAINER_

#include <SFML/Graphics.hpp>
#include <list>

#include "widget.hpp"

class Container : public Widget
{

public :
    Container( void );
    virtual ~Container( void );

    virtual void loadFromFile( const std::string & path, const std::string & name );

    //! const char wType = 'c';

    // Getters :

    std::list< Widget* > * getContents( void );

    // Methods :

    virtual void addWidget( Widget * w );
    virtual void update( void );
    virtual Widget * getWidget( std::string name );
    virtual void setShow( bool b );

private :

    //! Inherited from sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Attributes :

    std::list< Widget* > contents;

};

#endif // _CORE_CONTAINER_
