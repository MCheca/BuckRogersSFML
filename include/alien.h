#ifndef ALIEN_H
#define ALIEN_H

#include <NPC.h>


class alien : public NPC
{
    public:
        alien(float, float);
        virtual ~alien();
        sf::Sprite *getSprite();
        void moverse(float); //Funcion para moverse




    private:
//        alien();


        //Metodos


        int dir;
        bool subiendo;
        int xdir=1;


    protected:



};

#endif // alien_H
