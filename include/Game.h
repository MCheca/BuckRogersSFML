#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "Nave.h"
#include "Nivel.h"
#include "Torre.h"
#include "Disparo.h"
#include "NPC.h"
#include "alien.h"
#include "Boss.h"
#include "HUD.h"

using namespace std;

//int width = 1024;
//int height = 768;

class Game
{
    public:
        //Singleton
        static Game *getInstance(){
            if(unicaInstancia == 0)
                unicaInstancia = new Game(1024,768,"BuckRogers Orbit");

            return unicaInstancia;
        }
        //Fin del Singleton

        void gameLoop(); //Bucle mientras que la ventana este abierta
        void draw(sf::Sprite); //Metodo para dibujar todo
        void eventsLoop(); //Metodo para detetar los eventos

        //Getters
        sf::RenderWindow* getWindow();
        virtual ~Game();

    protected:

    private:
        Game(int,int,string);
        static Game *unicaInstancia;
        int velocidad;
//        vector<Disparo> *balas;


        sf::RenderWindow *window; //La ventana
        sf::Event *event; //Para manejar los eventos
        sf::Time deltaTime; //Tiempo trascurrido entre cada frame

        sf::Clock clock; //Utilizado para mostrar aliens
        sf::Clock deltaClock; //utilizado para moviemientos
        sf::Clock updateClock;
        Nave *nave; //Nuestra nave
        Nivel *nivel;
        HUD *hud;
        Torre *torreI;
        Torre *torreD;

};

#endif // GAME_H
