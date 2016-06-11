#include "escenarioVista.hpp"
using namespace std;

EscenarioVista::EscenarioVista(string infoEscenario, Ventana* ventana){
    this->anchoVentana = Decodificador::popInt(infoEscenario);
    this->altoVentana = Decodificador::popInt(infoEscenario);
    this->ventana = ventana;
    this->ancho = Decodificador::popInt(infoEscenario);
    this->alto = Decodificador::popInt(infoEscenario);
    this->pathImagen = Decodificador::popIdImg(infoEscenario);
    this->scrollingOffset = 0;
    this->contadorSonido = 0;
    this->fondo = new Figura();
    this->soundBoard = new SoundBoard();
    this->soundBoard->inicializar();
    this->inicializarComponentes(infoEscenario);
    this->figuraVidas = new Figura();

    puntajes.push_back(0);
    if (porEquipos) puntajes.push_back(0);

    textosPuntaje.push_back(new TextoDinamico(16, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana));
    textosPuntaje[0]->cambiarTexto("0");
    titulosPuntaje.push_back(new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana));
    titulosPuntaje[0]->cargarFuente("Puntaje - Equipo 1");
    if (porEquipos) {
        textosPuntaje.push_back(new TextoDinamico(16, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana));
        textosPuntaje[1]->cambiarTexto("0");
        titulosPuntaje.push_back(new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana));
        titulosPuntaje[1]->cargarFuente("Puntaje - Equipo 2");
    }
}

void EscenarioVista::inicializarComponentes(string infoEscenario) {
    int cantAviones = Decodificador::popInt(infoEscenario);
    for(int i = 0; i < cantAviones; i++) {
        string avion = Decodificador::popAvionInicial(infoEscenario);
        this->agregarAvionVista(avion);
    }
    cout << "Inicializo los aviones, ahora inicializa las etapas" << endl;
    int cantEtapas = Decodificador::popInt(infoEscenario);
    for (int i = 0; i < cantEtapas; ++i) {
        int cantElementos = Decodificador::popInt(infoEscenario);
        EtapaVista * etapaVista = new EtapaVista();

        for(int j = 0; j < cantElementos; ++j) {
            string elemento = Decodificador::popElementoInicial(infoEscenario);
            etapaVista->agregarElementoVista(elemento);
        }
        etapas.push_back(etapaVista);
    }
    itEtapa = etapas.begin();
    string disparo = Decodificador::popDisparoInicial(infoEscenario);
    this->agregarDisparoVista(disparo);
    this->agregarDisparoEnemigoVista();
    cout << "agrego los disparos" << endl;
    this->agregarVistasEnemigos();
    cout << "agrego los enemigos" << endl;
    this->agregarVistasPowerUps();
    cout << "agrego los powerups" << endl;
    this->porEquipos = (bool)Decodificador::popInt(infoEscenario);
    this->nroAvion = Decodificador::popInt(infoEscenario);

    if (infoEscenario.length() != 0) {
        cout << "Advertencia: el mensaje de inicialización del escenario todavía tiene bytes sin usar." << endl;
    }

    cout << "El número del avión es " << nroAvion << endl;
}

int EscenarioVista::comenzarEtapa() {
    this->activar();
    this->scrollingOffset = 0;
    this->elementos = etapaActual()->getElementos();
    cout << "se comienza una etapa con " << elementos.size() << " elementos." << endl;
    return this->mainLoop();
}

void EscenarioVista::avanzarEtapa() {
    desactivar();
    ++itEtapa;
}

EtapaVista* EscenarioVista::etapaActual() {
    return *itEtapa;
}

bool EscenarioVista::quedanEtapas() {
    return itEtapa != etapas.end();
}

void EscenarioVista::finalizarJuego() {
    avanzarEtapa();
    // TODO hay que liberar algo acá? O es mejor afuera?
}

void EscenarioVista::manejarEvento(int evento) {
    switch (evento) {
        case AVANZAR_ETAPA:
            avanzarEtapa();
            Logger::instance()->logInfo("Se avanza de etapa.");
            break;
        case FINALIZAR_JUEGO:
            finalizarJuego();
            Logger::instance()->logInfo("El juego ha finalizado.");
            cout << "El juego ha finalizado." << endl;
            break;
        default:
            Logger::instance()->logWarning("El evento que recibió el cliente no existe.");
            break;
    }
}

