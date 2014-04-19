#ifndef _METEO_
#define _METEO_


#include "../engine/animation.hpp"
#include <vector>

typedef enum MeteoType {
	SOLEIL,
	PLUIE,
	UNDEFINED
} MeteoType;


class Meteo
{
    public:

        Meteo(const std::string pluiepath);//chemin pour animation de la pluie
        Meteo(MeteoType temps,const std::string pluiepath);
        ~Meteo();
        void updateMeteo(); //fonction à appeler en fin de journée pour faire les incidences
        void initPluie(const std::string pluiepath);
        void draw(sf::RenderTarget& target);

        //getters
        MeteoType getTempsHier();
        MeteoType getTempsToday();
        int       getNbJMemeTemps();//nombre de jours consécutifs du même temps que la journée
        Animation* getAnimationPluie();

        //setters
        void setTempsHier(MeteoType m);
        void setTempsToday(MeteoType m);
        void setNbJMemeTemps(int n);
        void setAnimationPluie(const std::string pluiepath);


    private:
        MeteoType m_tempsHier;
        MeteoType m_tempsToday;
        int       m_nbJMemeTemps;
        Animation* m_pluie;

};
#endif
