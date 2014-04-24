#ifndef _METEO_
#define _METEO_


#include "../engine/animation.hpp"
#include "entity/entity.hpp"
#include <ctime>
#include <cstdlib>


typedef enum WeatherType {
	SUNNY,
	RAINY,
	UNDEFINED
} WeatherType;


class Entity;

class Weather
{
    public:

        Weather(const std::string rainpath);//chemin pour animation de la pluie
        Weather(WeatherType weather,const std::string rainpath);
        ~Weather();
        void updateWeather(); //fonction à appeler en fin de journée pour faire les incidences
        void initRain(const std::string rainpath);
        void draw(sf::RenderTarget& target);

        //Incidences sur les entités
        void impactsOnEntities(std::vector< Entity * > entityList, int weatherGrade);

        //getters
        WeatherType getWeatherYesterday();
        WeatherType getWeatherToday();
        int       getWeatherGrade();
        Animation* getRainAnimation();

        //setters
        void setWeatherYesterday(WeatherType m);
        void setWeatherToday(WeatherType m);
        void setWeatherGrade(int n);
        void setRainAnimation(const std::string rainpath);


    private:
        WeatherType m_weatherYesterday;
        WeatherType m_weatherToday;
        int       m_weatherGrade;
        Animation* m_rain;

};
#endif
