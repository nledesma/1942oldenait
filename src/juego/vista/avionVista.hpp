#ifndef INC_1942OLDENAIT_AVIONVISTA_HPP
#define INC_1942OLDENAIT_AVIONVISTA_HPP

#include <string>
#include <cstring>
using namespace std;

class AvionVista {
private:
    float posX;
    float posY;
    int estadoAnimacion;
public:
    void actualizar(string codigo);
};


#endif //INC_1942OLDENAIT_AVIONVISTA_HPP
