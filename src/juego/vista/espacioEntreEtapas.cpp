#include "espacioEntreEtapas.hpp"

EspacioEntreEtapas::EspacioEntreEtapas(Ventana * ventana, string mensaje) {
    this->ventana = ventana;
    this->fondo = new Figura();
    // TODO path constante.
    this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas");
    porEquipos = (bool) Decodificador::popInt(mensaje);
    decodificarPuntos(mensaje);
    dibujar = true;
}

EspacioEntreEtapas::~EspacioEntreEtapas() {

}

void EspacioEntreEtapas::decodificarPuntos(string mensaje) {
    // Cada jugador viene como un par, equipo, puntos.
    // Vienen en orden (no hace falta pasar el número).
    // TODO chequear que sea múltiplo de 2*sizeof(int) el length.
    int nroAvion = 1;
    int equipo;
    int puntos;
    while(mensaje.length() != 0) {
        equipo = Decodificador::popInt(mensaje);
        puntos = Decodificador::popInt(mensaje);
        // Se agrega un texto.
        Texto * textoAux = new Texto(30, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
        stringstream ss;
        ss << "Avion: " << nroAvion;
        ss << " - Equipo: " << equipo + 1;
        ss << " - puntos: " << puntos;
        textoAux->cargarFuente(ss.str());
        textos.push_back(textoAux);
        ++nroAvion;
    }

}

void EspacioEntreEtapas::renderLoop() {
    // TODO mejorar x e y.
    while(dibujar) {
        fondo->render(0, 0, ventana->getVentanaRenderer());
        renderTextos();
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
    cout << "FIN RENDER LOOP";
}

void EspacioEntreEtapas::renderTextos() {
    list<Texto*>::iterator it;
    int x = 10;
    int y = 10;
    for (it = textos.begin(); it != textos.end(); ++it) {
        (*it)->renderizar(x, y);
        y += 40;
    }
}

void EspacioEntreEtapas::finalizar() {
    dibujar = false;
}
