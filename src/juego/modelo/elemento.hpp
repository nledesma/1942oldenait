#ifndef INC_1942OLDENAIT_ELEMENTO_HPP
#define INC_1942OLDENAIT_ELEMENTO_HPP

#include <string>
using namespace std;

class Elemento {
private:
    float posX;
    float posY;
    float velocidadY;
    float posXInicial;
    float posYInicial;
public:
    Elemento(float posX, float posY, float velocidadDesplazamientoY);
    void mover(float timeStep);
    float getPosX();
    float getPosY();
    float getVelocidadY();
    void volverEstadoInicial();
};


#endif //INC_1942OLDENAIT_ELEMENTO_HPP
