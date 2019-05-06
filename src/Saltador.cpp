#include "Saltador.h"

#include <iostream>
#include <Game.h>
#include <stdlib.h>     /* srand, rand */
//Constructor del Saltador
Saltador::Saltador(float x, float y)
{
    velocidad = 0.3;
    int dir=1;
    subiendo=false;
    texture = new sf::Texture();

    texture->loadFromFile("images/lordakia.png");
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(x,y);
    std::cout << "Creado Saltador";

}

sf::Sprite* Saltador::getSprite(){return sprite;}

void Saltador::moverse(float _deltaTime){

    //std::cout << "La posi y es: " << sprite->getPosition().y <<endl;
        int raDir = rand() % 10;
        int xdir=1;
        if(raDir<5){
            xdir=-1;
        }
        int ray = rand() % 600;
        ray=ray-150;
        int diry= rand() % 7;
        int dirx= rand() % 4;
        if(sprite->getPosition().y>=740){
            subiendo=true;
        }
        else if(sprite->getPosition().y<0){
            //this.~Saltador();
        }
        if(subiendo){
            dir=-1;
        }
        else{
           dir=1;
        }
        sprite->move(xdir*0.05*dirx*_deltaTime,dir*0.03*diry*_deltaTime);

}


Saltador::~Saltador()
{
    //dtor
}
