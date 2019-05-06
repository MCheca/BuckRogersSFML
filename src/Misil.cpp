#include "Misil.h"
#include <iostream>

using namespace std;

Misil::Misil(int x, int y)
{
    //Cargamos el sprite del Misil
    txt = new sf::Texture();

    txt->loadFromFile("images/misil.png");
    dsp = new sf::Sprite(*txt);
    dsp->setOrigin(20/2, 78/2);
    dsp->setPosition(x, y+25);

}

sf::Sprite* Misil::getSprite(){return dsp;}

void Misil::mover(float _deltaTime){
    dsp->move(0,0.3*_deltaTime);
}

Misil::~Misil()
{
    //dtor
}
