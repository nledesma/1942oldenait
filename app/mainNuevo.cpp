#include "../src/menu/manejador/manejador1942.hpp"

int main() {
    Ventana ventana(800, 800);
    ventana.iniciar();
    Cliente cliente(&ventana);
    Manejador1942 manejador(&ventana, &cliente);
    manejador.renderLoop();
}
