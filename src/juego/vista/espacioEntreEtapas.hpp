#ifndef ESPACIO_ENTRE_ETAPAS_HPP
#define ESPACIO_ENTRE_ETAPAS_HPP

#include <sstream>
#include "ventana.hpp"
#include "texto.hpp"
#include "../../net/decodificador.hpp"

class EspacioEntreEtapas {
private:
    Ventana * ventana;
    Figura * fondo;
    list<Texto*> textos;
    vector<pair<int,int> > puntajes;
    bool porEquipos;
    bool dibujar;
public:
    EspacioEntreEtapas(Ventana * ventana, string mensajeInicial);
    void finalizar();
    int renderLoop();
    void renderTextos();
    void decodificarPuntos(string mensaje);
    virtual ~EspacioEntreEtapas ();
};

#endif
