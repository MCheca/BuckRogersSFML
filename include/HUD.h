#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"
#include <iostream>

class HUD
{
    public:
        HUD();
        virtual ~HUD();
        sf::Text getPuntos();
        sf::Text getVidas();
        sf::Text getVictoria();
        void setPuntos(int);
        void setVidas(int);

    protected:

    private:
        sf::Text puntos;
        sf::Text vidas;
        sf::Text ganado;
        sf::Font font;

};

#endif // HUD_H