void EscenarioVista::actualizarComponentes(string infoActualizacion) {
    float offset = Decodificador::popFloat(infoActualizacion);
    this->actualizar(offset);
    list<AvionVista*>::iterator itAvion;
    for(itAvion = this->getAviones().begin(); itAvion != this->getAviones().end(); itAvion++){
        string avion = Decodificador::popAvion(infoActualizacion);
        int sonido = (*itAvion)->actualizar(avion);
        if (sonido == CODIGO_SONIDO_DISPARO){
            if (this->contadorSonido == 0){
                this->contadorSonido = CONTADOR_SONIDO_DISPARO_INICIAL;
                this->soundBoard->reproducirDisparo();
            }
        } else if (sonido == CODIGO_SONIDO_LOOP) {
            this->soundBoard->reproducirLoop();
        }
        if (this->contadorSonido > 0){
            this->contadorSonido = this->contadorSonido - 1;
        }
    }
    list<ElementoVista*>::iterator itElemento;
    for(itElemento = this->getElementos().begin(); itElemento != this->getElementos().end(); itElemento++){
        string elemento = Decodificador::popElemento(infoActualizacion);
        (*itElemento)->actualizar(elemento);
    }
    list<disparo> disparos;
    int cantDisparos = Decodificador::popInt(infoActualizacion);
    if (cantDisparos != 0) {
    }
    for (int i = 0; i < cantDisparos; ++i) {
        disparo unDisparo;
        unDisparo.posX = Decodificador::popFloat(infoActualizacion);
        unDisparo.posY = Decodificador::popFloat(infoActualizacion);
        unDisparo.estado = Decodificador::popInt(infoActualizacion);
        disparos.push_front(unDisparo);
    }
    this->setDisparos(disparos);

    int cantEnemigos = Decodificador::popInt(infoActualizacion);
    list<enemigo> enemigos;
    for (int i = 0; i < cantEnemigos; ++i) {
        enemigo unEnemigo;
        unEnemigo.posX = Decodificador::popFloat(infoActualizacion);
        unEnemigo.posY = Decodificador::popFloat(infoActualizacion);
        unEnemigo.estadoAnimacion = Decodificador::popInt(infoActualizacion);
        unEnemigo.tipoEnemigo = Decodificador::popInt(infoActualizacion);
        enemigos.push_front(unEnemigo);
    }
    this->setEnemigos(enemigos);

    list<disparoEnemigo> disparosEnemigos;
    int cantDisparosEnemigos = Decodificador::popInt(infoActualizacion);
    if (cantDisparosEnemigos != 0) {
    }
    for (int i = 0; i < cantDisparosEnemigos; ++i) {
        disparoEnemigo unDisparoEnemigo;
        unDisparoEnemigo.posX = Decodificador::popFloat(infoActualizacion);
        unDisparoEnemigo.posY = Decodificador::popFloat(infoActualizacion);
        disparosEnemigos.push_front(unDisparoEnemigo);
    }
    this->setDisparosEnemigos(disparosEnemigos);

    int cantidadPowerUps = Decodificador::popInt(infoActualizacion);
    list <powerUp> powerUps;
    for(int i = 0; i < cantidadPowerUps; ++i){
        powerUp unPowerUp;
        unPowerUp.posX = Decodificador::popFloat(infoActualizacion);
        unPowerUp.posY = Decodificador::popFloat(infoActualizacion);
        unPowerUp.estadoAnimacion = Decodificador::popInt(infoActualizacion);
        unPowerUp.tipoPowerUp = Decodificador::popInt(infoActualizacion);
        unPowerUp.valorPowerUp = Decodificador::popInt(infoActualizacion);
        powerUps.push_front(unPowerUp);
    }
    this->setPowerUps(powerUps);

    int puntajeAux = Decodificador::popInt(infoActualizacion);
    this->puntajes[0] = puntajeAux;
    if (porEquipos) {
        puntajeAux = Decodificador::popInt(infoActualizacion);
        this->puntajes[1] = puntajeAux;
    }

    if (infoActualizacion.size() != 0) {
        cout << "el mensaje queda con " <<  infoActualizacion.size() << " bytes luego de actualizar." << endl;
    }
}

