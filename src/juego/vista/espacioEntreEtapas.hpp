#ifndef ESPACIO_ENTRE_ETAPAS_HPP
#define ESPACIO_ENTRE_ETAPAS_HPP

#include "ventana.hpp"
#include "texto.hpp"
#include "../../net/decodificador.hpp"

class EspacioEntreEtapas {
private:
    Ventana * ventana;
    vector<pair<int,int> > puntajes;
    vector<Texto> textosPuntajes;
    bool porEquipos;
public:
    EspacioEntreEtapas(Ventana * ventana, string mensajeInicial);
    void renderLoop();
    void decodificarPuntos(string mensaje);
    virtual ~EspacioEntreEtapas ();
};

#endif
