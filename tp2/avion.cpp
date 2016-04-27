#include "avion.hpp"

using namespace std;

Avion::Avion(string idSprite,int velocidadDesplazamiento,string idSpriteAnimacion,Disparo unDisparo){
	this->idSprite = idSprite;
	this->velocidadDesplazamiento = velocidadDesplazamiento;
	this->idSpriteAnimacion = idSpriteAnimacion;
	this->disparo = unDisparo;
}

Avion::Avion(){
	this->gAvionTextura = new Figura();
	this->posX = 400;
	this->posY = 0;
	this->velocidadX = 0;
	this->velocidadY = 0;
	this->velocidad = 500;
}
Avion::~Avion(){

}

void Avion::manejarEvento(SDL_Event evento){
	if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP: this->velocidadY -= this->velocidad; break;
            case SDLK_DOWN: this->velocidadY += this->velocidad; break;
            case SDLK_LEFT: this->velocidadX -= this->velocidad; break;
            case SDLK_RIGHT: this->velocidadX += this->velocidad; break;
        }
    }
    //If a key was released
    else if( evento.type == SDL_KEYUP && evento.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP: this->velocidadY += this->velocidad; break;
            case SDLK_DOWN: this->velocidadY -= this->velocidad; break;
            case SDLK_LEFT: this->velocidadX += this->velocidad; break;
            case SDLK_RIGHT: this->velocidadX -= this->velocidad; break;
        }
    }
}

void Avion::mover(float timeStep){
//Move the dot left or right
    this->posX += this->velocidadX * timeStep;
    //If the dot went too far to the left or right
    if( this->posX < 0 ){
			this->posX = 0;
		}else if( this->posX + 25 > 800){
        //Move back
        this->posX = 775;
    }
    //Move the dot up or down
    this->posY += this->velocidadY * timeStep;
    //If the dot went too far up or down
    if( this->posY < 0 ){
			this->posY = 0;
		} else if ( this->posY > 600 - 25 ){
        //Move back
        this->posY = 575;
    }
}

string Avion::getIdSprite(){
	return this->idSprite;
}

void Avion::setIdSprite(string idSprite){
	this->idSprite = idSprite;
}

int Avion::getVelocidadDesplazamiento(){
	return this->velocidadDesplazamiento;
}

void Avion::setVelocidadDesplazamiento(int velocidadDesplazamiento){
	this->velocidadDesplazamiento = velocidadDesplazamiento;
}

string Avion::getIdSpriteAnimacion(){
	return this->idSpriteAnimacion;
}

void Avion::setIdSpriteAnimacion(string idSpriteAnimacion){
	this->idSpriteAnimacion = idSpriteAnimacion;
}
Disparo Avion::getDisparo() {
	return this->disparo;
}

void Avion::setDisparo(Disparo unDisparo) {
	this->disparo = unDisparo;
}

int Avion::cargarImagen(string path, SDL_Renderer* renderer){
	if(!this->gAvionTextura->loadFromFile(path, renderer)){
		cout << "Failed" << endl;
		//TODO usar una excepcion
		return 0;
	}
	this->render(renderer);
	return 1;
}

void Avion::render(SDL_Renderer* renderer){
	this->gAvionTextura->render((int)this->posX, (int)this->posY, renderer);
	SDL_RenderPresent(renderer);
}

void Avion::cerrar(){
	this->gAvionTextura->free();
}

SDL_Renderer* Avion::getAvionRenderer(){
	return this->gAvionRenderer;
}

Figura* Avion::getAvionTextura(){
	return this->gAvionTextura;
}

float Avion::getPosicionX(){
	return this->posX;
}
float Avion::getPosicionY(){
	return this->posY;
}

int Avion::getAncho(){
	return AVION_ANCHO;
}
int Avion::getAlto(){
	return AVION_ALTO;
}
