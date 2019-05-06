#include "Nivel.h"
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
//#include <Clock.hpp>    /* reloj */
using namespace sf;
using namespace std;


int roadW = 2000;
int segL = 200; //segment length
float camD = 0.84; //camera depth
float x=0,dx=0;
int maxy = 768;
int pos = 0;
int tAliens=10;
int startPos = pos/segL;
bool entra=false;
Torre *torreI;
Torre *torreD;
alien *cAliens[10];
vector<alien*> aliensNPC(0);
vector<alien*> aliensBOSS1(0);
vector<alien*> aliensBOSS2(0);
vector<Saltador*> saltadorNPC(0);

   float playerX = 0;
   int H = 1500;
   int speed=100;

Nivel::Nivel(int n)
{
    nivel = n;
    if(n==3){
        caliens=100;
        csaltadores=80;
    }
    else if(n==1){
        caliens=50;
        csaltadores=30;
    }
    else if(n==2){
        caliens=80;
        csaltadores=50;
    }
    vmon = 0.5;
    for(int i=0;i<caliens;i++){
        int ra = rand() % 800;
        alien *aaux = new alien(ra,100+i*10);
        aliensNPC.push_back(aaux);
    }
    for(int i=0;i<csaltadores;i++){
        int ra = rand() % 800;
        Saltador *saux = new Saltador(ra,100+i*10);
        saltadorNPC.push_back(saux);
    }
    torreI = new Torre();
    torreD = new Torre();
        torreI->getSprite()->setPosition(1024/5, 350);
        torreD->getSprite()->setPosition(2.5*1024/5, 350);

//Cargamos la imagen de fondo
    bagr = new sf::Texture();

    bagr->loadFromFile("images/bg.jpg");
    bagr->setRepeated(true);

    bg = new sf::Sprite(*bagr);
    bg->setPosition(-2000,0);
    bg->setTextureRect(IntRect(500,500,5000,150));

//Cargamos el planeta (Parallax)

    planeta = new sf::Texture();

    planeta->loadFromFile("images/mountain.png");
    planeta->setRepeated(true);

    planeta5 = new sf::Sprite(*planeta);
    planeta5->setTextureRect(IntRect(0,0,10240,150));
    planeta5->setOrigin(10240/2,150/2);
    planeta5->setPosition(0,150/2);

//Cargamos el suelo

    suelo1 = new sf::Texture();
    suelo2 = new sf::Texture();
    suelo3 = new sf::Texture();
    suelo4 = new sf::Texture();
    suelo5 = new sf::Texture();
    suelo6 = new sf::Texture();

    suelo1->loadFromFile("images/suelo01.png");
    suelo2->loadFromFile("images/suelo02.png");
    suelo3->loadFromFile("images/suelo03.png");
    suelo4->loadFromFile("images/suelo04.png");
    suelo5->loadFromFile("images/suelo05.png");
    suelo6->loadFromFile("images/suelo06.png");

    suelo21 = new sf::Texture();
    suelo22 = new sf::Texture();
    suelo23 = new sf::Texture();
    suelo24 = new sf::Texture();
    suelo25 = new sf::Texture();
    suelo26 = new sf::Texture();

    suelo21->loadFromFile("images/suelo201.png");
    suelo22->loadFromFile("images/suelo202.png");
    suelo23->loadFromFile("images/suelo203.png");
    suelo24->loadFromFile("images/suelo204.png");
    suelo25->loadFromFile("images/suelo205.png");
    suelo26->loadFromFile("images/suelo206.png");

    suelo31 = new sf::Texture();
    suelo32 = new sf::Texture();
    suelo33 = new sf::Texture();
    suelo34 = new sf::Texture();
    suelo35 = new sf::Texture();
    suelo36 = new sf::Texture();

    suelo31->loadFromFile("images/suelo301.png");
    suelo32->loadFromFile("images/suelo302.png");
    suelo33->loadFromFile("images/suelo303.png");
    suelo34->loadFromFile("images/suelo304.png");
    suelo35->loadFromFile("images/suelo305.png");
    suelo36->loadFromFile("images/suelo306.png");



    //suelo3->setRepeated(true);

    if(nivel==3){
        sSuelo = new sf::Sprite(*suelo31);
    }
    else if(nivel==2){
        sSuelo = new sf::Sprite(*suelo21);
    }
    else{
        sSuelo = new sf::Sprite(*suelo1);
    }
        sSuelo->setTextureRect(IntRect(0,0,1024,619));
        sSuelo->setOrigin(0,0);
        sSuelo->setPosition(0,150);



}

