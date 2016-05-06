#include "avionVista.hpp"

void AvionVista::actualizar(string codigo){
    memcpy((void*) &(this->posX), (void*) &(codigo[0]), sizeof(float));
    memcpy((void*) &(this->posY), (void*) &(codigo[sizeof(float)]), sizeof(float));
    estadoAnimacion = (int) codigo[2*sizeof(float)];
}

//TODO ver de donde sacar las dimensiones del avion
AvionVista::AvionVista(float posX, float posY){
    this->posX = posX;
    this->posY = posY;
    this->estadoAnimacion = 0;

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

    //Primer sprite vuelta
    this->clipsAnimacion[3].x = 0 + AVION_ANCHO * 3;
    this->clipsAnimacion[3].y = 0;
    this->clipsAnimacion[3].w = AVION_ANCHO;
    this->clipsAnimacion[3].h = AVION_ALTO;

    //Segundo sprite vuelta
    this->clipsAnimacion[4].x = 0 + AVION_ANCHO * 4;
    this->clipsAnimacion[4].y = 0;
    this->clipsAnimacion[4].w = AVION_ANCHO;
    this->clipsAnimacion[4].h = AVION_ALTO;

    //Tercer sprite vuelta
    this->clipsAnimacion[5].x = 0;
    this->clipsAnimacion[5].y = 0 + AVION_ALTO;
    this->clipsAnimacion[5].w = AVION_ANCHO;
    this->clipsAnimacion[5].h = AVION_ALTO;

}

float AvionVista::getPosX(){
    return this->posX;
}

void AvionVista::setPosX(float posX){
    this->posX = posX;
}

void AvionVista::setPosY(float posY){
    this->posY = posY;
}

float AvionVista::getPosY(){
    return this->posY;
}

void AvionVista::majenarEvento(SDL_Event evento){
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 )
    {
			if((this->estadoAnimacion < 3)){
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP:
				this->cliente->enviarEvento(ARRIBA_PRESIONA);
				break;
            case SDLK_DOWN:
                this->cliente->enviarEvento(ABAJO_PRESIONA);
				break;
            case SDLK_LEFT:
                this->cliente->enviarEvento(IZQUIERDA_PRESIONA);
				break;
            case SDLK_RIGHT:
				this->cliente->enviarEvento(DERECHA_PRESIONA);
				break;
			case SDLK_SPACE:
				this->cliente->enviarEvento(PRESIONA_ESPACIO);
				break;
			case SDLK_RETURN:
				this->cliente->enviarEvento(PRESIONA_ENTER);
				break;
				}
			}
    }
    else if( evento.type == SDL_KEYUP && evento.key.repeat == 0 )
    {
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP:
				this->cliente->enviarEvento(ARRIBA_SUELTA);
				break;
            case SDLK_DOWN:
				this->cliente->enviarEvento(ABAJO_SUELTA);
				break;
            case SDLK_LEFT:
				this->cliente->enviarEvento(IZQUIERDA_SUELTA);
				break;
            case SDLK_RIGHT:
                this->cliente->enviarEvento(DERECHA_SUELTA);
				break;
        }
    }
}

int AvionVista::cargarImagen(string path, SDL_Renderer* renderer){
	if(!this->figuraAvion->loadFromFile(path, renderer, 1)){
		cout << "Failed" << endl;
		//TODO usar una excepcion
		return 0;
	}
	this->render(renderer);
	return 1;
}

void AvionVista::render(SDL_Renderer* renderer){
	this->figuraAvion->render((int)this->posX, (int)this->posY, renderer, &this->clipsAnimacion[this->estadoAnimacion]);
}

void AvionVista::cerrar(){
	this->figuraAvion->free();
}

Figura* AvionVista::getFiguraAvion(){
	return this->figuraAvion;
}

void AvionVista::setFiguraAvion(Figura * figura){
    this->figuraAvion = figura;
}

int AvionVista::getEstadoAnimacion(){
    return this->estadoAnimacion;
}

void AvionVista::setEstadoAnimacion(int estadoAnimacion){
    this->estadoAnimacion = estadoAnimacion;
}
