#include "decodificador.hpp"
#include <iostream>

/* Push y pop de Strings de ids de sprites e imágenes */

void Decodificador::push(string &codigo, string idImg) {
    push(codigo, (int) idImg.length());
    codigo += idImg;
}

string Decodificador::popString(string &codigo) {
    string lengthString = popBytes(codigo, sizeof(int));
    int length = stringToInt(lengthString);
    return popBytes(codigo, length);
}

/* Push y pop de Elementos del mapa. */
void Decodificador::push(string & codigo, Elemento *e) {
    push(codigo, e->getPosX());
    push(codigo, e->getPosY());
}

string Decodificador::popElemento(string & codigo) {
    return popBytes(codigo, 2 * sizeof(float));
}

/* Push y pop de Aviones. */
void Decodificador::push(string & codigo, Avion* a) {
    push(codigo, a->getPosicionX());
    push(codigo, a->getPosicionY());
    push(codigo, (int) a->getEstadoPowerUp());
    push(codigo, (int) a->getEstadoAnimacion());
    push(codigo, (int)a->getVidas());
}

void Decodificador::push(string & codigo, AvionSecundario* a){
    push(codigo, a->getPosicionX());
    push(codigo, a->getPosicionY());
    push(codigo, (int) a->getEstadoAnimacion());
}

string Decodificador::popAvionSecundario(string & codigo){
  return popBytes(codigo, 2*sizeof(float) + sizeof(int));
}

string Decodificador::popAvion(string & codigo){
    return popBytes(codigo, 2*sizeof(float) + 3*sizeof(int));
}

/* Push y pop de powerUps */
void Decodificador::push(string &codigo, PowerUp *powerUp){
  push(codigo, powerUp->getPosicionX());
  push(codigo, powerUp->getPosicionY());
  push(codigo, powerUp->getEstadoAnimacion());
  push(codigo, powerUp->getTipoPowerUp());
  push(codigo, powerUp->getValor());
}

/* Push y pop de disparo. */
void Decodificador::push(string & codigo, Disparo *d) {
    push(codigo, d->getPosX());
    // cout << "EN EL PUSH LA POS X ES : " << d->getPosX() << endl;
    push(codigo, d->getPosY());
    // cout << "EN EL PUSH LA POS Y ES : " << d->getPosY() << endl;
    push(codigo, d->getEstado());
}

void Decodificador::push(string & codigo, DisparoAvionSecundario *d) {
    push(codigo, d->getPosX());
    // cout << "EN EL PUSH LA POS X ES : " << d->getPosX() << endl;
    push(codigo, d->getPosY());
    // cout << "EN EL PUSH LA POS Y ES : " << d->getPosY() << endl;
    push(codigo, d->getEstado());
}

/* Push y pop de disparo enemigo. */
void Decodificador::push(string & codigo, DisparoEnemigo *d) {
    push(codigo, d->getPosX());
    push(codigo, d->getPosY());
}

string Decodificador::popDisparo(string & codigo) {
    return popBytes(codigo, 2*sizeof(float) + sizeof(int));
}

/* Push enemigo */

void Decodificador::push(string & codigo, AvionEnemigo *enemigo){
    push(codigo, enemigo->getPosicionX());
    push(codigo, enemigo->getPosicionY());
    push(codigo, enemigo->getEstadoAnimacion());
    push(codigo, enemigo->getTipoAvion());
}

/* Push y Pop del Escenario. */
void Decodificador::push(string & codigo, EscenarioJuego *e) {
    push(codigo, e->getScrollingOffset());
}

string Decodificador::popEscenario(string &codigo){
    return popBytes(codigo, sizeof(float));
}

/*Push y Pop de Eventos*/
void Decodificador::pushEvento(string & codigo, int evento){
	push(codigo, evento);
}

string Decodificador::popEvento(string & codigo){
    return popBytes(codigo, sizeof(int));
}

string Decodificador::popCantidad(string & codigo){
    return popBytes(codigo, sizeof(int));
}

/* Push y pop de bool (1 byte)*/
void Decodificador::push(string & codigo, bool b) {
    if (b)
        push(codigo, 't');
    else
        push(codigo, 'f');
    imprimirBytes(codigo);
}

