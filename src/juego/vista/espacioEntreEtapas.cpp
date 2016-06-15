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
    Texto * textoAux = new Texto(30, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    stringstream ss;
    ss << "ETAPA " << nroEtapa << " FINALIZADA";
    textoAux->cargarFuente(ss.str());
    textos.push_back(textoAux);
}

void EspacioEntreEtapas::decodificarPuntos(string mensaje) {
    // Cada jugador viene como un par, equipo, puntos.
    // Vienen en orden (no hace falta pasar el número).
    // TODO chequear que sea múltiplo de 2*sizeof(int) el length.
    int nroAvion = 1;
    int equipo;
    int puntos;
    int cantJugadores;
    string nombre;
    map<int, string> nombreSegunNroAvion;
    while(mensaje.length() != 0) {
        equipo = Decodificador::popInt(mensaje);
        puntos = Decodificador::popInt(mensaje);
        cantJugadores = Decodificador::popInt(mensaje);
        for (int i = 0; i < cantJugadores; i ++){
            nombreSegunNroAvion[i] = Decodificador::popString(mensaje);
        }
        // Se agrega un texto.
        Texto * textoAux = new Texto(30, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
        stringstream ss;
        ss << nombreSegunNroAvion[nroAvion];
        ss << " - Equipo: " << equipo + 1;
        ss << " - puntos: " << puntos;
        textoAux->cargarFuente(ss.str());
        textos.push_back(textoAux);
        ++nroAvion;
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
