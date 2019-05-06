#include <iostream>
#include <math.h>
#include <algorithm>
#include "Game.h"


using namespace std;

Game* Game::unicaInstancia=0;
int velocidad=200;

//vector<Disparo> *balas =new vector<Disparo>();
bool una=true;
bool god=false;
int n=0;
int nAlien=0;
int nAB=0;

Game::Game(int x, int y, string title)
{

    window = new sf::RenderWindow(sf::VideoMode(x,y),title);
    event = new sf::Event();
    window->setFramerateLimit(90);

    nave = new Nave();

    nivel = new Nivel(1);

    hud = new HUD();

    //GameLoop, infinity iterations
    gameLoop();
}

void Game::draw(sf::Sprite s){
    window->draw(s);
}

//Function that executes once per frame
void Game::gameLoop(){

    while(window->isOpen()){
        deltaTime = deltaClock.restart();

        eventsLoop();
        window->clear();

            //Dibujamos todos los sprites

if(!nave->getGanador()){
        window->draw(*nivel->getSuelo()); //
        window->draw(*nivel->getSprite()); //
        window->draw(*nivel->getPlaneta()); //
        window->draw(*nivel->getTorreI()->getSprite());
        window->draw(*nivel->getTorreD()->getSprite());

        nave->moverse(deltaTime.asMilliseconds(), god);
        nivel->moverse(deltaTime.asMilliseconds());

        if(!nivel->getBoss()){
            // Linea que une las dos torres
            sf::ConvexShape meta;

            meta.setPointCount(4);

            meta.setPoint(0, sf::Vector2f(nivel->getTorreI()->getSprite()->getPosition().x, nivel->getTorreI()->getSprite()->getPosition().y));
            meta.setPoint(1, sf::Vector2f(nivel->getTorreI()->getSprite()->getPosition().x, nivel->getTorreI()->getSprite()->getPosition().y+1));
            meta.setPoint(2, sf::Vector2f(nivel->getTorreD()->getSprite()->getPosition().x, nivel->getTorreD()->getSprite()->getPosition().y));
            meta.setPoint(3, sf::Vector2f(nivel->getTorreD()->getSprite()->getPosition().x, nivel->getTorreD()->getSprite()->getPosition().y+1));

            if(nave->puntosTorre(meta)){
                nave->sumaPuntos(10);
            }
        }


        if(nivel->getAliens().size()>0 && nivel->getSaltador().size()>0){
            nave->puntosAlien(nivel->getAliens().at(nAlien/1000), nivel, 0);
            nave->puntosSaltador(nivel->getSaltador().at(nAlien/1000), nivel);
        }
        if(nivel->getBoss()){
            if(nivel->getAliensB1().size()>0 && nivel->getAliensB2().size()>0){
                nave->puntosAlien(nivel->getAliensB1().at(nAB/700), nivel, 1);
                nave->puntosAlien(nivel->getAliensB2().at(nAB/700), nivel, 2);

                window->draw(*nivel->getAliensB1().at(nAB/700)->getSprite());
                window->draw(*nivel->getAliensB2().at(nAB/700)->getSprite());
                nivel->aliens(nAB/700,deltaTime.asMilliseconds(),2);
                nivel->aliens(nAB/700,deltaTime.asMilliseconds(),3);
                if(!god){
                    if(nivel->getAliensB1().size()>0 && nivel->getAliensB2().size()>0){
                        if(nave->choqueAlien(nivel->getAliensB1().at(nAB/700)) || nave->choqueAlien(nivel->getAliensB2().at(nAB/700))){
                            nave->vidaMenos();
                            nivel->borrarAlien(nAB/700,1);
                        }
                        if(nave->choqueAlien(nivel->getAliensB2().at(nAB/700))){
                            nave->vidaMenos();
                            nivel->borrarAlien(nAB/700,2);
                        }
                    }
                }
            }
            else{
                //cout << "Viene el boss" <<endl;
            }

            nAB++;
        }



    //Nivel 1
    if(nave->getPuntos()>=1000 && nave->getPuntos()<5000 && nivel->getNivel()==1){ //1000
        window->draw(*nivel->getAliens().at(nAlien/1000)->getSprite());
        nivel->aliens(nAlien/1000,deltaTime.asMilliseconds(),0);
        nAlien++;
    }
    if(nave->getPuntos()>=2000 && nave->getPuntos()<5000 && nivel->getNivel()==1){ //2000
        window->draw(*nivel->getSaltador().at(nAlien/1000)->getSprite());
        nivel->aliens(nAlien/1000,deltaTime.asMilliseconds(),1);
    }
    if(nave->getPuntos()>=5000 && nave->getPuntos()<5200 && nivel->getNivel()==1){ //5000
        //FASE 1 BOSS
        nivel->setBoss(0);
    }
    if(nave->getPuntos()>=5200 && nivel->getNivel()==1){
        //FASE 2 BOSS
        nivel->setBoss(1);
        nivel->getjefe()->moverse(deltaTime.asMilliseconds());
        window->draw(*nivel->getjefe()->getSprite());
        if(nivel->getjefe()->getSprite()->getPosition().y>=300){

            nivel->getjefe()->disparar(deltaTime.asMilliseconds());
            nivel->getjefe()->limpiarBalas();
            if(nivel->getjefe()->getMisiles().size()>0){
                nivel->getjefe()->getMisiles().at(0)->mover(deltaTime.asMilliseconds());
                window->draw(*nivel->getjefe()->getMisiles().at(0)->getSprite());

                if(!god){
                    if(nave->choqueMisil(nivel->getjefe()->getMisiles().at(0), nivel->getjefe())){
                        nivel->getjefe()->borrarMisil();
                        nave->vidaMenos();
                    }
                }
            }
            if(nave->puntosBoss(nivel->getjefe(), nivel)){
                nivel = new Nivel(2);
                nAlien=0;
            }
        }
    }
    //NIVEL 2
    if(nave->getPuntos()>=5900 && nave->getPuntos()<9500 && nivel->getNivel()==2){ //1000
        window->draw(*nivel->getAliens().at(nAlien/1000)->getSprite());
        nivel->aliens(nAlien/1000,deltaTime.asMilliseconds(),0);
        nAlien++;
    }
    if(nave->getPuntos()>=6200 && nave->getPuntos()<9500 && nivel->getNivel()==2){ //2000
        window->draw(*nivel->getSaltador().at(nAlien/1000)->getSprite());
        nivel->aliens(nAlien/1000,deltaTime.asMilliseconds(),1);
    }
        if(nave->getPuntos()>=9500 && nivel->getNivel()==2){
        //FASE 2 BOSS
        nivel->setBoss(1);
        nivel->getjefe()->moverse(deltaTime.asMilliseconds());
        window->draw(*nivel->getjefe()->getSprite());
        if(nivel->getjefe()->getSprite()->getPosition().y>=300){

            nivel->getjefe()->disparar(deltaTime.asMilliseconds());
            nivel->getjefe()->limpiarBalas();
            if(nivel->getjefe()->getMisiles().size()>0){
                nivel->getjefe()->getMisiles().at(0)->mover(deltaTime.asMilliseconds());
                window->draw(*nivel->getjefe()->getMisiles().at(0)->getSprite());

                if(!god){
                    if(nave->choqueMisil(nivel->getjefe()->getMisiles().at(0), nivel->getjefe())){
                        nivel->getjefe()->borrarMisil();
                        nave->vidaMenos();
                    }
                }
            }
            if(nave->puntosBoss(nivel->getjefe(), nivel)){
                nAlien=0;
                nivel = new Nivel(3);
            }
        }
    }

    //NIVEL 3
    if(nave->getPuntos()>=10000 && nave->getPuntos()<15000 && nivel->getNivel()==3){ //1000
        window->draw(*nivel->getAliens().at(nAlien/1000)->getSprite());
        nivel->aliens(nAlien/1000,deltaTime.asMilliseconds(),0);
        nAlien++;
    }
    if(nave->getPuntos()>=10000 && nave->getPuntos()<15000 && nivel->getNivel()==3){ //2000
        window->draw(*nivel->getSaltador().at(nAlien/1000)->getSprite());
        nivel->aliens(nAlien/1000,deltaTime.asMilliseconds(),1);
    }
        if(nave->getPuntos()>=15000 && nivel->getNivel()==3){
        //FASE 2 BOSS
        nivel->setBoss(1);
        nivel->getjefe()->moverse(deltaTime.asMilliseconds());
        window->draw(*nivel->getjefe()->getSprite());
        if(nivel->getjefe()->getSprite()->getPosition().y>=300){

            nivel->getjefe()->disparar(deltaTime.asMilliseconds());
            nivel->getjefe()->limpiarBalas();
            if(nivel->getjefe()->getMisiles().size()>0){
                nivel->getjefe()->getMisiles().at(0)->mover(deltaTime.asMilliseconds());
                window->draw(*nivel->getjefe()->getMisiles().at(0)->getSprite());

                if(!god){
                    if(nave->choqueMisil(nivel->getjefe()->getMisiles().at(0), nivel->getjefe())){
                        nivel->getjefe()->borrarMisil();
                        nave->vidaMenos();
                    }
                }
            }
            if(nave->puntosBoss(nivel->getjefe(), nivel)){
                nAlien=0;

                nave->setGanador();
                cout << "HAS GANADO" <<endl;
            }
        }
    }


    if(!god){
        if(nave->choqueTorre(nivel->getTorreI(),nivel->getTorreD())){
            nave->vidaMenos();
            nivel->resetTorres();
        }
        if(nivel->getAliens().size()>0 && nivel->getSaltador().size()>0){
            if(nave->choqueAlien(nivel->getAliens().at(nAlien/1000))){
                nave->vidaMenos();
                nivel->borrarAlien(nAlien/1000, 0);
            }
            if(nave->choqueSaltador(nivel->getSaltador().at(nAlien/1000))){
                nave->vidaMenos();
                nivel->borrarSaltador(nAlien/1000);
            }
        }
    }

    window->draw(*nave->getSombra()); //
    window->draw(*nave->getSprite()); //
    /*if(debug){
        window->draw(nave->getSprite().getGlobalBounds());
    }*/
    if(nave->getBalas().size()>0){
        for(int i=0;i<nave->getBalas().size();i++){

            nave->getBalas().at(i)->mover(deltaTime.asMilliseconds());
            window->draw(*nave->getBalas().at(i)->getSprite());

        }
    }

    hud->setPuntos(nave->getPuntos());
    hud->setVidas(nave->getVidas());
    window->draw(hud->getPuntos());
    window->draw(hud->getVidas());
    //window->draw(meta); //--> La linea que une las torres
    nave->limpiarBalas();
    nivel->torres(deltaTime.asMilliseconds(), velocidad);


if(nave->getVidas()==0){

        cout << "GAME OVER" <<endl;

        nave = new Nave();

        nivel = new Nivel(1);

        hud = new HUD();
}
}
else{
    window->draw(hud->getVictoria());
}
        window->display();
    }
}

