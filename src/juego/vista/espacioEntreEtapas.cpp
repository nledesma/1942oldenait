#include "espacioEntreEtapas.hpp"


EspacioEntreEtapas::EspacioEntreEtapas(Ventana * ventana, string mensaje, int nroEtapa) {
    this->ventana = ventana;
    this->fondo = new Figura();
    this->nroEtapa = nroEtapa;
    // TODO path constante.
    this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas");
    this->porEquipos = (bool) Decodificador::popInt(mensaje);
    this->etapaFinal = (bool) Decodificador::popInt(mensaje);

    if (this->nroEtapa != -1) {
        imprimirTituloEtapa();
        decodificarPuntos(mensaje);
    } else {
        imprimirTituloReiniciar();
    }
    dibujar = true;
}

EspacioEntreEtapas::~EspacioEntreEtapas() {

}

void EspacioEntreEtapas::imprimirTituloEtapa(){
    Texto * textoAux = new Texto(30, AMARILLO_STAR_WARS, STAR_WARS_FONT2, ventana);
    stringstream ss;
    ss << "etapa " << nroEtapa << " terminada";
    textoAux->cargarFuente(ss.str());
    textos.push_back(textoAux);

    if (this->etapaFinal){
        Texto * textoAux2 = new Texto(30, AMARILLO_STAR_WARS, STAR_WARS_FONT2, ventana);
        stringstream ss2;
        ss2 << "partida terminada!";
        textoAux->cargarFuente(ss2.str());
        textos.push_back(textoAux2);
    }
}

void EspacioEntreEtapas::imprimirTituloReiniciar(){
    Texto * textoAux = new Texto(30, AMARILLO_STAR_WARS, STAR_WARS_FONT2, ventana);
    stringstream ss;
    ss << "reiniciando partida";
    textoAux->cargarFuente(ss.str());
    textos.push_back(textoAux);
}

