#ifndef INC_1942OLDENAIT_SUPERFICIE_HPP
#define INC_1942OLDENAIT_SUPERFICIE_HPP

#include "../trigonomaster.hpp"
#include "punto.hpp"

class Superficie{
private:
    Punto* izqAbajo;
    Punto* izqArriba;
    Punto* derArriba;
    Punto* derAbajo;
    int ancho;
    int alto;
    int offSetX;
    int offSetY;

public:
    Superficie(float posX, float posY, int ancho, int alto, int offSetX, int offSetY);
    void mover(float x, float y);
    bool colisiona(Superficie * superficie);
    void rotar(float angulo, float x, float y);
    Punto* getIzqAbajo();
    Punto* getIzqArriba();
    Punto* getDerArriba();
    Punto* getDerAbajo();
    int getAncho();
    int getAlto();
    pair<float, float> proyectar(Superficie * superficie, Punto * punto);
    bool proyeccionesSuperpuestas(pair<float, float> unaProyeccion, pair<float, float> otraProyeccion);

};

#endif
