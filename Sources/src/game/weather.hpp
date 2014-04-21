#ifndef _METEO_
#define _METEO_


#include "../engine/animation.hpp"
#include <vector>

typedef enum WeatherType {
	SUNNY,
	RAINY,
	UNDEFINED
} WeatherType;


class Weather
{
    public:

        Weather(const std::string pluiepath);//chemin pour animation de la pluie
        Weather(WeatherType weather,const std::string pluiepath);
        ~Weather();
        void updateWeather(); //fonction à appeler en fin de journée pour faire les incidences
        void initRain(const std::string pluiepath);
        void draw(sf::RenderTarget& target);
        bool verifWeather(WeatherType m,int nb);// regarde si le temps est apparu nb fois parmi les 5 derniers jours

        //getters
        WeatherType getWeather(unsigned int i);//du 4 ème jour avant aujourd'hui(i==0) à aujourd'hui(i==4)
        WeatherType getWeatherToday();
        int       getNbDSameWeather();//nombre de jours consécutifs du même temps que la journée
        Animation* getRainAnimation();

        //setters
        void setWeather(WeatherType m,unsigned int i);
        void setWeatherToday(WeatherType m);
        void setNbDSameWeather(int n);
        void setRainAnimation(const std::string pluiepath);


    private:
        std::vector<WeatherType> m_weatherList;
        WeatherType m_weatherToday;
        int       m_nbDSameWeather;
        Animation* m_rain;

};
#endif
