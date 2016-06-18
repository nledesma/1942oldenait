#include "../src/menu/manejador/manejador1942.hpp"

int main() {
    Ventana* ventana = new Ventana(800, 800);
    ventana->iniciar();
    Manejador1942 manejador(ventana);
    manejador.renderLoop();
}
