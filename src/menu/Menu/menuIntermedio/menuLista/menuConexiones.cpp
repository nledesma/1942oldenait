#include "menuConexiones.hpp"

MenuConexiones::MenuConexiones(Ventana* ventana, Cliente * cliente) : MenuLista(ventana){
    this->cliente = cliente;
    titulo->cargarFuente("CONEXIONES");
    aviso = new Aviso(ventana);
    agregarOpciones();
}

MenuConexiones::~MenuConexiones() {
    //TODO Liberar cosas.
}

void MenuConexiones::agregarOpciones() {
    conexionesGuardadas = ClienteParser::levantarConexiones();
    list<Conexion>::iterator it;
    for(it = conexionesGuardadas.begin(); it != conexionesGuardadas.end(); it ++){
        string conexion = it->nombre + ". ip: " + it->ip + ". puerto: " + to_string(it->puerto);
        lista->agregarOpcion(conexion);
    }
    lista->agregarOpcion("conexion manual");
}

void MenuConexiones::accionAnterior() {}

void MenuConexiones::accionSiguiente() {
    if (lista->getNroBotonSeleccionado() != lista->getCantidadOpciones() - 1) {
        siguiente = menuPorEquipos;
    } else {
        siguiente = menuConexionManual;
    }
}

void MenuConexiones::setMenuConexionManual(Menu * m) {
    this->menuConexionManual = m;
}

void MenuConexiones::setMenuPorEquipos(Menu * m) {
    this->menuPorEquipos = m;
}

void MenuConexiones::setMenuDatosUsuario(Menu * m) {
    this->anterior = m;
}


int MenuConexiones::manejarEvento(SDL_Event * e) {
    aviso->manejarEvento(e);
    if (esTecla(e,SDLK_RETURN) || botonSiguiente->manejarEvento(e) == BOTON_APRETADO) {
        if (lista->getNroBotonSeleccionado() != lista->getCantidadOpciones() - 1) {
            // Caso conexión específica.
            list<Conexion>::iterator it = conexionesGuardadas.begin();
            advance(it, lista->getNroBotonSeleccionado());
            this->cliente->setAddress(it->ip, it->puerto);
            cout << "Se seteó la dirección en " << it->ip << ":" << it->puerto << endl;
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
        } else {
            // Si está seleccionada la última.
            return SIGUIENTE;
        }
    }
    return MenuLista::manejarEvento(e);
}

void MenuConexiones::render() {
    MenuLista::render();
    aviso->render();
}
