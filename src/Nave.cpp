#include "Nave.h"
#include <iostream>
#include <Game.h>
#include <stdlib.h>

int width = 1024;
int height = 768;

vector<Disparo*> balas(0);

Nave::Nave()
{
    velocidad = 0.3;

    //TEXTURAS DEL MODO DIOS

    g1 = new sf::Texture();
    g1->loadFromFile("images/god1.png");
    g2 = new sf::Texture();
    g2->loadFromFile("images/god2.png");
    g3 = new sf::Texture();
    g3->loadFromFile("images/god3.png");

    //Cargamos el sprite de la nave
    texture = new sf::Texture();

    texture->loadFromFile("images/pusat.png");
    texture2 = new sf::Texture();

    texture2->loadFromFile("images/pusat2.png");
    sprite = new sf::Sprite(*texture);

    sprite->setOrigin(82/2,97/2);
    sprite->setPosition(width/2, 600);

    //Cargamos la sombra de la nave
    text = new sf::Texture();

    text->loadFromFile("images/pusatsombra.png");
    sombra = new sf::Sprite(*text);
    sombra->setOrigin(82/2,97/2);
    sombra->setPosition(width/2, 715);
    sombra->scale(0.8f,0.8f);
    lastX = 0;
    lastY = 0;
    newX = 40;

}

//Getters
int Nave::getPuntos(){return puntos;}
int Nave::getVidas(){return vidas;}
int Nave::getDireccion(){return direccion;}
bool Nave::getMoviendose(){return moviendose;}
bool Nave::getGanador(){return ganador;}
float Nave::getVelocidad(){return velocidad;}
float Nave::getNewX(){return newX;}
sf::Sprite* Nave::getSprite(){return sprite;}
sf::Sprite* Nave::getSombra(){return sombra;}


vector<Disparo*> Nave::getBalas(){return balas;}

void Nave::limpiarBalas(){
    if(balas.size()>0){
        for(int i=0;i<balas.size();i++){
            if(balas.at(i)->getSprite()->getPosition().y<150){
                balas.erase(balas.begin());
                //cout << "Begin: " << balas.begin()->getSprite()->getPosition().y <<endl;
            }
        }
    }
}

void Nave::disparar(sf::RenderWindow& window){

    Disparo *dsp = new Disparo(sprite->getPosition().x, sprite->getPosition().y);
    balas.push_back(dsp);
    //window.draw(*sprite);

    std::cout << "HAS DISPARADO" <<endl;
}

void Nave::puntosAlien(alien *a, Nivel *n, int t){
    for(int i=0;i<balas.size();i++){
            if(a->getSprite()->getGlobalBounds().intersects(balas.at(i)->getSprite()->getGlobalBounds())){
                balas.erase(balas.begin());
                n->borrarAlien(0, t);
                sumaPuntos(50);
                cout << "*** Alien muerto ***" <<endl;
            }
        }
}

void Nave::puntosSaltador(Saltador *s, Nivel *n){
    for(int i=0;i<balas.size();i++){
            if(s->getSprite()->getGlobalBounds().intersects(balas.at(i)->getSprite()->getGlobalBounds())){
                balas.erase(balas.begin());
                n->borrarSaltador(0);
                sumaPuntos(100);
                cout << "*** Saltador muerto ***" <<endl;
            }
        }
}

bool Nave::puntosBoss(Boss *b, Nivel *n){

    for(int i=0;i<balas.size();i++){
            if(b->getSprite()->getGlobalBounds().intersects(balas.at(i)->getSprite()->getGlobalBounds())){
                balas.erase(balas.begin());

                sumaPuntos(500);
                cout << "*** Boss muerto ***" <<endl;
                return true;
            }
        }
        return false;
}

