#ifndef SALTADOR_H
#define SALTADOR_H

#include <NPC.h>


class Saltador : public NPC
{
    public:
        Saltador(float, float);
        virtual ~Saltador();
        sf::Sprite *getSprite();
        void moverse(float); //Funcion para moverse




    private:
//        Saltador();


        //Metodos


        int dir;
        bool subiendo;


    protected:



};



#endif // SALTADOR_H