EscenarioVista::~EscenarioVista(){}

// Carga todas las cosas. Anterior al loop.
void EscenarioVista::preloop(){
    // ventana->iniciar();
    cargarFondo();
    cargarVistasAviones();
    cargarVistasElementos();
    cargarVistasPowerUps();
    cargarVistaDisparos();
    cargarVistaEnemigos();
    cargarVistaDisparosEnemigos();
    cargarSonidos();
    cargarVistaVidas();
}

int EscenarioVista::mainLoop(){
    cout << "se entra al mainLoop" << endl;
    SDL_Event e;
    this->soundBoard->toggleMusica();
    while(this->getActivo()){
        while ( SDL_PollEvent( &e ) != 0 ) {
            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_CLOSE){
                    cout << "Evento de cierre" << endl;
                    this->desactivar();
                    return CERRAR;
                }
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_x) {
                    cout << "Se apretó x" << endl;
                    this->desactivar();
                    return CERRAR;
                }
            }
            this->pushEvento(e);
        }
        // TODO por ahí conviene agregar un mutex.
        this->renderizarFondo(this->scrollingOffset);
        this->renderizarFondo(this->scrollingOffset - this->fondo->getHeight());
        this->renderizarElementos();
        this->renderizarPowerUps();
        this->renderizarAviones();
        this->renderizarDisparos();
        this->renderizarDisparosEnemigos();
        this->renderizarEnemigos();
        // NOTE esta imágen se recarga si hubo cambios y debe estar en este thread.
        this->actualizarImagenPuntajes();
        this->renderizarPuntajes();
        this->renderizarImagenVidas();
        SDL_RenderPresent(this->getVentana()->getVentanaRenderer());
    }
    cout << "el getActivo es " << (getActivo()?" true":" false") << endl;
    cout << "Finalizó el ciclo de render." << endl;
    //cerrar();
    return CONTINUAR;
}

void EscenarioVista::pushEvento(SDL_Event evento){
    if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 )
    {
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP:
                this->colaEventos.push((int)ARRIBA_PRESIONA);
                break;
            case SDLK_DOWN:
                this->colaEventos.push((int)ABAJO_PRESIONA);
                break;
            case SDLK_LEFT:
                this->colaEventos.push((int)IZQUIERDA_PRESIONA);
                break;
            case SDLK_RIGHT:
                this->colaEventos.push((int)DERECHA_PRESIONA);
                break;
            case SDLK_SPACE:
                this->colaEventos.push((int)PRESIONA_ESPACIO);
                break;
            case SDLK_RETURN:
                this->colaEventos.push((int)PRESIONA_ENTER);
                break;
            case SDLK_r:
                this->colaEventos.push((int)PRESIONA_R);
                break;
            case SDLK_x:
                this->colaEventos.push((int)PRESIONA_X);
            case SDLK_m:
                this->soundBoard->toggleMusica();
                break;
        }
    } else if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ) {
        switch( evento.key.keysym.sym )
            {
                case SDLK_UP:
                    this->colaEventos.push((int)ARRIBA_SUELTA);
                    break;
                case SDLK_DOWN:
                    this->colaEventos.push((int)ABAJO_SUELTA);
                    break;
                case SDLK_LEFT:
                    this->colaEventos.push((int)IZQUIERDA_SUELTA);
                    break;
                case SDLK_RIGHT:
                    this->colaEventos.push((int)DERECHA_SUELTA);
                    break;
            }
    }
}

int EscenarioVista::popEvento() {
    if(!colaEventos.vacia()){
        return colaEventos.pop();
    } else{
        return EVENTO_VACIO;
    }
}

void EscenarioVista::activar() {
    this->activo = true;
}

void EscenarioVista::desactivar() {
    this->activo = false;
    colaEventos.avisar();
}

void EscenarioVista::cerrar() {
    this->fondo->free();

    for(list<AvionVista*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        AvionVista* avionVista = *iterador;
        avionVista->cerrar();
    }

    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        ElementoVista* elementoVista = *iterador;
        elementoVista->cerrar();
    }
    this->disparoVista->cerrar();
    // this->ventana->cerrar();
}

