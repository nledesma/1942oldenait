#include "../trigonomaster.hpp"

class Superficie{
private:
    float izqAbajo[2];
    float izqArriba[2];
    float derArriba[2];
    float derAbajo[2];

public:
    Superficie(float posX, float posY, int ancho, int alto);
    void mover(float x, float y);
    bool colisiona(Superficie * superficie);
    void rotar(float angulo, float x, float y);
    float[2] getIzqAbajo();
    float[2] getIzqArriba();
    float[2] getDerArriba();
    float[2] getDerAbajo();

}
