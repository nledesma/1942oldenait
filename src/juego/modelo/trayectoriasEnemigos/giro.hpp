#ifndef INC_1942OLDENAIT_GIRO_HPP
#define INC_1942OLDENAIT_GIRO_HPP

#include "../../../accesorios/trigonomaster.hpp"
#include "tipoMovimiento.hpp"

class Giro : public TipoMovimiento {
private:
    float anguloAbarrer;
    float velocidadAngular;
    float anguloAbarrerInicial;
    float velocidadAngularInicial;
    float transportarAngulo(float &angulo, float velocidadAngular,float timestep);
public:
    Giro(float anguloAbarrer, float velocidadAngular);
    ~Giro();
    bool mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
    void setEstadoInicial();
};


#endif //INC_1942OLDENAIT_GIRO_HPP
