#ifndef MENSAJE_CHAR_H
#define MENSAJE_CHAR_H

#include "mensaje.hpp"
#include <string>

using namespace std;

class MensajeChar : public Mensaje {
private:
    char valor;
public:
    MensajeChar(int unId, string valor);

    MensajeChar(infoMensaje datos, char *unValor);

    int getTipo();

    void setTipo(int unTipo);

    void setValor(char unValor);

    char getValor();

    string strTipo();

    string strValor();

    const char *codificar();

    int lengthValor();
};

#endif // MENSAJE_CHAR_H