void Nivel::setBoss(int n){
    boss=true;
    sSuelo->setScale(0.0,0.0);
    planeta5->setScale(0.0,0.0);
    bg->setTextureRect(IntRect(500,500,5000,1500));
    aliensNPC.clear();
    saltadorNPC.clear();
    if(n==0){
        if(primera){
            for(int i=0;i<10;i++){
                int ra = rand() % 800;
                alien *aaux = new alien(ra,100+i*10);
                aliensBOSS1.push_back(aaux);
            }
            for(int i=0;i<10;i++){
                int ra = rand() % 800;
                alien *aaux = new alien(ra,100+i*10);
                aliensBOSS2.push_back(aaux);
            }
            primera=false;
        }
    }
    else if(n==1){
        aliensBOSS1.clear();
        aliensBOSS2.clear();
        if(pBoss){
            jefe = new Boss();
            pBoss=false;
        }
    }

}

//GETTERS
int Nivel::getNivel(){return nivel;}
sf::Sprite* Nivel::getSprite(){return bg;}
sf::Sprite* Nivel::getPlaneta(){return planeta5;}
sf::Sprite* Nivel::getSuelo(){return sSuelo;}
int Nivel::getTorres(){return cTorres;}

Torre* Nivel::getTorreI(){return torreI;}
Torre* Nivel::getTorreD(){return torreD;}

vector<alien*> Nivel::getAliens(){return aliensNPC;}
vector<alien*> Nivel::getAliensB1(){return aliensBOSS1;}
vector<alien*> Nivel::getAliensB2(){return aliensBOSS2;}
vector<Saltador*> Nivel::getSaltador(){return saltadorNPC;}
Boss* Nivel::getjefe(){return jefe;}


void Nivel::torres(float _deltaTime, int velocidad){
    if(!boss){
        if(torreI->getSprite()->getPosition().y<960){
            torreI->mover(_deltaTime, velocidad, direccion);
            torreD->mover(_deltaTime, velocidad, direccion);
        }
        else{
            int ra = rand() % 600;
            ra=ra-150;
            int separacion= rand() % 70; //separacion entre las dos torres
            //std::cout << separacion <<endl;
            torreI->getSprite()->setPosition(ra+1024/5, 150);
            torreD->getSprite()->setPosition(ra+2.5*1024/5+separacion, 150);
            cTorres++;
        }
    }
    else{
        torreI->ocultar();
        torreD->ocultar();
    }
}

void Nivel::resetTorres(){
    int ra = rand() % 600;
        ra=ra-150;
        int separacion= rand() % 70; //separacion entre las dos torres
        //std::cout << separacion <<endl;
        torreI->getSprite()->setPosition(ra+1024/5, 150);
        torreD->getSprite()->setPosition(ra+2.5*1024/5+separacion, 150);
}

void Nivel::aliens(int c, sf::Int32 _deltaTime,int tipo){

        if(tipo==0){
            aliensNPC.at(c)->moverse(_deltaTime);
        }
        else if(tipo==1){
            saltadorNPC.at(c)->moverse(_deltaTime);
        }
        if(tipo==2){
            aliensBOSS1.at(c)->moverse(_deltaTime);
        }
        if(tipo==3){
            aliensBOSS2.at(c)->moverse(_deltaTime);
        }


}

 void Nivel::borrarAlien(int n, int t){
    if(t==0){
        if(aliensNPC.size()>0){
            aliensNPC.erase(aliensNPC.begin()+n);
        }
    }
    else if(t==1){
        if(aliensBOSS1.size()>0){
            aliensBOSS1.erase(aliensBOSS1.begin()+n);
        }
    }
    else if(t==2){
        if(aliensBOSS2.size()>0){
            aliensBOSS2.erase(aliensBOSS2.begin()+n);
        }
    }

 }

  void Nivel::borrarSaltador(int n){

    if(saltadorNPC.size()>0){
        saltadorNPC.erase(saltadorNPC.begin()+n);
    }

 }


void Nivel::setDireccion(int _dir){direccion = _dir;}
void Nivel::setMoviendose(bool _moviendose){moviendose = _moviendose;}

