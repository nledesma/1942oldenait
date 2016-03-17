#include "fruta.cpp"
int main(){
  Fruta *anana = new Fruta();
  anana->setGusto("dulce");
  anana->setPeso(30);
  anana->serializar();
  return 0;
}
