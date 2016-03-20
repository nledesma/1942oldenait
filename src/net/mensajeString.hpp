#ifndef MENSAJE_STRING_H
#define MENSAJE_STRING_H
#include "mensaje.hpp"
#include <string>
using namespace std;

class MensajeString: public Mensaje{
private:
  string valor;
public:
  MensajeString(int unId, string valor);
  int getTipo();
  void setTipo(int unTipo);
  void setValor(string unValor);
  string getValor();
  string strTipo();
  string strValor();
};

#endif
