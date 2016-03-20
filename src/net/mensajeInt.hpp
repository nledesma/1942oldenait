#ifndef MENSAJE_INT_H
#define MENSAJE_INT_H
#include "mensaje.hpp"
#include <string>
using namespace std;

class MensajeInt: public Mensaje{
private:
  int valor;
public:
  MensajeInt(int unId, string valor);
  int getTipo();
  void setTipo(int unTipo);
  void setValor(int unValor);
  int getValor();
  string strTipo();
  string strValor();
};

#endif