bool Decodificador::popBool(string & codigo) {
    char b = popBytes(codigo, 1)[0];
    if (b == 't') {
        return true;
    } else if (b == 'f') {
        return false;
    }
    // TODO excepcion
    cout << "El popBool recibe un código no válido: " << b << "("<< (int) b <<")" << endl;
    cout << "Quedaban en el mensaje recibido los siguientes bytes" << endl;
    imprimirBytes(codigo);
    return false;
}

/* Generales para cualquier tipo */
template<typename T> void Decodificador::push(string & str, T e) {
    int n = sizeof(e);
    char * bytes = new char[n];
    memcpy((void*)bytes, (void*) &e, n);

    for (int i = 0; i < n; i++) {
        str += bytes[i];
    }

    delete bytes;
}

string Decodificador::popBytes(string & codigo, int cBytes) {
    string ret = codigo.substr(0, cBytes);
    codigo.erase(0, cBytes);
    return ret;
}

void Decodificador::imprimirBytes(string codigo) {
    for (unsigned int i = 0; i < codigo.length(); ++i) {
        cout << (int) codigo[i] << " ";
    }
    cout << endl;
}

int Decodificador::stringToInt(string codigo){
    int valorConvertido;
    memcpy((void*)&valorConvertido, (void*)&codigo[0], sizeof(int));
    return valorConvertido;
}

float Decodificador::stringToFloat(string codigo){
    float valorConvertido;
    memcpy((void*)&valorConvertido, (void*)&codigo[0], sizeof(float));
    return valorConvertido;
}

void Decodificador::pushInicial(string &codigo, Avion *a) {
    push(codigo, a->getPosicionX());
    push(codigo, a->getPosicionY());
    push(codigo, a->getIdSprite());
}

void Decodificador::pushInicial(string &codigo, Elemento *e) {
    push(codigo, e->getPosX());
    push(codigo, e->getPosY());
    push(codigo, e->getIdSprite());
}

void Decodificador::pushInicial(string &codigo, EscenarioJuego *e) {
    push(codigo, e->getAnchoVentana());
    push(codigo, e->getAltoVentana());
    push(codigo, e->getAncho());
    push(codigo, e->getAlto());
    push(codigo, e->getIdSprite());
}

void Decodificador::pushInicialDisparo(string &codigo, string idSpriteDisparo) {
    push(codigo, idSpriteDisparo);
}

void Decodificador::pushCantidad(string &codigo, int cantidad) {
    push(codigo, cantidad);
}

string Decodificador::popAvionInicial(string & codigo){
    string str1 = popBytes(codigo, sizeof(float));
    string str2 = popBytes(codigo, sizeof(float));
    string str3 = popString(codigo);
    return str1 + str2 + str3;
}

string Decodificador::popElementoInicial(string & codigo){
    string str1 = popBytes(codigo, 2*sizeof(float));
    string str2 = popString(codigo);
    return str1 + str2;
}

string Decodificador::popEscenarioInicial(string & codigo){
    string str1 = popBytes(codigo, 2*sizeof(int));
    string str2 = popString(codigo);
    return str1 + str2;
}

string Decodificador::popDisparoInicial(string &codigo) {
    return popString(codigo);
}

string Decodificador::getCodigoEstadoInicial(EscenarioJuego * escenarioJuego) {
    string codigo;
    Decodificador::pushInicial(codigo, escenarioJuego);
    list<Avion*> aviones = escenarioJuego->getAviones();
    Decodificador::pushCantidad(codigo, (int) aviones.size());
    for(list<Avion*>::iterator iterador = aviones.begin(); iterador != aviones.end(); ++iterador){
        Avion* avion = *iterador;
        Decodificador::pushInicial(codigo, avion);
    }
    // TODO por ahí no conviene copia sino referencia, por velocidad. Igual es una vez.
    list<Etapa *> etapas = escenarioJuego->getEtapas();
    list<Etapa *>::iterator itEtapa;
    Decodificador::pushCantidad(codigo, etapas.size());
    for (itEtapa = etapas.begin(); itEtapa != etapas.end(); ++itEtapa) {
        list<Elemento*> elementos = (*itEtapa)->getElementos();
        Decodificador::pushCantidad(codigo, elementos.size());
        list<Elemento *>::iterator itElemento;
        for(itElemento = elementos.begin(); itElemento != elementos.end(); ++itElemento) {
            Elemento* elemento = *itElemento;
            Decodificador::pushInicial(codigo, elemento);
        }
    }
    Decodificador::pushInicialDisparo(codigo, aviones.front()->getIdSpriteDisparos());
    Decodificador::pushCantidad(codigo, escenarioJuego->porEquipos());
    Decodificador::push(codigo, escenarioJuego->getNroEtapa());
    // TODO poner esto en el cliente.
    return codigo;
}

