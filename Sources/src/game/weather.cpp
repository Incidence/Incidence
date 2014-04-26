
#include "weather.hpp"


using namespace std;


Weather::Weather( const string rainpath)
{
    //Meteo par défaut Soleil
    m_weatherToday=SUNNY;
    m_weatherYesterday=UNDEFINED;
    m_weatherGrade=0;
    m_rain=new Animation();
    initRain(rainpath);
}

Weather::Weather(WeatherType weather,const string rainpath)
{
    m_weatherToday=weather;
    m_weatherYesterday=UNDEFINED;
    m_weatherGrade=0;
    m_rain=new Animation();
    initRain(rainpath);
}

Weather::~Weather()
{
    if(m_rain)
    {
        delete m_rain;
    }
}



void Weather::updateWeather()
{
    if(m_weatherToday==m_weatherYesterday || m_weatherYesterday==UNDEFINED)
    {
        switch(m_weatherToday)
        {
            case SUNNY:
                if(m_weatherGrade!=5)
                {
                    m_weatherGrade++;
                }
                break;

            case RAINY:
                if(m_weatherGrade!=-5)
                {
                    m_weatherGrade--;
                }
                break;

            default:
                break;
        }
    }
    else
    {
       switch(m_weatherToday)
        {
            case SUNNY:
                if(m_weatherGrade<=-3)
                {
                    m_weatherGrade=-1;
                }
                else
                {
                    m_weatherGrade++;
                }

                break;

            case RAINY:
                 if(m_weatherGrade>=3)
                {
                    m_weatherGrade=1;
                }
                else
                {
                    m_weatherGrade--;
                }
                break;

            default:
                break;
        }
    }

    m_weatherYesterday=m_weatherToday;
    std::cout<<"Niveau du temps : "<<m_weatherGrade<<std::endl;
}

void Weather::initRain(const string rainpath)
{
    m_rain->load(rainpath);
}

void Weather::draw(sf::RenderTarget& target)
{
    switch (m_weatherToday)
    {
    case RAINY:
        m_rain->draw(target);
        break;

    default:
        break;
    }
}

void Weather::impactsOnEntities(std::vector< Entity * > entityList, int weatherGrade)
{
    //srand (time(NULL));
    for(unsigned int i=0;i<entityList.size();i++)
    {
        int nb=rand()%100;
        switch(weatherGrade)
        {
            case 5:
                if(nb<=20){
                    entityList[i]->setisTired(true);
                }
                break;
            case 4:
                if(nb<=5){
                    entityList[i]->setisTired(true);
                }
                break;
            case -1:
                if(nb<=4){
                    entityList[i]->setisSick(true);
                }
                break;
            case -2:
                if(nb<=8){
                    entityList[i]->setisSick(true);
                }
                break;
            case -3:
                if(nb<=16){
                    entityList[i]->setisSick(true);
                }
                break;
            case -4:
                if(nb<=32){
                    entityList[i]->setisSick(true);
                }
                break;
            case -5:
                if(nb<=50){
                    entityList[i]->setisSick(true);
                }
                break;
            default:
                break;
        }
    }
}


WeatherType Weather::getWeatherYesterday()
{
    return m_weatherYesterday;
}

WeatherType Weather::getWeatherToday()
{
    return m_weatherToday;
}

int Weather::getWeatherGrade()
{
    return m_weatherGrade;
}

Animation* Weather::getRainAnimation()
{
    return m_rain;
}


void Weather::setWeatherToday(WeatherType m)
{
    m_weatherToday=m;
    //updateWeather();// à enlever après debug

}

void Weather::setWeatherYesterday(WeatherType m)
{
    m_weatherYesterday=m;
}

void Weather::setWeatherGrade(int n)
{
    m_weatherGrade=n;
}

void Weather::setRainAnimation(const string rainpath)
{
    initRain(rainpath);
}




