#ifndef _METEO_
#define _METEO_


#include "../engine/animation.hpp"

typedef enum WeatherType {
	SUNNY,
	RAINY,
	UNDEFINED
} WeatherType;


class Weather
{
    public:

        Weather(const std::string rainpath);//chemin pour animation de la pluie
        Weather(WeatherType weather,const std::string rainpath);
        ~Weather();
        void updateWeather(); //fonction � appeler en fin de journ�e pour faire les incidences
        void initRain(const std::string rainpath);
        void draw(sf::RenderTarget& target);

        //getters
        WeatherType getWeatherYesterday();
        WeatherType getWeatherToday();
        int       getNbDSameWeather();//nombre de jours cons�cutifs du m�me temps que la journ�e
        Animation* getRainAnimation();

        //setters
        void setWeatherYesterday(WeatherType m);
        void setWeatherToday(WeatherType m);
        void setNbDSameWeather(int n);
        void setRainAnimation(const std::string rainpath);


    private:
        WeatherType m_weatherYesterday;
        WeatherType m_weatherToday;
        int       m_nbDSameWeather;
        Animation* m_rain;

};
#endif
