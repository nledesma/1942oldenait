#include "espacioEntreEtapas.hpp"

EspacioEntreEtapas::EspacioEntreEtapas(Ventana * ventana, string mensaje) {
    this->ventana = ventana;
    porEquipos = (bool) Decodificador::popInt(mensaje);
    decodificarPuntos(mensaje);
    renderLoop();
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
        // por ahora solo hace couts. Luego va a dibujar.
        cout << "Avión: " << nroAvion;
        cout << " - Equipo: " << equipo;
        cout << " - puntos: " << puntos << endl;
        ++nroAvion;
    }
}

void EspacioEntreEtapas::renderLoop() {

}
