#ifndef _CORE_WIDGET_CONTENT_
#define _CORE_WIDGET_CONTENT_

#include <SFML/Graphics.hpp>

enum TypeContent { TYPE_SPRITE, TYPE_TEXT, TYPE_NONE };

class WidgetContent
{

private :

    int type;
    union {
        sf::Sprite * s;
        sf::Text * t;
        //! Animation, ...
    };
    sf::Vector2f position;

public :

    WidgetContent( std::string type, std::string val );
    WidgetContent( std::string type, std::string val, sf::FloatRect r );
    WidgetContent( std::string type, std::string val, sf::Color c );
    ~WidgetContent( void );

    sf::Drawable * getContentDraw( void );
    sf::FloatRect getContentBounds( void );
    void setContentPosition( sf::Vector2f p );
    void setText( std::string text );

};

#endif // _CORE_WIDGET_CONTENT_
