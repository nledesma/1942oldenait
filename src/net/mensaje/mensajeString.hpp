#ifndef MENSAJE_STRING_H
#define MENSAJE_STRING_H

#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include "mensaje.hpp"
#include <string>

using namespace std;

class MensajeString : public Mensaje {
private:
    string valor;
public:
    MensajeString(int unId, string valor);

    MensajeString(infoMensaje datos, char *unValor);

    int getTipo();

    void setTipo(int unTipo);

    void setValor(string unValor);

    string getValor();

    string strTipo();

    string strValor();

    const char *codificar();

    int lengthValor();
};

#endif
