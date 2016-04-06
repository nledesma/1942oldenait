#ifndef MENSAJE_DOUBLE_H
#define MENSAJE_DOUBLE_H

#include "mensaje.hpp"
#include <string>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;

class MensajeDouble : public Mensaje {
private:
    double valor;
public:
    MensajeDouble(int unId, string valor);

    MensajeDouble(infoMensaje datos, char *unValor);

    int getTipo();

    void setTipo(int unTipo);

    void setValor(double unValor);

    double getValor();

    string strTipo();

    string strValor();

    const char *codificar();

    int lengthValor();
};

#endif
