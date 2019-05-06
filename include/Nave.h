#ifndef Nave_H
#define Nave_H

#include <Nave.h>
#include "Torre.h"
#include "Disparo.h"
#include "alien.h"
#include "Saltador.h"
#include "Nivel.h"
#include "Misil.h"
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace std;

class Nave
{
    public:
        Nave();

        //Getters
        int getDireccion();
        int getVidas();
        int getPuntos();
        bool getMoviendose();
        bool getGanador();
        float getVelocidad();
        float getNewX();
        sf::Sprite *getSprite();
        sf::Sprite *getSombra();

        vector<Disparo*> getBalas();


        //Setters
        void setDireccion(int);
        void setMoviendose(bool);
        void setNewX(float);
        void setGanador();

        //Metodos
        void moverse(float, bool);
        void sumaPuntos(int);
        void vidaMenos();
        void setVelocidad(float);
        bool puntosTorre(sf::ConvexShape);
        void puntosAlien(alien*, Nivel*, int);
        void puntosSaltador(Saltador*, Nivel*);
        bool puntosBoss(Boss*, Nivel*);
        void disparar(sf::RenderWindow&);
        void limpiarBalas();
        bool choqueTorre(Torre*, Torre*);
        bool choqueAlien(alien* a);
        bool choqueMisil(Misil* m, Boss* b);
        bool choqueSaltador(Saltador* s);
        void moverseInterpolado(float,float);
        void nuevoEstado(float, float);






        virtual ~Nave();


    private:


        protected:

        //Variables
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose = false; //Dice si se esta moviendo o no
        float velocidad=0.1;
        float newX = 0;
        float lastX = 0;
        float lastY;
        int puntos=0;
        int vidas=7;
        bool ganador=false;
        sf::Texture *texture;
        sf::Texture *texture2;
        sf::Texture *g1; //textura modo dios
        sf::Texture *g2; //textura modo dios
        sf::Texture *g3; //textura modo dios
        sf::Sprite *sprite;
        sf::Texture *text;
        sf::Sprite *sombra;
        Disparo *dps;
        vector<Disparo*> balas;

};

#endif // Nave_H