void Game::eventsLoop(){

    while(window->pollEvent(*event)){

        switch(event->type){

            //Presiona la tecla
            case sf::Event::KeyPressed:
                switch(event->key.code){

                    case sf::Keyboard::Escape:

                        window->close();
                        break;

                    case sf::Keyboard::Space:

                        nave->disparar(*window);

                        break;

                    case sf::Keyboard::Up: //Presiona la W
                        if(nave->getSprite()->getPosition().y>=768/1.4){
                            nave->getSprite()->move(0,-5);
                            nave->getSombra()->scale(0.99f,0.99f);
                            nave->setVelocidad(0.01);
                            nivel->setVelocidad(0.01);
                            velocidad=velocidad+10;
                        }
                        break;

                    case sf::Keyboard::Down: //Presiona la S
                        if(nave->getSprite()->getPosition().y<=610){
                            nave->getSprite()->move(0,5);
                            nave->getSombra()->scale(1.01f,1.01f);
                            nave->setVelocidad(-0.01);
                            nivel->setVelocidad(-0.01);
                            velocidad=velocidad-10;
                        }
                        break;

                    case sf::Keyboard::Right: //Presiona la D
                        nave->setDireccion(1);
                        nave->setMoviendose(true);
                        nivel->setDireccion(-1);
                        nivel->setMoviendose(true);

                        break;

                    case sf::Keyboard::Left: //Presiona la A
                        nave->setDireccion(-1);
                        nave->setMoviendose(true);
                        nivel->setDireccion(1);
                        nivel->setMoviendose(true);

                        break;

                    case sf::Keyboard::G: //Presiona la G
                        if(god){
                            god=false;
                        }
                        else{
                            god=true;
                        }
                        break;

                    case sf::Keyboard::Q: //Presiona la Q
                        window->close();
                        break;

                    default:
                        break;


                }//End KeyPressed event
                break;


            //Levanta la tecla
            case sf::Event::KeyReleased:
                switch(event->key.code){

                    case sf::Keyboard::Right:
                        nave->setDireccion(0);
                        nave->setMoviendose(false);
                        nivel->setDireccion(0);
                        nivel->setMoviendose(false);

                        break;

                    case sf::Keyboard::Left:
                        nave->setDireccion(0);
                        nave->setMoviendose(false);
                        nivel->setDireccion(0);
                        nivel->setMoviendose(false);

                        break;
                    case sf::Keyboard::Up:

                        break;

                }//End KeyReleased event
                break;

            //Hit close button
            case sf::Event::Closed:

                window->close();
                break;



        }//End switch event type




    }//End events loop


}

sf::RenderWindow* Game::getWindow(){return window;}


Game::~Game()
{
    //dtor
}