void EscenarioVista::setDisparos(list<disparo> disparosParam){
    pthread_mutex_lock(&this->mutexDisparos);
    this->disparos = disparosParam;
    pthread_mutex_unlock(&this->mutexDisparos);
}

void EscenarioVista::setDisparosEnemigos(list<disparoEnemigo> disparosEnemigosParam){
    pthread_mutex_lock(&this->mutexDisparosEnemigos);
    this->disparosEnemigos = disparosEnemigosParam;
    pthread_mutex_unlock(&this->mutexDisparosEnemigos);
}

void EscenarioVista::setEnemigos(list<enemigo> enemigosParam){
    pthread_mutex_lock(&this->mutexEnemigos);
    this->enemigos = enemigosParam;
    pthread_mutex_unlock(&this->mutexEnemigos);
}

void EscenarioVista::setPowerUps(list<powerUp> powerUpsParam){
    pthread_mutex_lock(&this->mutexPowerUps);
    this->powerUps = powerUpsParam;
    pthread_mutex_unlock(&this->mutexPowerUps);
}

void EscenarioVista::setScrollingOffset(float scrollingOffset){
    this->scrollingOffset = scrollingOffset;
}

/* Inicializacion de elementos internos del escenario */

void EscenarioVista::agregarAvionVista(string infoAvion){
    AvionVista* avionVista = new AvionVista(infoAvion);
    this->aviones.push_back(avionVista);
}

void EscenarioVista::agregarDisparoVista(string pathSprite){
    this->disparoVista = new DisparoVista(pathSprite);
}

void EscenarioVista::agregarDisparoEnemigoVista(){
    this->disparoEnemigoVista = new DisparoEnemigoVista();
}

void EscenarioVista::agregarVistasEnemigos(){
    this->enemigoPequenio = new EnemigoPequenio();
    this->enemigoDeEscuadron = new EnemigoDeEscuadron();
    this->enemigoMediano = new EnemigoMediano();
    this->enemigoGrande = new EnemigoGrande();
}

void EscenarioVista::agregarVistasPowerUps(){
  this->powerUpBonificacion = new PowerUpBonificacionVista();
  this->powerUpDosAmetralladoras = new PowerUpDosAmetralladorasVista();
  this->powerUpDestruirEnemigos = new PowerUpDestruirEnemigosVista();
  this->powerUpAvionesSecundarios = new PowerUpAvionesSecundariosVista();
}

void EscenarioVista::cargarVistasAviones(){
    int numeroJugador = 1;
    for(list<AvionVista*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        AvionVista* avionVista = *iterador;
        this->cargarAvion(avionVista, ventana->getVentanaRenderer(), numeroJugador);
        numeroJugador++;
    }
}


void EscenarioVista::cargarVistasElementos(){
    // Cargo imágenes de todas las etapas.
    list<EtapaVista*>::iterator i;
    for (i = etapas.begin(); i != etapas.end(); ++i) {
        EtapaVista * etapa = *i;
        list<ElementoVista*>::iterator j;
        list<ElementoVista*> elementos = etapa->getElementos();
        for (j = elementos.begin(); j != elementos.end(); ++j){
            this->cargarElemento(*j, ventana->getVentanaRenderer());
        }
    }
}

void EscenarioVista::cargarVistaDisparos() {
    this->disparoVista->cargarImagen(this->ventana->getVentanaRenderer());
}

void EscenarioVista::cargarVistaDisparosEnemigos() {
    this->disparoEnemigoVista->cargarImagen(this->ventana->getVentanaRenderer());
}

void EscenarioVista::cargarVistaEnemigos() {
    this->enemigoPequenio->cargarImagen(this->ventana->getVentanaRenderer());
    this->enemigoDeEscuadron->cargarImagen(this->ventana->getVentanaRenderer());
    this->enemigoMediano->cargarImagen(this->ventana->getVentanaRenderer());
    this->enemigoGrande->cargarImagen(this->ventana->getVentanaRenderer());

}

