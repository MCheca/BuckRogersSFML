#include "Boss.h"

#include <iostream>
#include <Game.h>
#include <stdlib.h>     /* srand, rand */

using namespace std;
//Constructor del Boss
Boss::Boss()
{
    velocidad = 0.3;
    int dir=1;

    int raDir = rand() % 10;

    if(raDir<5){
        xdir=-1;
    }
    texture = new sf::Texture();

    texture->loadFromFile("images/devolarium.png");
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(900,100);
    std::cout << "Creado Boss";

}

sf::Sprite* Boss::getSprite(){return sprite;}
vector<Misil*> Boss::getMisiles(){return misiles;}

void Boss::moverse(float _deltaTime){


        if(sprite->getPosition().y<300 && sprite->getPosition().x>500){
            sprite->move(-1*6*0.05*_deltaTime,0.05*_deltaTime);
        }
        else{
            if(sprite->getPosition().y<350){
                sprite->move(0,0.05*_deltaTime);
            }
            else{
                if(metros<60){
                    sprite->move(1*0.05*_deltaTime,0);
                    metros++;
                }
                else{
                    sprite->move(-1*0.05*_deltaTime,0);
                    metros++;
                    if(metros==120){
                        metros=0;
                    }
                }
            }
        }


}

void Boss::disparar(float _deltaTime){
float time1 = clock.getElapsedTime().asMilliseconds();

    //if(sprite->getPosition().y<350){
        if(time1>3000){ //DISPARA CADA 3 SEGUNDOS

            Misil *msaux = new Misil(sprite->getPosition().x, sprite->getPosition().y);
            misiles.push_back(msaux);
            time1 = clock.restart().asMilliseconds();
        }
   // }

}

void Boss::borrarMisil(){
    misiles.erase(misiles.begin());
}

void Boss::limpiarBalas(){
    if(misiles.size()>0){
        for(int i=0;i<misiles.size();i++){
            if(misiles.at(i)->getSprite()->getPosition().y>760){
                misiles.erase(misiles.begin());
            }
        }
    }
}

Boss::~Boss()
{
    //dtor
}