void Nivel::moverse(float _deltaTime){
    //Movimiento lineal


float time1 = clock.getElapsedTime().asMilliseconds();

    //cout << "La VMON: " <<time1 << " --> " << (vmon*100) <<endl;
    int t=900-(((vmon*1000)-20)*1.5);
    if(time1>0 && time1<=t){
    if(nivel==3){
        sSuelo = new sf::Sprite(*suelo31);
        sSuelo->setTextureRect(IntRect(0,0,1024,619));
        sSuelo->setOrigin(0,0);
        sSuelo->setPosition(0,150);
    }
    else if(nivel==2){
        sSuelo = new sf::Sprite(*suelo21);
        sSuelo->setTextureRect(IntRect(0,0,1024,619));
        sSuelo->setOrigin(0,0);
        sSuelo->setPosition(0,150);
    }
    else
        sSuelo->setTexture(*suelo1);
    }
    else if(time1>t && time1<=t*2){
        if(nivel==3){
            sSuelo = new sf::Sprite(*suelo32);
            sSuelo->setTextureRect(IntRect(0,0,1024,619));
            sSuelo->setOrigin(0,0);
            sSuelo->setPosition(0,150);
        }
        else if(nivel==2){
        sSuelo = new sf::Sprite(*suelo22);
        sSuelo->setTextureRect(IntRect(0,0,1024,619));
        sSuelo->setOrigin(0,0);
        sSuelo->setPosition(0,150);
        }
        else
        sSuelo->setTexture(*suelo2);
    }
    else if(time1>t*2 && time1<=t*3){
        if(nivel==3){
            sSuelo = new sf::Sprite(*suelo33);
            sSuelo->setTextureRect(IntRect(0,0,1024,619));
            sSuelo->setOrigin(0,0);
            sSuelo->setPosition(0,150);
        }
        else if(nivel==2){
            sSuelo = new sf::Sprite(*suelo23);
            sSuelo->setTextureRect(IntRect(0,0,1024,619));
            sSuelo->setOrigin(0,0);
            sSuelo->setPosition(0,150);
        }
        else
        sSuelo->setTexture(*suelo3);
    }
    else if(time1>t*3 && time1<=t*4){
        if(nivel==3){
            sSuelo = new sf::Sprite(*suelo34);
            sSuelo->setTextureRect(IntRect(0,0,1024,619));
            sSuelo->setOrigin(0,0);
            sSuelo->setPosition(0,150);
        }
        else if(nivel==2){
        sSuelo = new sf::Sprite(*suelo24);
        sSuelo->setTextureRect(IntRect(0,0,1024,619));
        sSuelo->setOrigin(0,0);
        sSuelo->setPosition(0,150);
        }
        else
        sSuelo->setTexture(*suelo4);
    }
    else if(time1>t*4 && time1<=t*5){
        if(nivel==3){
            sSuelo = new sf::Sprite(*suelo35);
            sSuelo->setTextureRect(IntRect(0,0,1024,619));
            sSuelo->setOrigin(0,0);
            sSuelo->setPosition(0,150);
        }
        else if(nivel==2){
            sSuelo = new sf::Sprite(*suelo25);
            sSuelo->setTextureRect(IntRect(0,0,1024,619));
            sSuelo->setOrigin(0,0);
            sSuelo->setPosition(0,150);
        }
        else
        sSuelo->setTexture(*suelo5);
    }
    else if(time1>t*5){
        if(nivel==3){
            sSuelo = new sf::Sprite(*suelo36);
            sSuelo->setTextureRect(IntRect(0,0,1024,619));
            sSuelo->setOrigin(0,0);
            sSuelo->setPosition(0,150);
        }
        else if(nivel==2){
            sSuelo = new sf::Sprite(*suelo26);
            sSuelo->setTextureRect(IntRect(0,0,1024,619));
            sSuelo->setOrigin(0,0);
            sSuelo->setPosition(0,150);
        }
        else
        sSuelo->setTexture(*suelo6);
        time1 = clock.restart().asMilliseconds();
    }

    //Movimiento lateral
    if(moviendose){
        planeta5->move(direccion*vmon* _deltaTime,0);
        bg->move(direccion*vmon*0.1* _deltaTime,0);
    }
}

void Nivel::setVelocidad(float v){
vmon=vmon+v;
}

bool Nivel::getBoss(){
    return boss;
}

Nivel::~Nivel()
{
    //dtor
}