void EscenarioVista::cargarFondo(){
    if(!this->fondo->loadFromFile(this->pathImagen, this->ventana->getVentanaRenderer())){
        this->fondo->loadFromFile(FONDO_POR_DEFECTO, this->ventana->getVentanaRenderer());
    }
}

void EscenarioVista::cargarVistasPowerUps() {
    this->powerUpBonificacion->cargarImagen(this->ventana->getVentanaRenderer());
    this->powerUpDestruirEnemigos->cargarImagen(this->ventana->getVentanaRenderer());
    this->powerUpDosAmetralladoras->cargarImagen(this->ventana->getVentanaRenderer());
    this->powerUpAvionesSecundarios->cargarImagen(this->ventana->getVentanaRenderer());
}

void EscenarioVista::cargarAvion(AvionVista* avionVista, SDL_Renderer* renderer, int numeroJugador){
    avionVista->cargarImagen(renderer, numeroJugador);
}

void EscenarioVista::cargarElemento(ElementoVista* elementoVista, SDL_Renderer* renderer){
    elementoVista->cargarImagen(renderer);
}

void EscenarioVista::cargarSonidos() {
    this->soundBoard->cargarSonidos();
}

void EscenarioVista::cargarVistaVidas(){
    this->figuraVidas->loadFromFile(VIDAS, this->ventana->getVentanaRenderer());
}

/* Renderizaciones */

void EscenarioVista::renderizarImagenVidas(){
    list<AvionVista*>::iterator it = aviones.begin();
    advance (it, this->nroAvion - 1);
    AvionVista *avionVida = *it;
    int vidas =  (avionVida)->getVidas();
    for(int i = 0; i < vidas; i++){
        this->figuraVidas->render(330 + (i*ANCHO_VIDA), 10, this->ventana->getVentanaRenderer());
    }
}

void EscenarioVista::renderizarElementos(){
    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        ElementoVista* elementoVista = *iterador;
        elementoVista->render(this->ventana->getVentanaRenderer());
    }
}

void EscenarioVista::actualizarImagenPuntajes() {
    stringstream ss; ss << puntajes[0];
    textosPuntaje[0]->cambiarTexto(ss.str());
    if (porEquipos) {
        stringstream ss2; ss2 << puntajes[1];
        textosPuntaje[1]->cambiarTexto(ss2.str());
    }
}

void EscenarioVista::renderizarPuntajes() {
    titulosPuntaje[0]->renderizar(POSX_PUNTAJE1, POSY_PUNTAJES);
    textosPuntaje[0]->renderizar(POSX_PUNTAJE1, POSY_PUNTAJES + 20);
    if (porEquipos) {
        titulosPuntaje[1]->renderDerecho(ventana->getAncho() - 10, POSY_PUNTAJES);
        textosPuntaje[1]->renderDerecho(ventana->getAncho() - 10, POSY_PUNTAJES + 20);
    }
}

void EscenarioVista::renderizarAviones() {
    list<AvionVista*>::iterator iterador;
    AvionVista* avionDelCliente;

    int i = 0;
    for(iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador) {
        ++i;
        // Primero dibujamos los aviones que no le correspondan a este cliente.
        if (i != nroAvion) {
            AvionVista* avion = *iterador;
            avion->render(this->ventana->getVentanaRenderer());
        } else {
            avionDelCliente = *iterador;
        }
    }
    // Último hay que dibujar el del nroAvion, para que esté arriba.
    avionDelCliente->render(this->ventana->getVentanaRenderer());
}

void EscenarioVista::renderizarFondo(float y) {
    pthread_mutex_lock(&mutexActualizar);
    this->fondo->render(0,(int)y,this->ventana->getVentanaRenderer(), NULL);
    pthread_mutex_unlock(&mutexActualizar);
}

void EscenarioVista::renderizarDisparos(){
    pthread_mutex_lock(&mutexDisparos);
    for(list<disparo>::iterator iterador = this->disparos.begin(); iterador != this->disparos.end(); ++iterador) {
        disparo disparo1 = *iterador;
        disparoVista->render(disparo1.posX, disparo1.posY, disparo1.estado, this->ventana->getVentanaRenderer());
    }
    pthread_mutex_unlock(&mutexDisparos);
}

