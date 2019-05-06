#ifndef NPC_H
#define NPC_H


#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
class NPC
{
    public:
        NPC();
        virtual ~NPC();
        sf::Texture *texture;
        sf::Sprite *sprite;
        sf::Texture *luz;
        sf::Sprite *vista;

        //Getters
        int getDireccion();
        bool getMoviendose();
        float getVelocidad();

        //Setters
        void setDireccion(int);
        void setMoviendose(bool);

        //Metodos
        virtual void moverse(float) = 0;



    protected:

        //Varialbes
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose =false; //Dice si se esta moviendo o no
        float velocidad;


        //Metodos


};

#endif // NPC_H
