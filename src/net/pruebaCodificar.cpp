#include "mensajeChar.hpp"
#include "mensajeString.hpp"
#include "mensajeInt.hpp"
#include "mensajeDouble.hpp"
#include <iostream>
#include <string>
using namespace std;
int main(){

  MensajeString mensaje(3, "HOLA");
  const char* mensajeCodificado = mensaje.codificar();
  cout << "Tipo:  " << (int)mensajeCodificado[0] << endl;
  for(int i = 1; i < 5; i++){
    cout << "Longitud " << (int)mensajeCodificado[i] << endl;
  }
  for(int i = 5; i < 9; i++){
    cout << "ID " << (int)mensajeCodificado[i] << endl;
  }
  for(int i = 9; i < 9 + mensajeCodificado[4]+ (mensajeCodificado[3] << 8) + (mensajeCodificado[2] << 16) + (mensajeCodificado[1] << 24); i++){
    cout << "Valor " << (int)mensajeCodificado[i] << endl;
  }

  return 0;
}
