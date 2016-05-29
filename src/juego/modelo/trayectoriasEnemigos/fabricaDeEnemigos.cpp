#include "fabricaEnemigos.hpp"
// TODO: incluir clases de aviones enemigos 
#include <string>
#include <iostream>
using namespace std;

AvionEnemigo *FabricaMensajes::fabricarEnemigo(string tipo, string cantidad){
  if (tipo == "pequenio") return new AvionPequenio(id, valor);
  if (tipo == "escuadron") return new AvionDeEscuadron(id, valor);
  if (tipo == "mediano") return new AvionMediano(id, valor);
  if (tipo == "grande") return new AvionGrande(id, valor);
  // TODO LOG.
  cout « "Tipo no válido, no se pudo crear enemigo." « endl;
  return NULL;
}
