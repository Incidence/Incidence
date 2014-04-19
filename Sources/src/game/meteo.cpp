
#include "meteo.hpp"


using namespace std;


Meteo::Meteo( const string pluiepath)
{
    //Meteo par d�faut Soleil
    m_tempsToday=SOLEIL;
    m_tempsHier=UNDEFINED;
    m_nbJMemeTemps=0;
    m_pluie=new Animation();
    initPluie(pluiepath);
}

Meteo::Meteo(MeteoType temps,const string pluiepath)
{
    m_tempsToday=temps;
    m_tempsHier=UNDEFINED;
    m_nbJMemeTemps=0;
    m_pluie=new Animation();
    initPluie(pluiepath);
}

Meteo::~Meteo(){}



void Meteo::updateMeteo()
{
    if(m_tempsHier==m_tempsToday)
    {
        m_nbJMemeTemps++;
    }
    else
    {
        m_tempsHier=m_tempsToday;
        m_nbJMemeTemps=1;
    }
}

void Meteo::initPluie(const string pluiepath)
{
    m_pluie->load(pluiepath);
}

void Meteo::draw(sf::RenderTarget& target)
{
    switch (m_tempsToday)
    {
    case PLUIE:
        m_pluie->draw(target);
        break;

    default:
        break;
    }
}


MeteoType Meteo::getTempsHier()
{
    return m_tempsHier;
}

MeteoType Meteo::getTempsToday()
{
    return m_tempsToday;
}

int Meteo::getNbJMemeTemps()
{
    return m_nbJMemeTemps;
}

Animation* Meteo::getAnimationPluie()
{
    return m_pluie;
}


void Meteo::setTempsToday(MeteoType m)
{
    m_tempsToday=m;
}

void Meteo::setTempsHier(MeteoType m)
{
    m_tempsHier=m;
}

void Meteo::setNbJMemeTemps(int n)
{
    m_nbJMemeTemps=n;
}

void Meteo::setAnimationPluie(const string pluiepath)
{
    initPluie(pluiepath);
}




