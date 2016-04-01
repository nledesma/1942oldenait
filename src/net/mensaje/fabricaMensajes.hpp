#include "mensaje.hpp"
#include "mensajeInt.hpp"
#include "mensajeString.hpp"
#include "mensajeChar.hpp"
#include "mensajeDouble.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include "../../logger.hpp"
using namespace std;

class FabricaMensajes {
public:
    static Mensaje *fabricarMensaje(int id, string tipo, string valor);
    static Mensaje *fabricarMensaje(infoMensaje datos, char * valor);
};