//Setters
void Nave::moverse(float _deltaTime, bool g){
int ra = rand() % 10;
    if(!g){
        if(ra>5){
            sprite->setTexture(*texture);
        }
        else{
            sprite->setTexture(*texture2);
        }
    }
    else{ //Modo dios
        if(ra>=3 && ra<6){
            sprite->setTexture(*g1);
        }
        else if(ra>=6){
            sprite->setTexture(*g2);
        }
        else{
            sprite->setTexture(*g3);
        }
    }
        //std::cout << moviendose << endl;
        if(moviendose){

            if((sprite->getPosition().x>100 && direccion==-1)||(sprite->getPosition().x<924 && direccion==1)){
            sprite->move(direccion*velocidad* _deltaTime,0);
            sombra->move(direccion*velocidad* _deltaTime,0);
        }
    }
}


void Nave::setGanador(){
    ganador=true;
}

void Nave::setVelocidad(float v){
velocidad=velocidad+v;
}

void Nave::sumaPuntos(int p){
puntos=puntos+p;
}

void Nave::vidaMenos(){
vidas--;
}



bool Nave::puntosTorre(sf::ConvexShape m){
    sf::FloatRect n = this->getSprite()->getGlobalBounds(); //Guarda la posicion de la nave
    sf::FloatRect meta = m.getGlobalBounds();
    if(meta.intersects(n)){
        return true;
    }
    return false;

}

bool Nave::choqueTorre(Torre *torreI, Torre *torreD){
    sf::FloatRect shape1 = torreI->getSprite()->getGlobalBounds(); //Guarda la posicion de la torreI
    sf::FloatRect shape2 = torreD->getSprite()->getGlobalBounds(); //Guarda la posicion de la torreD
    sf::FloatRect shape3 = this->getSprite()->getGlobalBounds(); //Guarda la posicion de la nave
    if (shape1.intersects(shape3) || shape2.intersects(shape3)){
        return true;
    }
    else
        return false;
}

bool Nave::choqueAlien(alien *a){
    sf::FloatRect shape1 = a->getSprite()->getGlobalBounds(); //Guarda la posicion del alien
    sf::FloatRect shape2 = this->getSprite()->getGlobalBounds(); //Guarda la posicion de la nave
    if (shape1.intersects(shape2)){
        return true;
    }
    else
        return false;
}

bool Nave::choqueMisil(Misil *m, Boss *b){
    sf::FloatRect shape1 = m->getSprite()->getGlobalBounds(); //Guarda la posicion del alien
    sf::FloatRect shape2 = this->getSprite()->getGlobalBounds(); //Guarda la posicion de la nave
    if (shape1.intersects(shape2)){
        b->limpiarBalas();
        return true;
    }
    else
        return false;
}

bool Nave::choqueSaltador(Saltador *s){
    sf::FloatRect shape1 = s->getSprite()->getGlobalBounds(); //Guarda la posicion del Saltador
    sf::FloatRect shape2 = this->getSprite()->getGlobalBounds(); //Guarda la posicion de la nave
    if (shape1.intersects(shape2)){
        return true;
    }
    else
        return false;
}

void Nave::setDireccion(int _dir){
    direccion = _dir;

    //Flipeamos el sprite
    if(direccion==-1){ //Izquierda
        sprite->setRotation(-5.f);
        sprite->setRotation(-15.f);
        sombra->setRotation(-5.f);
        sombra->setRotation(-15.f);
    }else if(direccion==1){ //Derecha
        sprite->setRotation(5.f);
        sprite->setRotation(15.f);
        sombra->setRotation(5.f);
        sombra->setRotation(15.f);
    }
    else if(direccion==2){ //Arriba

        if(sprite->getPosition().y>=height/1.5){
            sprite->move(0,-5);
        }
    }
    else if(direccion==-2){ //Abajo

        if(sprite->getPosition().y>=height/1.5){
            sprite->move(0,5);
        }
    }
    else{ //Quieto
        sprite->setRotation(0.f);
        sombra->setRotation(0.f);
    }
}
void Nave::setMoviendose(bool _moviendose){moviendose = _moviendose;}
void Nave::setNewX(float _x){newX = _x;}

Nave::~Nave()
{
    //dtor
}
