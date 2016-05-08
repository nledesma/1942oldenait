#ifndef INC_1942OLDENAIT_ELEMENTO_HPP
#define INC_1942OLDENAIT_ELEMENTO_HPP

#include <string>
using namespace std;

class Elemento {
private:
    float posX;
    float posY;
    float posXInicial;
    float posYInicial;
    string idSprite;
public:
    Elemento(float posX, float posY, string idSprite);
    void mover(float timeStep, float velocidadY);
    float getPosX();
    float getPosY();
    void volverEstadoInicial();
    string getIdSprite();
};


#endif //INC_1942OLDENAIT_ELEMENTO_HPP
