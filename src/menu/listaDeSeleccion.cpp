#include "listaDeSeleccion.hpp"

ListaDeSeleccion::ListaDeSeleccion(Ventana * ventana, int x, int y) {
    this->ventana = ventana;
    this->x = x;
    this->y = y;
    cout << "Se crea la lista en x: " << x << " - y: " << y << endl;
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
    SDL_Color color = {0, 0, 0};
    Texto* texto = new Texto(20, color, this->ventana);
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
