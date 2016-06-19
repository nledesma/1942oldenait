#include "../src/menu/manejador/manejador1942.hpp"

int main() {
    Ventana ventana(800, 800);
    SoundBoard* soundboard = new SoundBoard();
    soundboard->inicializar();
    soundboard->cargarSonidos();
    soundboard->playMusicaMenu();
    ventana.iniciar();
    Cliente cliente(&ventana, soundboard);
    Manejador1942 manejador(&ventana, &cliente, soundboard);
    manejador.renderLoop();
}
