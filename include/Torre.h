#ifndef TORRE_H
#define TORRE_H

#include "SFML/Graphics.hpp"
#include <iostream>
class Torre
{
    public:
        Torre();
        virtual ~Torre();
        sf::Sprite *getSprite();

        void mover(float, int, int); //Mueve la torre
        void ocultar();

    protected:

    private:
    protected:
        sf::Texture *txt;
        sf::Sprite *trr;
};

#endif // TORRE_H
