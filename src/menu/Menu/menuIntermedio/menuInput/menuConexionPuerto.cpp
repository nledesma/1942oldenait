#include "menuConexionPuerto.hpp"

MenuConexionPuerto::MenuConexionPuerto(Ventana * ventana, Cliente * cliente) : MenuInput(ventana){
    titulo->cargarFuente("INGRESE PUERTO");
    aviso = new Aviso(ventana);
    this->cliente = cliente;
}


void MenuConexionPuerto::setMenuIP(Menu * menu) {
    anterior = menu;
}

void MenuConexionPuerto::setMenuEquipos(Menu * menu) {
    siguiente = menu;
}

void MenuConexionPuerto::accionAnterior() {}

void MenuConexionPuerto::accionSiguiente() {
    cout << "acá se debería setear la IP." << input->getTexto() << endl;
    cout << "Luego de setear la IP se debería conectar." << endl;
}


int MenuConexionPuerto::manejarEvento(SDL_Event * e) {
    aviso->manejarEvento(e);
    if (esTecla(e,SDLK_RETURN) || botonSiguiente->manejarEvento(e) == BOTON_APRETADO) {
        stringstream ss; ss << input->getTexto();
        int puerto;
        ss >> puerto;
        this->cliente->setAddress(((MenuConexionManual*)anterior)->getIP(), puerto);

        if (cliente->conectar(aviso)) {
            string elServidorNecesitaEquipo;
            cout << "El servidor nos dirá si es por equipos." << endl;
            if(cliente->recibirMensaje(elServidorNecesitaEquipo) != MENSAJEOK) return SALIR;
            if (Decodificador::popBool(elServidorNecesitaEquipo))
                // Si necesitamos elegir equipo, vamos al siguiente. Si no, jugamos.
                return SIGUIENTE;
            return JUGAR;
            // Después de la elección de  equipo, si la hubo, se procede con el juego.
        }
        // Si no se pudo conectar, nos quedamos en la misma pantalla.
        return NADA;
    }
    return MenuInput::manejarEvento(e);
}

void MenuConexionPuerto::render() {
    MenuInput::render();
    aviso->render();
}
