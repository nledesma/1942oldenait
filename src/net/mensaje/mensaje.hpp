#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>
#include <cstring> // memcpy
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#define T_STRING 0
#define T_INT 1
#define T_DOUBLE 2
#define T_CHAR 3
#define LONG_INFO_MENSAJE 9
// Utilizamos 32 bits para evitar incompatibilidades.
#define INT_SIZE 4
#define DOUBLE_SIZE 8
#define MENSAJEOK 1

struct infoMensaje {
    int tipo;
    int longitudId;
    int longitudValor;
};

class Mensaje {
private:
    int tipo;
    string id;
    string valor;
public:
    Mensaje(int tipo, string id, string valor);

    Mensaje(infoMensaje datos, char *contenido);

    ~Mensaje();

    string getId();

    string getValor();

    int getTipo();

    string strTipo();

    int lengthId();

    int lengthValor();

    /* Genera el siguiente array de bytes para codificar un mensaje
    ** - 1 byte para el tipo.
    ** - 4 bytes para la longitud del id.
    ** - 4 bytes para la longitud del valor.
    ** - longitudID bytes para el valor.
    ** - longitudValor bytes para el valor.
    */
    const char *codificar();

    /* Recibe 9 bytes y genera la struct.
    ** - 1 bytes para tipo.
    ** - 4 bytes para longitudID.
    ** - 4 bytes para longitudValor.
    */
    static infoMensaje decodificarInfo(char *pInfoMensaje);

    void set(int tipo, string id, string valor);

    void set(infoMensaje datos, char *pMensaje);

    // Estas dos cosas habría que meterlas en otro lado.
    static void imprimirBytes(const char *bytes, int n);

    void pushearInt(string &str, int n);
};

#endif
