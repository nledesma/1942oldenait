#include "espacioEntreEtapas.hpp"


EspacioEntreEtapas::EspacioEntreEtapas(Ventana * ventana, string mensaje, int nroEtapa) {
    this->ventana = ventana;
    this->fondo = new Figura();
    this->nroEtapa = nroEtapa;
    // TODO path constante.
    this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas");
    porEquipos = (bool) Decodificador::popInt(mensaje);
    imprimirTituloEtapa();
    decodificarPuntos(mensaje);
    dibujar = true;
}

EspacioEntreEtapas::~EspacioEntreEtapas() {

}

void EspacioEntreEtapas::imprimirTituloEtapa(){
    Texto * textoAux = new Texto(30, AMARILLO_STAR_WARS, STAR_WARS_FONT2, ventana);
    stringstream ss;
    ss << "etapa " << nroEtapa << " finalizada";
    textoAux->cargarFuente(ss.str());
    textos.push_back(textoAux);
}

void EspacioEntreEtapas::decodificarPuntos(string mensaje) {
    // Cada jugador viene como un par, equipo, puntos.
    // Vienen en orden (no hace falta pasar el número).
    // TODO chequear que sea múltiplo de 2*sizeof(int) el length.
    int nroAvion;
    int equipo;
    int puntos;
    int disparos;
    int aciertos;
    int porcentaje;
    int cantJugadores;
    string nombre;
    while(mensaje.length() != 0) {
        nroAvion = Decodificador::popInt(mensaje);
        equipo = Decodificador::popInt(mensaje);
        puntos = Decodificador::popInt(mensaje);
        disparos = Decodificador::popInt(mensaje);
        aciertos = Decodificador::popInt(mensaje);
        porcentaje = Decodificador::popInt(mensaje);
        nombre = Decodificador::popString(mensaje);
        // Se agrega un texto.
        Texto * textoAux = new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
        stringstream ss;
        ss <<  "jugador: " << nombre;
        ss << " - equipo: " << equipo + 1;
        ss << " - puntaje: " << puntos;
        textoAux->cargarFuente(ss.str());
        textos.push_back(textoAux);
        Texto * textoAux2 = new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
        stringstream ss2;
        ss2 << "    estadisticas: ";
        ss2 << " disparos: " << disparos;
        ss2 << " - aciertos: " << aciertos;
        ss2 << " - punteria: " << porcentaje << "%";
        textoAux2->cargarFuente(ss2.str());
        textos.push_back(textoAux2);
        Texto * textoAux3 = new Texto(18, AMARILLO_STAR_WARS, STAR_WARS_SYMBOL, ventana);
        textoAux3->cargarFuente("$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $");
        textos.push_back(textoAux3);
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
        y += 40;
    }
}

void EspacioEntreEtapas::finalizar() {
    dibujar = false;
}
