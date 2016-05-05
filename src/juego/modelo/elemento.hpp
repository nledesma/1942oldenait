#ifndef INC_1942OLDENAIT_ELEMENTO_HPP
#define INC_1942OLDENAIT_ELEMENTO_HPP

#include <string>
using namespace std;

class Elemento {
private:
    int id;
    float posX;
    float posY;
    float velocidadY;
public:
    Elemento(int id, float posX, float posY, float velocidadDesplazamientoY);
    void mover(float timeStep);
    float getPosX();
    float getPosY();
    float getVelocidadY();
    int getId();
};


#endif //INC_1942OLDENAIT_ELEMENTO_HPP
