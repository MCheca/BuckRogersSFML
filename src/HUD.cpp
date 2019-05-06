#include "HUD.h"
#include <iostream>
#include <string>
#include <sstream>

namespace strint
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

using namespace std;

HUD::HUD()
{

    if(!font.loadFromFile("Minecraft.ttf")){
        cout << "*** No se puede cargar la fuente ***" <<endl;
    }
    puntos.setFont(font);
    puntos.setString("Hola mundo");
    puntos.setCharacterSize(24);
    puntos.setColor(sf::Color::White);
    puntos.setOrigin(0,0);
    puntos.setPosition(10,10);

    vidas.setFont(font);
    vidas.setString("Hola mundo");
    vidas.setCharacterSize(24);
    vidas.setColor(sf::Color::White);
    vidas.setOrigin(0,0);
    vidas.setPosition(880,10);

    ganado.setFont(font);
    ganado.setString("Enhorabuena, has ganado!");
    ganado.setCharacterSize(24);
    ganado.setColor(sf::Color::White);
    ganado.setOrigin(0,0);
    ganado.setPosition(400,300);
}

sf::Text HUD::getPuntos(){return puntos;}
sf::Text HUD::getVidas(){return vidas;}
sf::Text HUD::getVictoria(){return ganado;}

void HUD::setPuntos(int p){
    puntos.setString("Puntos: " + strint::to_string(p));
}
void HUD::setVidas(int p){
    vidas.setString("Vidas: " + strint::to_string(p));
}

HUD::~HUD()
{
    //dtor
}
