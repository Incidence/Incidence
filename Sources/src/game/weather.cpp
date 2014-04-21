
#include "weather.hpp"


using namespace std;


Weather::Weather( const string pluiepath)
{
    //Meteo par défaut Soleil
    for(int i=0;i<4;i++)
    {
        m_weatherList.push_back(UNDEFINED);
    }
    m_weatherToday=SUNNY;
    m_weatherList.push_back(m_weatherToday);
    m_nbDSameWeather=0;
    m_rain=new Animation();
    initRain(pluiepath);
}

Weather::Weather(WeatherType weather,const string pluiepath)
{
    for(int i=0;i<4;i++)
    {
        m_weatherList.push_back(UNDEFINED);
    }
    m_weatherToday=weather;
    m_weatherList.push_back(m_weatherToday);
    m_nbDSameWeather=0;
    m_rain=new Animation();
    initRain(pluiepath);
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
    if(m_weatherList[3]==m_weatherList[4])
    {
        m_nbDSameWeather++;
    }
    else
    {
        m_nbDSameWeather=1;
    }
    m_weatherList.erase(m_weatherList.begin());
    m_weatherList.push_back(UNDEFINED);
}

void Weather::initRain(const string pluiepath)
{
    m_rain->load(pluiepath);
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

bool Weather::verifWeather(WeatherType m,int nb)
{
    int times=0;
   for(unsigned int i=0;i<m_weatherList.size();i++)
   {
       if(m_weatherList[i]==m)
       {
           times++;
       }
   }

   return times==nb;
}


WeatherType Weather::getWeather(unsigned int i)
{
    if(i>=0 && i<m_weatherList.size())
    {
        return m_weatherList[i];
    }
    else {
		return UNDEFINED;
	}
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

void Weather::setWeather(WeatherType m,unsigned int i)
{
    if(i>=0 && i<m_weatherList.size())
    {
        m_weatherList[i]=m;
    }
}

void Weather::setNbDSameWeather(int n)
{
    m_nbDSameWeather=n;
}

void Weather::setRainAnimation(const string pluiepath)
{
    initRain(pluiepath);
}