string Decodificador::getCodigoEstadoActual(EscenarioJuego *escenarioJuego) {
    string codigo;
    Decodificador::push(codigo, escenarioJuego);
    list<Avion*> aviones = escenarioJuego->getAviones();
    for(list<Avion*>::iterator iterador = aviones.begin(); iterador != aviones.end(); ++iterador) {
        Avion* avion = *iterador;
        Decodificador::push(codigo, avion);
        //if(avion->getAvionesSecundarios().size() > 0){
            //cout << "Cantidad de aviones secundarios en decodificador: " << (int)avion->getAvionesSecundarios().size() << endl;
            //Decodificador::pushCantidad(codigo, (int)avion->getAvionesSecundarios().size());
            //for(list<AvionSecundario*>::iterator iteradorAvionesSecundarios = avion->getAvionesSecundarios().begin(); iteradorAvionesSecundarios != avion->getAvionesSecundarios().end(); ++iteradorAvionesSecundarios){
            //    AvionSecundario* avionSecundario = *iteradorAvionesSecundarios;
            //    Decodificador::push(codigo,avionSecundario);
            //}
        //}
    }
    list<Elemento*> elementos = escenarioJuego->getElementos();
    for(list<Elemento*>::iterator iterador = elementos.begin(); iterador != elementos.end(); ++iterador) {
        Elemento* elemento = *iterador;
        Decodificador::push(codigo, elemento);
    }
    list<Disparo*> disparos = escenarioJuego->getDisparos();
    Decodificador::pushCantidad(codigo, (int) disparos.size());
    if(!disparos.empty()){
        for(list<Disparo*>::iterator iterador = disparos.begin(); iterador != disparos.end(); ++iterador) {
            Disparo* disparo = *iterador;
            // cout << "EN EL DECO LA POS X DEL DISPARO ES: " << disparo->getPosX() << endl;
            // cout << "EN EL DECO LA POS Y DEL DISPARO ES: " << disparo->getPosY() << endl;
            Decodificador::push(codigo, disparo);
        }
    }

    //TODO a partir de aca agregue
    list <DisparoAvionSecundario*> disparosAvionesSecundarios = escenarioJuego->getDisparosAvionesSecundarios();
    // cout « "EN EL DECO EL TAMAÑO DE LA LISTA DE AVIONES SECUNDARIOS DE AVION ES: " « avionesSecundarios.size()« endl;
    Decodificador::pushCantidad(codigo, (int) disparosAvionesSecundarios.size());
    if(!disparosAvionesSecundarios.empty()){
        for(list<DisparoAvionSecundario*>::iterator iterador = disparosAvionesSecundarios.begin(); iterador != disparosAvionesSecundarios.end(); ++iterador){
            DisparoAvionSecundario* disparoAvionSecundario = *iterador;
            // cout << "EN EL DECO LA POS X DEL DISPARO ES: " << disparoAvionSecundario->getPosX() << endl;
            // cout << "EN EL DECO LA POS Y DEL DISPARO ES: " << disparoAvionSecundario->getPosY() << endl;
            Decodificador::push(codigo, disparoAvionSecundario);
        }
    }
    //TODO hasta aca agregue
    list<AvionEnemigo*> enemigos = escenarioJuego->getEnemigos();
    Decodificador::pushCantidad(codigo, (int) enemigos.size());
    if(!enemigos.empty()){
        for(list<AvionEnemigo*>::iterator iterador = enemigos.begin(); iterador != enemigos.end(); ++iterador) {
            AvionEnemigo* enemigo = *iterador;
            Decodificador::push(codigo, enemigo);
        }
    }

    list<DisparoEnemigo*> disparosEnemigos = escenarioJuego->getDisparosEnemigos();
    Decodificador::pushCantidad(codigo, (int) disparosEnemigos.size());
    if(!disparosEnemigos.empty()){
        for(list<DisparoEnemigo*>::iterator iterador = disparosEnemigos.begin(); iterador != disparosEnemigos.end(); ++iterador) {
            DisparoEnemigo* disparoEnemigo = *iterador;
            Decodificador::push(codigo, disparoEnemigo);
        }
    }

    list<PowerUp*> powerUps = escenarioJuego->getPowerUps();
    Decodificador::pushCantidad(codigo, (int) powerUps.size());
    if(!powerUps.empty()){
        for(list<PowerUp*>::iterator iterador = powerUps.begin(); iterador != powerUps.end(); ++iterador) {
            PowerUp* powerUp = *iterador;
            Decodificador::push(codigo, powerUp);
        }
    }

    for(list<Avion*>::iterator iterador = aviones.begin(); iterador != aviones.end(); ++iterador) {
        Avion* avion = *iterador;
        list <AvionSecundario*> avionesSecundarios = avion->getAvionesSecundarios();
        // cout « "EN EL DECO EL TAMAÑO DE LA LISTA DE AVIONES SECUNDARIOS DE AVION ES: " « avionesSecundarios.size()« endl;
        Decodificador::pushCantidad(codigo, (int) avionesSecundarios.size());
        if(!avionesSecundarios.empty()){
            for(list<AvionSecundario*>::iterator iterador = avionesSecundarios.begin(); iterador != avionesSecundarios.end(); ++iterador){
                AvionSecundario* avionSecundario = *iterador;
                Decodificador::push(codigo, avionSecundario);
            }
        }
    }

    Decodificador::pushCantidad(codigo, escenarioJuego->getPuntaje(0));
    // Si es por equipos encolamos el puntaje del segundo.
    if (escenarioJuego->porEquipos())
        Decodificador::pushCantidad(codigo, escenarioJuego->getPuntaje(1));

    return codigo;
}

