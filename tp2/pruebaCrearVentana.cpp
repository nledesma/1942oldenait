#include <iostream>
#include "ventana.hpp"

using namespace std;

int main(){

  //Por ahora para probar le paso estos valores, pero en realidad son los que deberian ser pasados por el XML
  Ventana* ventana = new Ventana(640, 480);
  ventana->iniciar();

  //Elimino la ventana
  delete ventana;

  return 0;
}
