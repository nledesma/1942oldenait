#include <string>
#include <iostream>
#include "tinyxml2.cpp"

using namespace std;
using namespace tinyxml2;
using namespace std;

class Fruta{
  private:
    string gusto;
    int peso;
  public:
    string getGusto(){
      return gusto;
    }
    int getPeso(){
      return peso;
    }
    void setGusto(string gusto){
      this->gusto = gusto;
    }
    void setPeso(int peso){
      this->peso = peso;
    }
   
    void serializar(){
      XMLDocument doc;

      // Root
      XMLNode * pRoot = doc.NewElement("Fruta");
      doc.InsertFirstChild(pRoot);

      // Hijos del root. TODO: diferencia entre element y node.
      XMLElement * pNodoGusto = doc.NewElement("gusto");
      (*pNodoGusto).SetText(10);

      XMLElement * pNodoPeso = doc.NewElement("peso");
      // castear a string?
      (*pNodoPeso).SetText(10);

      // Inserto ambos elementos al root.
      pRoot -> InsertFirstChild(pNodoGusto);
      pRoot -> InsertFirstChild(pNodoPeso);

      XMLError e = doc.SaveFile("fruta.xml");
      if (e != XML_SUCCESS){
        cout << "Error! " << e << endl;
      }
    }

    void deserializar (string ruta) {
      XMLDocument xmlDoc;
      XMLError eResult = xmlDoc.LoadFile("fruta.xml");

      XMLNode * pRoot = xmlDoc.FirstChildElement();
      XMLElement * pElement = pRoot -> FirstChildElement("peso");

      int unPeso;
      eResult = pElement -> QueryIntText(&unPeso);

      pElement = pRoot -> FirstChildElement("gusto");
      
      string unGusto;
      unGusto = pElement -> Value();

      peso = unPeso;
      gusto = unGusto;
  }
};