void EspacioEntreEtapas::decodificarPuntos(string mensaje) {
    // Cada jugador viene como un par, equipo, puntos.
    // Vienen en orden (no hace falta pasar el número).
    // TODO chequear que sea múltiplo de 2*sizeof(int) el length.
    int equipo = 0;
    int puntos;
    int disparos;
    int aciertos;
    int porcentaje;
    int cantJugadores;
    string nombre;
    vector<puntajeJugador> equipo1;
    vector<puntajeJugador> equipo2;
    while(mensaje.length() != 0) {

        equipo = Decodificador::popInt(mensaje);
        puntajeJugador puntajeActual;
        puntajeActual.puntaje = Decodificador::popInt(mensaje);
        puntajeActual.disparos = Decodificador::popInt(mensaje);
        puntajeActual.aciertos = Decodificador::popInt(mensaje);
        puntajeActual.porcentaje = Decodificador::popInt(mensaje);
        puntajeActual.vidas = Decodificador::popInt(mensaje);
        puntajeActual.nombre = Decodificador::popString(mensaje);

        if (equipo == 0)
            equipo1.push_back(puntajeActual);
        else
            equipo2.push_back(puntajeActual);


    }

    if (this->porEquipos) {
        Texto *textoAux0 = new Texto(20, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
        stringstream ss0;
        ss0 << "equipo 1:";
        textoAux0->cargarFuente(ss0.str());
        textos.push_back(textoAux0);
    }

    int vidasEquipo1 = 0;
    int puntajeEquipo1 = 0;
    for (int i = 0; i < (int)equipo1.size(); i++) {
        vidasEquipo1 += equipo1[i].vidas;
        puntajeEquipo1 += equipo1[i].puntaje;

        Texto *textoAux = new Texto(15, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
        stringstream ss;
        ss << equipo1[i].nombre << " - puntaje: " << equipo1[i].puntaje;
        ss << "  disparos: " << equipo1[i].disparos;
        ss << "  aciertos: " << equipo1[i].aciertos;
        ss << "  punteria: " << equipo1[i].porcentaje;
        ss << "  vidas: " << equipo1[i].vidas;
        textoAux->cargarFuente(ss.str());
        textos.push_back(textoAux);
    }
    Texto *textoPuntajeEquipo1 = new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_SYMBOL, ventana);
    stringstream ssPuntajeEquipo1;
    ssPuntajeEquipo1 << "puntaje total: " << puntajeEquipo1;
    textoPuntajeEquipo1->cargarFuente(ssPuntajeEquipo1.str());
    textos.push_back(textoPuntajeEquipo1);

    Texto *textoSeparador1 = new Texto(14, AMARILLO_STAR_WARS, STAR_WARS_SYMBOL, ventana);
    textoSeparador1->cargarFuente("$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $");
    textos.push_back(textoSeparador1);

    if (equipo2.size() > 0){

        Texto *textoAux2 = new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
        stringstream ss2;
        ss2 << "equipo 2:";
        textoAux2->cargarFuente(ss2.str());
        textos.push_back(textoAux2);

        int vidasEquipo2 = 0;
        int puntajeEquipo2 = 0;
        for (int i = 0; i < (int)equipo2.size(); i++) {
            vidasEquipo2 += equipo2[i].vidas;
            puntajeEquipo2 += equipo2[i].puntaje;

            Texto *textoAux3 = new Texto(15, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
            stringstream ss3;
            ss3 << equipo2[i].nombre << " - puntaje: " << equipo2[i].puntaje;
            ss3 << "  disparos: " << equipo2[i].disparos;
            ss3 << "  aciertos: " << equipo2[i].aciertos;
            ss3 << "  punteria: " << equipo2[i].porcentaje;
            ss3 << "  vidas: " << equipo2[i].vidas;
            textoAux3->cargarFuente(ss3.str());
            textos.push_back(textoAux3);
        }

        Texto *textoPuntajeEquipo2 = new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_SYMBOL, ventana);
        stringstream ssPuntajeEquipo2;
        ssPuntajeEquipo2 << "puntaje total: " << puntajeEquipo2;
        textoPuntajeEquipo2->cargarFuente(ssPuntajeEquipo2.str());
        textos.push_back(textoPuntajeEquipo2);

        Texto *textoSeparador2 = new Texto(14, AMARILLO_STAR_WARS, STAR_WARS_SYMBOL, ventana);
        textoSeparador2->cargarFuente("$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $");
        textos.push_back(textoSeparador2);

        if (this->etapaFinal){
            Texto *textoGanador = new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_SYMBOL, ventana);
            stringstream ssGanador;
            if (vidasEquipo1 == 0){
                ssGanador << "equipo 2 ganador!";
            } else if (vidasEquipo2 == 0){
                ssGanador << "equipo 1 ganador!";
            } else if (puntajeEquipo1 > puntajeEquipo2){
                ssGanador << "equipo 1 ganador!";
            } else if (puntajeEquipo2 > puntajeEquipo1){
                ssGanador << "equipo 2 ganador!";
            } else {
                ssGanador << "empate entre los dos equipos!";
            }
            textoGanador->cargarFuente(ssGanador.str());
            textos.push_back(textoGanador);
        }
    }
}

int EspacioEntreEtapas::renderLoop() {
    SDL_Event e;

    while(dibujar) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_CLOSE){
                    cout << "Evento de cierre" << endl;
                    this->finalizar();
                    return CERRAR;
                }
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_x) {
                    cout << "Se apretó x" << endl;
                    this->finalizar();
                    return CERRAR;
                }
            }
        }
        fondo->render(0, 0, ventana->getVentanaRenderer());
        renderTextos();
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
    cout << "FIN RENDER LOOP";
    return CONTINUAR;
}

void EspacioEntreEtapas::renderTextos() {
    list<Texto*>::iterator it;
    int y = 20;
    for (it = textos.begin(); it != textos.end(); ++it) {
        (*it)->renderCentrado(y);
        y += 30;
    }
}

void EspacioEntreEtapas::finalizar() {
    dibujar = false;
}
