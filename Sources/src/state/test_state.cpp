#include "test_state.hpp"

#include "../engine/state_manager.hpp"
#include "../engine/time.hpp"

#include "../game/game.hpp"
#include "../game/entity/entity.hpp"
#include "../game/entity/lumberjack.hpp"
#include "../game/entity/enemy_citizen.hpp"
#include "../game/entity/gatherer.hpp"
#include "../game/entity/hunter.hpp"
#include "../game/entity/peaceful_animal.hpp"
#include "../game/entity/wild_animal.hpp"
#include "../game/entity/pickman.hpp"

#include "night_state.hpp"
#include "end_state.hpp"
#include "game_menu_state.hpp"

#include "../engine/ui/button.hpp"
#include "../engine/ui/container.hpp"

#include <iostream>

TestState::TestState( sf::RenderWindow * window, Game * game  ) : m_game(game), m_dayDuration(60), m_dayBeginTime(0), m_night(true), m_ui(this), m_pause(false)
{
    if(m_game == NULL) {
        m_game = new Game();
    }
    m_game->newGame(50, 50);
        m_night = true;

	m_window = window;
	sf::Vector2u windowSize = m_window->getSize();
    m_view = sf::View(sf::Vector2f(m_game->m_home.getPosition().x * 32 , m_game->m_home.getPosition().y * 32- 30), sf::Vector2f(windowSize.x,windowSize.y));
	//m_view = sf::View(sf::Vector2f(windowSize.x/2,windowSize.y/2-30), sf::Vector2f(windowSize.x,windowSize.y));

	init();
}

TestState::~TestState( void )
{
    if(m_game) {
        //delete m_game;
    }
}

void TestState::init( void )
{
    Container * c, * cs;
    Button * b;
    Widget * w;
    GameEvent ge;

    c = new Container;
    c->setSprite( DataManager::get()->getSprite( "data/img/interface/container1.png" ) );
    c->setPositionRelative(TOP);
    c->setPositionRelative(LEFT);

    /// ---------- Day

    w = new Widget;
    w->setText( "Day", sf::Color::White );
	w->setTextSize( 20 );
    w->setPositionAbsolute( 5, 0 );
    c->addWidget(w);

    cs = new Container;
    cs->setBackground(sf::Color(32,32,32));
    cs->setSize(50, 22);
    cs->setPositionAbsolute(55, 4);

    w = new Widget;
    w->setName("days_count");
    w->setText( itos(m_game->getDaysCount()+1), sf::Color::White );
	w->setTextSize( 20 );
    w->setPositionAbsolute(55,0);
    cs->addWidget(w);
    c->addWidget(cs);

    /// ---------- Pop

    w = new Widget;
    w->setText( "Pop", sf::Color::White );
	w->setTextSize( 20 );
    w->setPositionAbsolute( 129, 0 );
    c->addWidget(w);

    cs = new Container;
    cs->setBackground(sf::Color(32,32,32));
    cs->setSize(50, 22);
    cs->setPositionAbsolute(182, 4);

    w = new Widget;
    w->setName("pop_count");
    w->setText( itos(m_game->getPopulation().size()), sf::Color::White );
	w->setTextSize( 20 );
    w->setPositionAbsolute(182,0);
    cs->addWidget(w);
    c->addWidget(cs);

    /// ---------- IP

    w = new Widget;
    w->setText( "IP", sf::Color::White );
	w->setTextSize( 20 );
    w->setPositionAbsolute( 258, 0 );
    c->addWidget(w);

    cs = new Container;
    cs->setBackground(sf::Color(32,32,32));
    cs->setSize(202,22);
    cs->setPositionAbsolute(287, 4);
    c->addWidget(cs);

    //std::cout << m_game->getPI() << std::endl;
    //std::cout << (m_game->getPI()*200/Game::incidenceMax) << std::endl;

    m_ipDisplay.setTexture(DataManager::get()->getTexture("data/img/interface/ip.png"));
    m_ipDisplay.setSize(sf::Vector2f(m_game->getPI()*200/Game::incidenceMax,20));
    m_ipDisplay.setPosition(288,5);

    /// ---------- Food

    w = new Widget();
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/food.png" ) );
    w->setPositionAbsolute( 510, 4 );
    c->addWidget(w);

    cs = new Container;
    cs->setBackground(sf::Color(32,32,32));
    cs->setSize(50, 22);
    cs->setPositionAbsolute(532, 4);

    w = new Widget;
    w->setName("food_count");
    w->setText( itos(m_game->getQtyFood()), sf::Color::White );
	w->setTextSize( 20 );
    w->setPositionAbsolute(532,0);
    cs->addWidget(w);
    c->addWidget(cs);

    /// ---------- Wood

    w = new Widget();
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/wood.png" ) );
    w->setPositionAbsolute( 604, 4 );
    c->addWidget(w);

    cs = new Container;
    cs->setBackground(sf::Color(32,32,32));
    cs->setSize(50, 22);
    cs->setPositionAbsolute(626, 4);

    w = new Widget;
    w->setName("wood_count");
    w->setText( itos(m_game->getQtyWood()), sf::Color::White );
	w->setTextSize( 20 );
    w->setPositionAbsolute(626,0);
    cs->addWidget(w);
    c->addWidget(cs);

    /// ---------- Stone

    w = new Widget();
    w->setSprite( DataManager::get()->getSprite( "data/img/interface/stone.png" ) );
    w->setPositionAbsolute( 698, 4 );
    c->addWidget(w);

    cs = new Container;
    cs->setBackground(sf::Color(32,32,32));
    cs->setSize(50, 22);
    cs->setPositionAbsolute(720, 4);

    w = new Widget;
    w->setName("stone_count");
    w->setText( itos(m_game->getQtyStone()), sf::Color::White );
	w->setTextSize( 20 );
    w->setPositionAbsolute(720,0);
    cs->addWidget(w);
    c->addWidget(cs);

    m_ui.addWidget(c);

    /// ---------- Actions

    c = new Container;
    c->setSprite( DataManager::get()->getSprite( "data/img/interface/container2.png" ) );
    c->setPositionAbsolute(770,0);

    ge.type = EV_SELECT_FALAISE;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/cliff.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 121);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_SABLE;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/sand.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 153);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_TERRE_SECHE;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/dirt.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 185);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_TERRE;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/dry_grass.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 217);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_TERRE_INNONDE;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/wet_grass.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 249);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_EAU;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/water.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 281);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_PIERRE;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/stone_spot.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 393);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_ARBRE;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/tree.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 425);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_FRUITIER;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/fruit_tree.png" ) );
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 457);
    b->setEvent( ge );
    c->addWidget(b);

    ge.type = EV_SELECT_BUISSON;

    b = new Button;
    b->setSprite( DataManager::get()->getSprite( "data/img/interface/bush.png" ) );
    b->setTextOver(sf::Color(100, 20, 20));
    b->setBorder(sf::Color(32,32,32));
    b->setBorderOver(sf::Color(200,50,50));
    b->setBorderSize(1);
    b->setPositionAbsolute(775, 489);
    b->setEvent( ge );
    c->addWidget(b);

    m_ui.addWidget(c);
}

