#include "listaDeSeleccion.hpp"
ListaDeSeleccion::ListaDeSeleccion(){}

void ListaDeSeleccion::agregarOpcion(string strOpcion, SDL_Renderer* renderer){
    SDL_Color color = {0, 0, 0};
    Texto* texto = new Texto(20, color);
    RadioButton* boton = new RadioButton(renderer);
    pair<RadioButton*, Texto*> par = make_pair(boton, texto);
    opciones.push_back(par);
}

void ListaDeSeleccion::renderizar(SDL_Renderer* renderer){
    list <pair <RadioButton*, Texto*> > ::iterator iterador;
    int y = 40;
    for(iterador = opciones.begin(); iterador != opciones.end(); iterador++){
        iterador->first->renderizar(20, y, renderer);
        iterador->second->renderizar(30, y, renderer);
        y += 40;
    }
}
