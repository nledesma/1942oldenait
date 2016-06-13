#include "superficie.hpp"

Superficie::Superficie(float x, float y, int ancho, int alto, int offSetX, int offSetY){
    this->offSetX = offSetX;
    this->offSetY = offSetY;
    this->izqAbajo = new Punto(x + offSetX, y + offSetY);
    this->izqArriba = new Punto(x + offSetX, y + alto + offSetY);
    this->derArriba = new Punto(x + ancho + offSetX, y + alto + offSetY);
    this->derAbajo = new Punto(x + ancho + offSetX, y + offSetY);
    this->ancho = ancho;
    this->alto = alto;
}

Punto* Superficie::getIzqAbajo(){
    return this->izqAbajo;
}

Punto* Superficie::getIzqArriba(){
    return this->izqArriba;
}

Punto* Superficie::getDerArriba(){
    return this->derArriba;
}

Punto* Superficie::getDerAbajo(){
    return this->derAbajo;
}

void Superficie::mover(float x, float y){
    this->izqAbajo->mover(x + this->offSetX, y + this->offSetY);
    this->derAbajo->mover(x + this->ancho + this->offSetX, y + this->offSetY);
    this->derArriba->mover(x + this->ancho + this->offSetX, y + this->alto + this->offSetY);
    this->izqArriba->mover(x + this->offSetX, y + this->alto + this->offSetY);
}

int Superficie::getAlto(){
    return this->alto;
}

int Superficie::getAncho(){
    return this->ancho;
}

int Superficie::getOffsetX(){
    return this->offSetX;
}

int Superficie::getOffsetY() {
    return this->offSetY;
}

void Superficie::rotar(float angulo, float x, float y, int tipoElemento){
    if(tipoElemento == TIPO_AVION_PEQUENIO || tipoElemento == TIPO_AVION_ESCUADRON || tipoElemento == TIPO_AVION_MEDIANO ){
        if (angulo > 0) {
            this->izqAbajo->rotar(angulo, x, y);
            this->izqArriba->rotar(angulo, x, y);
            this->derArriba->rotar(angulo, x, y);
            this->derAbajo->rotar(angulo, x, y);
        }
    }
}

bool Superficie::colisiona(Superficie * superficie){
    Punto* normalArriba = new Punto(-(this->izqArriba->getPosY() - this->derArriba->getPosY()), this->izqArriba->getPosX() - this->derArriba->getPosX());
    Punto* normalDerecha = new Punto(-(this->derArriba->getPosY() - this->derAbajo->getPosY()), this->derArriba->getPosX() - this->derAbajo->getPosX());
    Punto* normalAbajo = new Punto(-(this->derAbajo->getPosY() - this->izqAbajo->getPosY()), this->derAbajo->getPosX() - this->izqAbajo->getPosX());
    Punto* normalIzquierda = new Punto(-(this->izqAbajo->getPosY() - this->izqArriba->getPosY()), this->izqAbajo->getPosX() - this->izqArriba->getPosX());

    pair<float, float> proyeccion = this->proyectar(this, normalArriba);
    pair<float, float> proyeccionSuperficie = this->proyectar(superficie, normalArriba);
    if(!this->proyeccionesSuperpuestas(proyeccion, proyeccionSuperficie)){
        return false;
    }

    proyeccion = this->proyectar(this, normalDerecha);
    proyeccionSuperficie = this->proyectar(superficie, normalDerecha);

    if(!this->proyeccionesSuperpuestas(proyeccion, proyeccionSuperficie)){
        return false;
    }

    proyeccion = this->proyectar(this, normalAbajo);
    proyeccionSuperficie = this->proyectar(superficie, normalAbajo);

    if(!this->proyeccionesSuperpuestas(proyeccion, proyeccionSuperficie)){
        return false;
    }

    proyeccion = this->proyectar(this, normalIzquierda);
    proyeccionSuperficie = this->proyectar(superficie, normalIzquierda);

    if(!this->proyeccionesSuperpuestas(proyeccion, proyeccionSuperficie)){
        return false;
    }

    return true;

}

pair<float, float> Superficie::proyectar(Superficie * superficie, Punto * punto){

    //TODO ver si se hace refactor con los puntos
    float minimo, maximo;
    minimo = maximo = punto->productoPunto(superficie->getDerArriba());
    float producto = punto->productoPunto(superficie->getDerAbajo());
    if(producto > maximo) {
        maximo = producto;
    }

    if(producto < minimo) {
        minimo = producto;
    }

    producto = punto->productoPunto(superficie->getIzqAbajo());

    if(producto > maximo) {
        maximo = producto;
    }

    if(producto < minimo) {
        minimo = producto;
    }

    producto = punto->productoPunto(superficie->getIzqArriba());

    if(producto > maximo) {
        maximo = producto;
    }

    if(producto < minimo) {
        minimo = producto;
    }

    pair<float, float> resultado;
    resultado.first = maximo;
    resultado.second = minimo;
    return resultado;
}

bool Superficie::proyeccionesSuperpuestas(pair<float, float> unaProyeccion, pair<float, float> otraProyeccion){

    if(unaProyeccion.second >= otraProyeccion.first){
        return false;
    }

    if(otraProyeccion.second >= unaProyeccion.first){
        return false;
    }

    return true;
}
