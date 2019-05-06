#ifndef MISIL_H
#define MISIL_H


#include "SFML/Graphics.hpp"
#include <iostream>

class Misil
{
    public:
        Misil(int x, int y);
        virtual ~Misil();
        sf::Sprite *getSprite();
        void mover(float);

        //Metodos

    protected:

    private:
    protected:
        sf::Texture *txt;
        sf::Sprite *dsp;
};

#endif // MISIL_H
