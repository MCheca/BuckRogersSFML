#include "Torre.h"
#include <iostream>
using namespace std;
Torre::Torre()
{
    //Cargamos el sprite de la torre
    txt = new sf::Texture();

    txt->loadFromFile("images/torre.png");
    trr = new sf::Sprite(*txt);
    trr->setOrigin(80/2,167/2);
    //trr->setPosition(1024/2, 500);

}

sf::Sprite* Torre::getSprite(){return trr;}

void Torre::mover(float _deltaTime, int velocidad, int direccion){
float v = (float)(velocidad/10);
v=v/10;
        //if(v>0){
            trr->move(direccion*(_deltaTime*0.1+(2*v)),_deltaTime*0.3+(1.4*v));
            trr->setScale(0.5*(trr->getPosition().y/320),0.5*(trr->getPosition().y/320));
       // }
        /*else{
            trr->move(direccion*_deltaTime*0.1+(2*v),_deltaTime*0.3+(2*v));
            trr->setScale(0.5*(trr->getPosition().y/320),0.5*(trr->getPosition().y/320));
        }*/
}

void Torre::ocultar(){
    trr->setScale(0.0,0.0);
}

Torre::~Torre()
{
    //dtor
}