string Decodificador::getPuntajes(EscenarioJuego * escenario, map<int, string> nombreSegunNroAvion) {
    string mensaje;
    list<pair <int,vector<int> > > listaPuntajes = escenario->getPuntajes();
    list<pair<int,vector<int>>>::iterator it;
    for (it = listaPuntajes.begin(); it != listaPuntajes.end(); ++it) {
        int nroAvion = it->first;
        Decodificador::pushCantidad(mensaje, nroAvion);
        cout << "nroAvion: " << nroAvion << endl;
        vector<int> datosAvion = it->second;
        int equipo = datosAvion[0];
        Decodificador::pushCantidad(mensaje, equipo);
        cout << "equipo: " << equipo << endl;
        int puntaje = datosAvion[1];
        Decodificador::pushCantidad(mensaje, puntaje);
        cout << "puntaje: " << puntaje << endl;
        int disparos = datosAvion[2];
        Decodificador::pushCantidad(mensaje, disparos);
        cout << "disparos: " << disparos << endl;
        int aciertos = datosAvion[3];
        Decodificador::pushCantidad(mensaje, aciertos);
        cout << "aciertos: " << aciertos << endl;
        int porcentaje = datosAvion[4];
        Decodificador::pushCantidad(mensaje, porcentaje);
        cout << "porcentaje: " << porcentaje << endl;
        Decodificador::push(mensaje, nombreSegunNroAvion[nroAvion]);
        cout << "nombre: " << nombreSegunNroAvion[nroAvion] << endl;
    }
    return mensaje;
}

float Decodificador::popFloat(string & codigo) {
    return stringToFloat(popBytes(codigo, sizeof(float)));
}

int Decodificador::popInt(string & codigo) {
    return stringToInt(popBytes(codigo, sizeof(int)));
}

int Decodificador::popByte(string & codigo) {
    return (int) popBytes(codigo, 1)[0];
}
