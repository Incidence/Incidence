
#include "weather.hpp"


using namespace std;


Weather::Weather( const string rainpath)
{
    //Meteo par défaut Soleil
    m_weatherToday=SUNNY;
    m_weatherYesterday=UNDEFINED;
    m_nbDSameWeather=0;
    m_rain=new Animation();
    initRain(rainpath);
}

Weather::Weather(WeatherType weather,const string rainpath)
{
    m_weatherToday=weather;
    m_weatherYesterday=UNDEFINED;
    m_nbDSameWeather=0;
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
    if(m_weatherToday==m_weatherYesterday)
    {
        m_nbDSameWeather++;
    }
    else
    {
        m_weatherYesterday=m_weatherToday;
        m_nbDSameWeather=1;
    }
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


WeatherType Weather::getWeatherYesterday()
{
    return m_weatherYesterday;
}

WeatherType Weather::getWeatherToday()
{
    return m_weatherToday;
}

int Weather::getNbDSameWeather()
{
    return m_nbDSameWeather;
}

Animation* Weather::getRainAnimation()
{
    return m_rain;
}


void Weather::setWeatherToday(WeatherType m)
{
    m_weatherToday=m;
}

void Weather::setWeatherYesterday(WeatherType m)
{
    m_weatherYesterday=m;
}

void Weather::setNbDSameWeather(int n)
{
    m_nbDSameWeather=n;
}

void Weather::setRainAnimation(const string rainpath)
{
    initRain(rainpath);
}




