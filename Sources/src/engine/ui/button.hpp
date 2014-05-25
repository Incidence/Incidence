#ifndef _CORE_BUTTON_
#define _CORE_BUTTON_

#include <SFML/Graphics.hpp>

#include "../game_event.hpp"
#include "widget.hpp"

class Button : public Widget
{

public :
    Button( void );
    virtual ~Button( void );

    virtual void loadFromFile( const std::string & path, const std::string & name );

    //! const char wType = 'b';

    // Setters :

    void setBorderOver( sf::Color c );
    void setTextOver( sf::Color c );
    void setEvent( GameEvent e );

    // Getter :

    GameEvent getEvent() const;

    // Methods :

    virtual bool isSetelected() const;

    virtual void select( bool b );
    virtual GameEvent active() const;

private :

    //! Inherited from sf::Drawable
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // with "border_over"

    // Attributes :

    sf::Color border_over;
    sf::Color cText_over;
    bool selected;

    GameEvent event;

};

#endif // _CORE_BUTTON_
