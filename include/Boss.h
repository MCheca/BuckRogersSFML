#ifndef BOSS_H
#define BOSS_H

#include "Misil.h"

#include <NPC.h>


class Boss : public NPC
{
    public:
        Boss();
        virtual ~Boss();
        sf::Sprite *getSprite();
        void moverse(float); //Funcion para moverse
        vector<Misil*> getMisiles();
        void disparar(float);
        void borrarMisil();
        void limpiarBalas();




    private:
//        Boss();


        //Metodos


        int dir;
        bool baja;
        int xdir=1;
        int metros=0;


    protected:
        sf::Clock clock;
        vector<Misil*> misiles;



};

#endif // BOSS_H