void EscenarioVista::renderizarDisparosEnemigos(){
    pthread_mutex_lock(&mutexDisparosEnemigos);
    for(list<disparoEnemigo>::iterator iterador = this->disparosEnemigos.begin(); iterador != this->disparosEnemigos.end(); ++iterador) {
        disparoEnemigo disparo1 = *iterador;
        disparoEnemigoVista->render(disparo1.posX, disparo1.posY, this->ventana->getVentanaRenderer());
    }
    pthread_mutex_unlock(&mutexDisparosEnemigos);
}

void EscenarioVista::renderizarEnemigos(){
    pthread_mutex_lock(&mutexEnemigos);
    for(list<enemigo>::iterator iterador = this->enemigos.begin(); iterador != this->enemigos.end(); ++iterador) {
        enemigo enemigo1 = *iterador;

        if (enemigo1.tipoEnemigo == TIPO_AVION_PEQUENIO)
            this->enemigoPequenio->render(enemigo1.posX, enemigo1.posY, enemigo1.estadoAnimacion, this->ventana->getVentanaRenderer());
        else if (enemigo1.tipoEnemigo == TIPO_AVION_ESCUADRON)
            this->enemigoDeEscuadron->render(enemigo1.posX, enemigo1.posY, enemigo1.estadoAnimacion, this->ventana->getVentanaRenderer());
        else if (enemigo1.tipoEnemigo == TIPO_AVION_MEDIANO)
            this->enemigoMediano->render(enemigo1.posX, enemigo1.posY, enemigo1.estadoAnimacion, this->ventana->getVentanaRenderer());
        else
            this->enemigoGrande->render(enemigo1.posX, enemigo1.posY, enemigo1.estadoAnimacion, this->ventana->getVentanaRenderer());
    }
    pthread_mutex_unlock(&mutexEnemigos);
}

void EscenarioVista::renderizarPowerUps(){
  pthread_mutex_lock(&mutexPowerUps);
  for(list<powerUp>::iterator iterador = this->powerUps.begin(); iterador != this->powerUps.end(); iterador++){
    powerUp unPowerUp = *iterador;

    if (unPowerUp.tipoPowerUp == TIPO_POWERUP_BONIFICACION){
        this->powerUpBonificacion->render(unPowerUp.posX,unPowerUp.posY,unPowerUp.estadoAnimacion,this->ventana->getVentanaRenderer());
    } else if (unPowerUp.tipoPowerUp == TIPO_POWERUP_DOS_AMETRALLADORAS){
        this->powerUpDosAmetralladoras->render(unPowerUp.posX,unPowerUp.posY,unPowerUp.estadoAnimacion,this->ventana->getVentanaRenderer());
    } else if (unPowerUp.tipoPowerUp == TIPO_POWERUP_DESTRUIR_ENEMIGOS){
        this->powerUpDestruirEnemigos->render(unPowerUp.posX,unPowerUp.posY,unPowerUp.estadoAnimacion,this->ventana->getVentanaRenderer());
    } else {
        this->powerUpAvionesSecundarios->render(unPowerUp.posX,unPowerUp.posY,unPowerUp.estadoAnimacion,this->ventana->getVentanaRenderer());
    }
  }
  pthread_mutex_unlock(&mutexPowerUps);
}

void EscenarioVista::actualizar(float offset) {
    pthread_mutex_lock(&this->mutexActualizar);
    this->scrollingOffset = offset;
    pthread_mutex_unlock(&this->mutexActualizar);

}

/* Getters */

int EscenarioVista::getAncho(){
    return this->ancho;
}

int EscenarioVista::getAlto(){
    return this->alto;
}

list<AvionVista*>& EscenarioVista::getAviones(){
    return this->aviones;
}

list<ElementoVista*>& EscenarioVista::getElementos(){
    return this->elementos;
}

Figura* EscenarioVista::getFondo(){
    return this->fondo;
}

Ventana* EscenarioVista::getVentana(){
    return this->ventana;
}

float EscenarioVista::getScrollingOffset(){
    return this->scrollingOffset;
}

bool EscenarioVista::getActivo(){
  return this->activo;
}
