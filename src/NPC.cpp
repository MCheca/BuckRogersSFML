#include "NPC.h"

NPC::NPC()
{
    //ctor
}


//Getters
int NPC::getDireccion(){return direccion;}
bool NPC::getMoviendose(){return moviendose;}
float NPC::getVelocidad(){return velocidad;}


//Setters
void NPC::setDireccion(int _dir){
    direccion = _dir;

    //Flipeamos el sprite
    if(direccion==-1){
        sprite->setTextureRect(sf::IntRect(sprite->getTexture()->getSize().x,0,-sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
        vista->setScale(-1,1);
    }else{
        sprite->setTextureRect(sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
        vista->setScale(1,1);
    }
}
void NPC::setMoviendose(bool _moviendose){moviendose = _moviendose;}


NPC::~NPC()
{
    //dtor
}
