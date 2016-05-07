#include "escenarioJuego.hpp"

void EscenarioJuego::reset(){
	// TODO
}

EscenarioJuego::EscenarioJuego(float velocidadDesplazamientoY){
	this->velocidadDesplazamientoY = velocidadDesplazamientoY;
    scrollingOffset = 0;
    posicionY = 0;
}

EscenarioJuego::~EscenarioJuego(){}

float EscenarioJuego::getOffset() {
    return offset;
}

void EscenarioJuego::manejarEvento(int nroAvion, char evento) {
	list<Avion*>::iterator iterador = aviones.begin();
	switch(evento){
		case PRESIONA_R: reset();
			break;
		case PRESIONA_ESPACIO:
			iterador = aviones.begin();
			advance(iterador, nroAvion - 1);
			disparos.push_back ((*iterador)->disparar());
			// TODO Hay que hacerle delete a esto en algún momento.
			break;
		default:
			// NOTE ojo, tienen que estar en orden los aviones.
			iterador = aviones.begin();
			advance(iterador, nroAvion - 1);
			(*iterador)->manejarEvento(evento);
			break;
	}
}

void EscenarioJuego::actualizarScrollingOffset(float timeStep) {
    scrollingOffset = scrollingOffset + timeStep * velocidadDesplazamientoY;
}

void* EscenarioJuego::mainLoop_th(void* THIS){
    EscenarioJuego* escenario = (EscenarioJuego*) THIS;
    bool quit = false;
    Temporizador temporizador;
    while(!quit){
        float timeStep = escenario->temporizador.getTicks() / 1000.f;
        escenario->actualizarScrollingOffset(timeStep);
		escenario->posicionY = escenario->posicionY + timeStep * escenario->velocidadDesplazamientoY;
        // TODO Por qué se comienza acá de todos los lugares? Fucking lazyfoo.
        temporizador.comenzar();
        escenario->moverAviones(timeStep);
		escenario->moverElementos(timeStep);
        escenario->moverDisparos(timeStep);
    }

    pthread_exit(NULL);
}

void EscenarioJuego::mainLoop(){
    pthread_create(&mainLoopThread, NULL, mainLoop_th, (void*)this);
}

void EscenarioJuego::moverAviones(float timeStep){
	for(list<Avion*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
		Avion* avion = *iterador;
		avion->mover(timeStep);
		//avion->moverDisparos(timeStep);
	}
}

void EscenarioJuego::moverElementos(float timeStep){
	for(list<Elemento*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
		Elemento* elemento = *iterador;
		elemento->mover(timeStep);
	}
}

void EscenarioJuego::moverDisparos(float timeStep){
	if(this->disparos.size() > 0){
		for(list<Disparo*>::iterator iterador = disparos.begin(); iterador != disparos.end(); iterador++){
			if((*iterador)->mover(timeStep) == 0){
				delete (*iterador);
				iterador = disparos.erase(iterador);
			}
		}
	}
}

/* getters */
list<Avion*>& EscenarioJuego::getAviones(){
	return this->aviones;
}


list<Elemento*>& EscenarioJuego::getElementos(){
	return this->elementos;
}