void TestState::draw( sf::RenderTarget & window )
{
	window.setView(m_view);
    m_game->draw(window);
    window.setView(window.getDefaultView());
    Animation* Rain = m_game->getWeather()->getRainAnimation();
    Rain->draw(window);
    m_ui.draw(window);
    window.draw(m_ipDisplay);
}

void TestState::update( void )
{
    if(m_night) {
        m_dayBeginTime = Time::get()->elapsed().asSeconds();
        m_game->saveGame("saves/auto_save.autosave");
        m_night = false;
        m_view.setCenter(m_game->m_home.getPosition().x * 32, m_game->m_home.getPosition().y * 32 - 30);
    }

    if(m_pause) {
        m_dayBeginTime = Time::get()->elapsed().asSeconds() - (m_timePause - m_dayBeginTime);
        m_pause = false;
    }

	sf::Vector2u dimensions = (m_game->getTilemap())->getDimensions();
	sf::Vector2u tilesize = ((m_game->getTilemap())->getTileSet())->getTileSize();
	//Animation* Rain = m_game->getWeather()->getRainAnimation();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        int temp(m_view.getCenter().x - m_view.getSize().x/2);
        if (temp >= (int)tilesize.x)
        {
            m_view.move(-((int)tilesize.x),0);
            //Rain->m_position.x-=tilesize.x;
        }
        else if (temp > 0)
        {
            m_view.move(-temp,0);
            //Rain->m_position.x-=temp;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        int temp((dimensions.x*tilesize.x+30-m_view.getSize().x/2) - m_view.getCenter().x);
        if (temp >= (int)tilesize.x)
        {
            m_view.move(tilesize.x,0);
            //Rain->m_position.x+=tilesize.x;
        }
        else if (temp > 0)
        {
            m_view.move(temp,0);
            //Rain->m_position.x+=temp;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        int temp(m_view.getCenter().y +30 - m_view.getSize().y/2);
        if (temp >= (int)tilesize.y)
        {
            m_view.move(0,-((int)tilesize.y));
            //Rain->m_position.y-=tilesize.y;
        }
        else if (temp > 0)
        {
            m_view.move(0,-temp);
            //Rain->m_position.y-=temp;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        int temp((dimensions.y*tilesize.y-m_view.getSize().y/2) - m_view.getCenter().y);
        if (temp >= (int)tilesize.y)
        {
            m_view.move(0,tilesize.y);
            //Rain->m_position.y+=tilesize.y;
        }
        else if (temp > 0)
        {
            m_view.move(0,temp);
            //Rain->m_position.y+=temp;
        }
    }



    updateDay();
    m_game->update();

    m_ui.getWidget("days_count")->setText(itos(m_game->getDaysCount()+1), sf::Color::White);

    m_ui.getWidget("pop_count")->setText(itos(m_game->getPopulation().size()), sf::Color::White);

	m_ipDisplay.setSize(sf::Vector2f(m_game->getPI()*200/Game::incidenceMax,20));

	m_ui.getWidget("food_count")->setText(itos(m_game->getQtyFood()), sf::Color::White);

	m_ui.getWidget("wood_count")->setText(itos(m_game->getQtyWood()), sf::Color::White);

	m_ui.getWidget("stone_count")->setText(itos(m_game->getQtyStone()), sf::Color::White);

	std::vector<Entity*> e = m_game->getEntities();
	bool j = true;
	for(unsigned int i = 0; i < e.size(); i++) {
        if(e[i]->getType() == ALLY_CITIZEN && e[i]->getHealth() != DEAD) {
            j = false;
        }
	}

    if (j)
    {
        StateManager::get()->addState(new EndState(m_game));
        DataManager::get()->getMusic("data/menu.ogg")->play();
        DataManager::get()->getMusic("data/partie.ogg")->stop();
    }

}

void TestState::handleEvent( sf::Event & e )
{
    if( e.type == sf::Event::KeyPressed )
    {
        switch(e.key.code)
        {
            case sf::Keyboard::S :
            {
                if(e.key.control) {
                    m_game->saveGame("saves/test.save");
                }
            } break;

            case sf::Keyboard::O :
            {
                if(e.key.control) {
                    m_game->loadGame("saves/test.save");
                    m_night = true;
                }
            } break;

            case sf::Keyboard::Escape :
            {
                DataManager::get()->getMusic("data/menu.ogg")->play();
                DataManager::get()->getMusic("data/partie.ogg")->stop();
                m_pause = true;
                m_timePause = Time::get()->elapsed().asSeconds();
                StateManager::get()->addState(new GameMenuState(m_game));
            } break;

            default :
                break;

        }
    }


    if(! m_ui.handleEvent(e)) {
        if ( e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && m_element != -1 ) {
            if(m_element == 0) {
                m_game->actionGround(m_select, m_game->m_tilemap->getXY(sf::Vector2f(e.mouseButton.x + m_view.getCenter().x - m_view.getSize().x/2, e.mouseButton.y + m_view.getCenter().y  - m_view.getSize().y/2)));
            } else if(m_element == 1) {
                m_game->actionElement(m_select, m_game->m_tilemap->getXY(sf::Vector2f(e.mouseButton.x + m_view.getCenter().x - m_view.getSize().x/2, e.mouseButton.y + m_view.getCenter().y - m_view.getSize().y/2)));
            }
        }
    }

     if ( e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right ) {
            m_select = -1;
    }

    m_game->handleEvent(e);
}

void TestState::treatEvent( GameEvent e )
{
    switch(e.type) {

    case EV_SELECT_FALAISE :
        m_select = 5;
        m_element = 0;
        //std::cout << "fal sol" << std::endl;
        break;

    case EV_SELECT_SABLE :
        m_select = 4;
        m_element = 0;
        //std::cout << "sable sol" << std::endl;
        break;

    case EV_SELECT_TERRE_SECHE :
        m_select = 3;
        m_element = 0;
        //std::cout << "sec sol" << std::endl;
        break;

    case EV_SELECT_TERRE :
        m_select = 2;
        m_element = 0;
        //std::cout << "terre sol" << std::endl;
        break;

    case EV_SELECT_TERRE_INNONDE :
        m_select = 1;
        m_element = 0;
        //std::cout << "inno sol" << std::endl;
        break;

    case EV_SELECT_EAU :
        m_select = 0;
        m_element = 0;
        //std::cout << "eau sol" << std::endl;
        break;


    case EV_SELECT_ARBRE :
        m_select = 0;
        m_element = 1;
        //std::cout << "arbre sol" << std::endl;
        break;

    case EV_SELECT_FRUITIER :
        m_select = 1;
        m_element = 1;
        //std::cout << "fruit sol" << std::endl;
        break;

    case EV_SELECT_BUISSON :
        m_select = 2;
        m_element = 1;
        //std::cout << "buisson sol" << std::endl;
        break;

    case EV_SELECT_PIERRE :
        m_select = 3;
        m_element = 1;
        //std::cout << "roch sol" << std::endl;
        break;

    default :
        break;

    }
}


void TestState::updateDay( void )
{

    if(m_dayBeginTime + m_dayDuration - 5 < Time::get()->elapsed().asSeconds()) {
        // ALL GO_HOME
        m_game->allHome();
    }

    if(m_dayBeginTime + m_dayDuration < Time::get()->elapsed().asSeconds()) {
        StateManager::get()->addState( new NightState(m_game) );
        m_night = true;
    }

}
