#include "mensaje.hpp"
#include "mensajeInt.hpp"
#include "mensajeString.hpp"
#include "mensajeChar.hpp"
#include "mensajeDouble.hpp"

class FabricaMensajes {
public:
    // TODO pasar a static.
    Mensaje *fabricarMensaje(int id, string tipo, string valor);
    static Mensaje *fabricarMensaje(infoMensaje datos, char * valor);
};
