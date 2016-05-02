#include "avion.hpp"

using namespace std;

Avion::Avion(float velocidadDesplazamiento, float velocidadDisparos, string avionSpriteId, string vueltaSpriteId, string disparosSpriteId){
	this->gAvionTextura = new Figura();
	this->posX = 400;
	this->posY = 600;
	this->velocidadX = 0;
	this->velocidadY = 0;
	this->velocidad = 500;
	this->idSprite = avionSpriteId;
	this->idSpriteVuelta = vueltaSpriteId;
	this->idSpriteDisparo = disparosSpriteId;
	this->velocidadDesplazamiento = velocidadDesplazamiento;
	this->velocidadDisparos = velocidadDisparos;
	this->idSpriteAnimacion = idSpriteAnimacion;


	//Avión en estado normal
	this->clipsAnimacion[0].x = 0;
	this->clipsAnimacion[0].y = 0;
	this->clipsAnimacion[0].w = AVION_ANCHO;
	this->clipsAnimacion[0].h = AVION_ALTO;

	//Avión moviéndose a la izquierda
	this->clipsAnimacion[1].x = 0 + AVION_ANCHO;
	this->clipsAnimacion[1].y = 0;
	this->clipsAnimacion[1].w = AVION_ANCHO;
	this->clipsAnimacion[1].h = AVION_ALTO;

	//Avión moviéndose a la derecha
	this->clipsAnimacion[2].x = 0 + AVION_ANCHO * 2;
	this->clipsAnimacion[2].y = 0;
	this->clipsAnimacion[2].w = AVION_ANCHO;
	this->clipsAnimacion[2].h = AVION_ALTO;

	this->estadoAnimacion = 0;
}
Avion::~Avion(){

}

void Avion::manejarEvento(SDL_Event evento, SDL_Renderer * renderer){
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP:
				this->velocidadY -= this->velocidad;
				break;
            case SDLK_DOWN:
				this->velocidadY += this->velocidad;
				break;
            case SDLK_LEFT:
				this->velocidadX -= this->velocidad;
				this->estadoAnimacion = 1;
				break;
            case SDLK_RIGHT:
				this->estadoAnimacion = 2;
				this->velocidadX += this->velocidad;
				break;
						case SDLK_SPACE:
				this->disparos.push_front(new Disparo(this->posX + (this->getAncho() / 2.f) - (this->getAnchoDisparo() / 2.f), this->posY - this->getAltoDisparo(), this->velocidadDisparos, this->idSpriteDisparo, renderer));
				case SDLK_RETURN:
					this->estadoAnimacion = 3;
				}
    }
    //If a key was released
    else if( evento.type == SDL_KEYUP && evento.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP:
				this->velocidadY += this->velocidad;
				break;
            case SDLK_DOWN:
				this->velocidadY -= this->velocidad;
				break;
            case SDLK_LEFT:
				this->velocidadX += this->velocidad;
				if( !currentKeyStates[ SDL_SCANCODE_RIGHT ])
					this->estadoAnimacion = 0;
				break;
            case SDLK_RIGHT:
				this->velocidadX -= this->velocidad;
				if( !currentKeyStates[ SDL_SCANCODE_LEFT ])
					this->estadoAnimacion = 0;
				break;
        }
    }
}

void Avion::mover(float timeStep){
//Move the dot left or right
    this->posX += this->velocidadX * timeStep;
    //If the dot went too far to the left or right
    if( this->posX < 0 ){
			this->posX = 0;
		}else if( this->posX + 80 > 800){
        //Move back
        this->posX = 720;
    }
    //Move the dot up or down
    this->posY += this->velocidadY * timeStep;
    //If the dot went too far up or down
    if( this->posY < 0 ){
			this->posY = 0;
		} else if ( this->posY + 80 > 800){
        //Move back
        this->posY = 720;
    }
}

void Avion::moverDisparos(float timeStep){
	if(this->disparos.size() > 0){
		for(list<Disparo*>::iterator iterador = disparos.begin(); iterador != disparos.end(); iterador++){
			if((*iterador)->mover(timeStep) == 0){
				delete (*iterador);
				iterador = disparos.erase(iterador);
			}
		}
	}
}

void Avion::renderDisparos(SDL_Renderer * renderer){
	if(disparos.size() > 0 ){
		for(list<Disparo*>::iterator iterator = disparos.begin(); iterator != disparos.end(); iterator++){
			(*iterator)->render(renderer);
		}
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
list<Disparo*> Avion::getDisparos() {
	return this->disparos;
}

void Avion::setDisparos(list<Disparo*> unosDisparos) {
	this->disparos = unosDisparos;
}

int Avion::cargarImagen(string path, SDL_Renderer* renderer){
	if(!this->gAvionTextura->loadFromFile(path, renderer, 1)){
		cout << "Failed" << endl;
		//TODO usar una excepcion
		return 0;
	}
	this->render(renderer);
	return 1;
}

void Avion::render(SDL_Renderer* renderer){
	this->gAvionTextura->render((int)this->posX, (int)this->posY, renderer, &this->clipsAnimacion[this->estadoAnimacion]);
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

int Avion::getAnchoDisparo(){
	return DISPARO_ANCHO;
}
int Avion::getAltoDisparo(){
	return DISPARO_ALTO;
}
