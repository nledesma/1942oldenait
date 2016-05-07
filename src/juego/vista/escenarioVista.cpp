#include "escenarioVista.hpp"

void EscenarioVista::actualizar(string codigo) {
    memcpy((void*) &(this->offset), (void*) &codigo[0], sizeof(float));
}
