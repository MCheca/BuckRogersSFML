#include "alien.h"

#include <iostream>
#include <Game.h>
#include <stdlib.h>     /* srand, rand */
//Constructor del alien
alien::alien(float x, float y)
{
    velocidad = 0.3;
    int dir=1;
    int raDir = rand() % 10;

    if(raDir<5){
        xdir=-1;
    }
    subiendo=false;
    texture = new sf::Texture();

    texture->loadFromFile("images/vagrant.png");
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(x,y);
    std::cout << "Creado alien";

}

sf::Sprite* alien::getSprite(){return sprite;}

void alien::moverse(float _deltaTime){

    //std::cout << "La posi y es: " << sprite->getPosition().y <<endl;


        int ray = rand() % 600;
        ray=ray-150;
        int diry= rand() % 7;
        int dirx= rand() % 4;
        if(sprite->getPosition().y>=740){
            subiendo=true;
        }
        else if(sprite->getPosition().y<0){
            //this.~alien();
        }
        if(subiendo){
            dir=-1;
            xdir=xdir*-1;
        }
        else{
           dir=1;
        }
        sprite->move(xdir*2*0.05*_deltaTime,dir*0.05*diry*_deltaTime);

}


alien::~alien()
{
    //dtor
}
