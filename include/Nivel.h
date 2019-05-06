#ifndef NIVEL_H
#define NIVEL_H

#include <Nivel.h>
#include "Torre.h"
#include "NPC.h"
#include "alien.h"
#include "Boss.h"
#include "Saltador.h"
#include "SFML/Graphics.hpp"
#include <iostream>
class Nivel
{
    public:
    Nivel(int);
    void setBoss(int);
    void aliens(int, sf::Int32, int);
    void torres(float, int);
    void resetTorres();
    void setDireccion(int);
    void setMoviendose(bool);
    void moverse(float);
    void setVelocidad(float);
    void borrarAlien(int, int);
    void borrarSaltador(int);
    int getNivel();
    int getTorres();
    sf::Sprite *getSprite();
    sf::Sprite *getPlaneta();
    sf::Sprite *getSuelo();
    Torre *getTorreI();
    Torre *getTorreD();
    vector<alien*> getAliens();
    vector<alien*> getAliensB1();
    vector<alien*> getAliensB2();
    vector<Saltador*> getSaltador();
    Boss *getjefe();
    bool getBoss();

        virtual ~Nivel();

    protected:

    private:

        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose = false; //Dice si se esta moviendo o no

        /*SEGUIR POR AQUI -> MOVIMIENTO DEL FONDO*/

    protected:
        sf::Clock clock;
        sf::Texture *bagr;
        sf::Sprite *bg;
        sf::Texture *planeta;
        sf::Sprite *planeta5;
        sf::Sprite *sSuelo;

        sf::Texture *suelo6;
        sf::Texture *suelo5;
        sf::Texture *suelo4;
        sf::Texture *suelo3;
        sf::Texture *suelo2;
        sf::Texture *suelo1;

        sf::Texture *suelo26;
        sf::Texture *suelo25;
        sf::Texture *suelo24;
        sf::Texture *suelo23;
        sf::Texture *suelo22;
        sf::Texture *suelo21;

        sf::Texture *suelo36;
        sf::Texture *suelo35;
        sf::Texture *suelo34;
        sf::Texture *suelo33;
        sf::Texture *suelo32;
        sf::Texture *suelo31;


        Torre *torreI;
        Torre *torreD;
        float vmon = 0.1;
        int cTorres=0;
        bool boss=false;
        bool primera=true;
        bool pBoss=true;
        int caliens=50;
        int csaltadores=30;
        vector<alien*> aliensNPC;
        vector<Saltador*> saltadorNPC;
        vector<alien*> aliensBOSS1;
        vector<alien*> aliensBOSS2;
        Boss *jefe;
        int nivel=1;
};

#endif // NIVEL_H
