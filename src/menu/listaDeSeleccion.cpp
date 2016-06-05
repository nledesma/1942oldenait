#include "listaDeSeleccion.hpp"
ListaDeSeleccion::ListaDeSeleccion(Ventana * ventana){
    this->ventana = ventana;
}

void ListaDeSeleccion::agregarOpcion(string strOpcion) {
    SDL_Color color = {0, 0, 0};
    Texto* texto = new Texto(20, color, this->ventana);
    texto->cargarFuente(strOpcion);
    RadioButton* boton = new RadioButton(this->ventana->getVentanaRenderer());
    pair<RadioButton*, Texto*> par = make_pair(boton, texto);
    opciones.push_back(par);
}

void ListaDeSeleccion::renderizar() {
    list <pair <RadioButton*, Texto*> > ::iterator iterador;
    int y = 40;
    for(iterador = opciones.begin(); iterador != opciones.end(); iterador++) {
        iterador->first->renderizar(20, y - 10, this->ventana->getVentanaRenderer());
        iterador->second->renderizar(60, y);
        y += 40;
    }
}

ListaDeSeleccion::~ListaDeSeleccion() {
    while (!opciones.empty()) {
        delete opciones.begin()->first;
        delete opciones.begin()->second;
        opciones.erase(opciones.begin());
    }
}
