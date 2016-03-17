#include "fruta.cpp"

using namespace std;

int main(){
  Fruta *anana = new Fruta();
  anana->deserializar("fruta.xml");
  cout<<anana->getGusto()<<endl<<anana->getPeso();
  return 0;
}
