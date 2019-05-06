#ifndef DISPARO_H
#define DISPARO_H

#include "SFML/Graphics.hpp"
#include <iostream>

class Disparo
{
    public:
        Disparo(int x, int y);
        virtual ~Disparo();
        sf::Sprite *getSprite();
        void mover(float);

        //Metodos

    protected:

    private:
    protected:
        sf::Texture *txt;
        sf::Sprite *dsp;
};

#endif // DISPARO_H
