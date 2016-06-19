#include "listaDeSeleccion.hpp"

ListaDeSeleccion::ListaDeSeleccion(Ventana * ventana, int x, int y) {
    this->ventana = ventana;
    this->x = x;
    this->y = y;
    //cout << "Se crea la lista en x: " << x << " - y: " << y << endl;
}

// NOTE esto debe hacerse antes de cerrar la ventana. Quizás convenga un método cerrar.
ListaDeSeleccion::~ListaDeSeleccion() {
    while (!opciones.empty()) {
        delete opciones.begin()->first;
        delete opciones.begin()->second;
        opciones.erase(opciones.begin());
    }
}

void ListaDeSeleccion::agregarOpcion(string strOpcion) {
    SDL_Color color = {255, 232, 32};
    Texto* texto = new Texto(20, color, STAR_WARS_FONT, this->ventana);
    texto->cargarFuente(strOpcion);
    RadioButton* boton = new RadioButton(this->ventana->getVentanaRenderer());
    if (opciones.size() == 0) {
        boton->seleccionar();
        nroBotonSeleccionado = 0;
    }
    pair<RadioButton*, Texto*> par = make_pair(boton, texto);
    opciones.push_back(par);
}

void ListaDeSeleccion::renderizar() {
    list <pair <RadioButton*, Texto*> > ::iterator iterador;
    int yOpcion = 0;
    for(iterador = opciones.begin(); iterador != opciones.end(); iterador++) {
        iterador->first->renderizar(x, y + yOpcion, this->ventana->getVentanaRenderer());
        iterador->second->renderizar(x + PADDING, y + yOpcion + 10);
        yOpcion += DISTANCIA_BOTONES;
    }
}

void ListaDeSeleccion::manejarEvento(SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        // Si es un click de mouse entonces se maneja el click.
        int x, y;
        SDL_GetMouseState( &x, &y );
        clickEn(x,y);
    } else if (e->type == SDL_KEYUP) {
        // Los botones importantes son arriba y abajo.
        if (e->key.keysym.sym == SDLK_UP) {
            if (nroBotonSeleccionado != 0) {
                cambiarSeleccion(nroBotonSeleccionado - 1);
            }
        } else if (e->key.keysym.sym == SDLK_DOWN) {
            if (nroBotonSeleccionado != opciones.size() - 1) {
                cambiarSeleccion(nroBotonSeleccionado + 1);
            }
        }
    }
}

int ListaDeSeleccion::getCantidadOpciones(){
    return opciones.size();
}

void ListaDeSeleccion::clickEn(int x, int y){
    int lado = PADDING;
    int altoTotal = PADDING*opciones.size();
    // Si el click está en el área de los botones.
    if ((x >= this->x) && (x <= this->x + lado) &&
        (y >= this->y) && (y <= this->y + altoTotal)) {
        int nroBoton = (y - this->y)/PADDING;
        cambiarSeleccion(nroBoton);
    }
}

RadioButton * ListaDeSeleccion::boton(int nroBoton) {
    list <pair <RadioButton*, Texto*> > ::iterator iterador = opciones.begin();
    advance(iterador, nroBoton);
    return iterador->first;
}

void ListaDeSeleccion::cambiarSeleccion(int nroBoton) {
    boton(nroBotonSeleccionado)->deseleccionar();
    boton(nroBoton)->seleccionar();
    nroBotonSeleccionado = nroBoton;
}

int ListaDeSeleccion::getNroBotonSeleccionado() {
    return nroBotonSeleccionado;
}
