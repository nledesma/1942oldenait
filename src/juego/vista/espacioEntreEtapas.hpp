#ifndef ESPACIO_ENTRE_ETAPAS_HPP
#define ESPACIO_ENTRE_ETAPAS_HPP

#include <sstream>
#include "ventana.hpp"
#include "texto.hpp"
#include "../../net/decodificador.hpp"
#include <utility> // pair
#include <map>
#include <string>

using namespace std;

class EspacioEntreEtapas {
private:
    int nroEtapa;
    Ventana * ventana;
    Figura * fondo;
    list<Texto*> textos;
    vector<pair<int,int> > puntajes;
    bool porEquipos;
    bool dibujar;
public:
    EspacioEntreEtapas(Ventana * ventana, string mensajeInicial, int nroEtapa);
    void imprimirTituloEtapa();
    void imprimirTituloReiniciar();
    void finalizar();
    int renderLoop();
    void renderTextos();
    void decodificarPuntos(string mensaje);
    virtual ~EspacioEntreEtapas ();
};

#endif
