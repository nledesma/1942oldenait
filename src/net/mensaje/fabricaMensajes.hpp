#include "mensaje.hpp"
#include "mensajeInt.hpp"
#include "mensajeString.hpp"
#include "mensajeChar.hpp"
#include "mensajeDouble.hpp"

class FabricaMensajes {
public:
    Mensaje *fabricarMensaje(int id, string tipo, string valor);
    //? Mensaje * fabricarMensaje(int id, int tipo, string valor)
};
