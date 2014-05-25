#ifndef _CORE_WIDGET_
#define _CORE_WIDGET_

#include <SFML/Graphics.hpp>

#include "../foo.hpp"
#include "widget_content.hpp"

class Animation;

class Widget : public sf::Drawable
{

public :
    Widget( char t = 'w' );
    virtual ~Widget( void );

    virtual void loadFromFile( const std::string & path, const std::string & name );

    const char wType; // = 'w'

    // Setters :

    void setName( std::string name );
    std::string getName( void ) const;

    void setBackground( sf::Color c );
    void setBorder( sf::Color c );
    void setBorderSize( int s );
    //void setContent( WidgetContent * d );
    void setAnimation( Animation * a );
    void setText( sf::Text * s );
    void setText( std::string t, const sf::Color c = sf::Color::Black );
	void setTextSize( int i );
    void setSprite( sf::Sprite * s );

    void setPositionRelative( RelativePosition p );
    void setPositionAbsolute( float x, float y );
    void setPositionAbsolute( sf::Vector2f p );

    void setPadding( float x, float y );
    void setPadding( sf::Vector2f p );
    void setSize( float x, float y );
    void setSize( sf::Vector2f p );

    void setParentBounds( sf::FloatRect r );
    sf::FloatRect getBounds( void );

    void move( float x, float y );
    void move( sf::Vector2f p );
    void update( void );

    virtual void setShow( bool b );
    virtual bool isShow( void );

    // Methods :

    virtual bool isOver( const sf::Vector2i & p ) const;

protected :

    //! Inherited from sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Attributes :

    std::string name;

    sf::Color background;
    sf::Color border;
    sf::Color cText;
    int border_size;
    //WidgetContent * content; //! sf::Font, Animation, sf::Sprite, ...
    sf::RectangleShape shape;

    // Content :
    sf::Text * text;
    Animation * animation;
    sf::Sprite * sprite;
    sf::Vector2f spritePosition;
    // -----

    sf::Vector2f position;
    sf::Vector2f padding;
    sf::Vector2f size;

    bool show;
    sf::FloatRect parentBounds;

};

#endif // _CORE_WIDGET_
