#ifndef _CORE_TEXT_INSERT_
#define _CORE_TEXT_INSERT_

#include <SFML/Graphics.hpp>

#include "widget.hpp"

class TextInsert : public Widget
{

public :
    TextInsert( void );
    virtual ~TextInsert( void );

    virtual void loadFromFile( const std::string & path, const std::string & name );

    //! const char wType = 't';

    // Methods :

    virtual void enter( char e );
    virtual void update( void );

    virtual bool isSetelected() const;

    virtual void select( bool b );
    virtual std::string getTextEnter() const;
    virtual void setTextEnter( std::string s );

    virtual void setLenght( unsigned int l );

private :

    // Attributes :

    bool selected;
    std::string textEnter;
    unsigned int lenght;

};

#endif // _CORE_TEXT_INSERT_
