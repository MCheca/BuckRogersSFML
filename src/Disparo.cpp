#include "Disparo.h"
#include <iostream>

using namespace std;

Disparo::Disparo(int x, int y)
{
    //Cargamos el sprite del disparo
    txt = new sf::Texture();

    txt->loadFromFile("images/shot.png");
    dsp = new sf::Sprite(*txt);
    dsp->setOrigin(20/2, 78/2);
    dsp->setPosition(x, y+25);

}

sf::Sprite* Disparo::getSprite(){return dsp;}

void Disparo::mover(float _deltaTime){
    dsp->move(0,-0.5*_deltaTime);
}

Disparo::~Disparo()
{
    //dtor
}
