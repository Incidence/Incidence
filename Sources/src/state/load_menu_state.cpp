#include "load_menu_state.hpp"

LoadMenuState::LoadMenuState( Game * g ) : m_ui(this)
{
    m_game = g;

    m_position = 0;

	init();
}

LoadMenuState::~LoadMenuState( void )
{

}

void LoadMenuState::init( void )
{
    std::string directoryPath("saves");

    DIR *directory;
    struct dirent *entry;
    if((directory  = opendir(directoryPath.c_str())) == NULL) {
        std::cout << "Error : Opening save directory !" << std::endl;
    }
    while ((entry = readdir(directory)) != NULL) {
        std::string fileName(entry->d_name);
        if ((fileName.size() > 5) && (fileName.substr((fileName.size()-5),5) == ".save"))
        {
            m_files.push_back(std::string(fileName));
        }
    }
    closedir(directory);

    Button * b;
    GameEvent ge;

    ge.type = EV_BACK;

    b = new Button();
    b->setText( "Back", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 300, 100 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_SCROLL_UP;

    b = new Button();
    b->setText( "Up", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 100, 200 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    ge.type = EV_SCROLL_DOWN;

    b = new Button();
    b->setText( "Down", sf::Color::White );
    b->setBorder( sf::Color::Blue );
    b->setBorderOver( sf::Color::Yellow );
    b->setBorderSize(1);
    b->setPositionAbsolute( 100, 400 );
    b->setSize(100, 50);
    b->setEvent( ge );
    m_ui.addWidget(b);

    unsigned int sizeY(250/m_itemNb);
    unsigned int i(0);
    while ((i < m_files.size()) && (i < m_itemNb))
    {
        ge.type = EV_LOAD;
        ge.text = m_files[i];

        b = new Button();
        b->setName("load"+itos(i));
        b->setText( m_files[i], sf::Color::White );
        b->setBorder( sf::Color::Blue );
        b->setBorderOver( sf::Color::Yellow );
        b->setBorderSize(1);
        b->setPositionAbsolute( 300, (200+sizeY*i) );
        b->setSize(100, sizeY);
        b->setEvent( ge );
        m_ui.addWidget(b);

        i++;
    }
}

void LoadMenuState::draw( sf::RenderTarget & window )
{
    window.setView(window.getDefaultView());
    m_ui.draw(window);
}

void LoadMenuState::update( void )
{

}

void LoadMenuState::handleEvent( sf::Event & e )
{
    m_ui.handleEvent(e);
}

void LoadMenuState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_BACK :
        StateManager::get()->popState();
        break;

    case EV_SCROLL_UP :
        {
            if (m_position > 0)
            {
                m_position--;

                GameEvent ge;
                ge.type = EV_LOAD;
                for (unsigned int i(0);i<m_itemNb;i++)
                {
                    (static_cast<Button*>(m_ui.getWidget("load"+itos(i))))->setText( m_files[i+m_position], sf::Color::White );
                    ge.text = m_files[i+m_position];
                    (static_cast<Button*>(m_ui.getWidget("load"+itos(i))))->setEvent( ge );
                }
            }
        }
        break;

    case EV_SCROLL_DOWN :
        {
            if ((int)m_position < ((int)m_files.size()-(int)m_itemNb))
            {
                m_position++;

                GameEvent ge;
                ge.type = EV_LOAD;
                for (unsigned int i(0);i<m_itemNb;i++)
                {
                    (static_cast<Button*>(m_ui.getWidget("load"+itos(i))))->setText( m_files[i+m_position], sf::Color::White );
                    ge.text = m_files[i+m_position];
                    (static_cast<Button*>(m_ui.getWidget("load"+itos(i))))->setEvent( ge );
                }
            }
        }
        break;

    case EV_LOAD :
        {
            std::cout << ("saves/"+e.text) << std::endl;
            m_game->loadGame("saves/"+e.text);
            StateManager::get()->popState();
        }
        break;

    default :
        break;

    }
}
