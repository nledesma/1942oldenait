#include "../net/decodificador.hpp"
#include "../juego/modelo/elemento.hpp"
#include "../juego/modelo/avion.hpp"
#include "../juego/vista/elementoVista.hpp"
#include <utility>
#include <iostream>
using namespace std;
/* Esto no es cppUnit. Esto es impresentable */

void testear(bool test, string nombre){
    if (test)
        cout << "Test " + nombre + " exitoso." << endl;
    else
        cout << "Test " + nombre + " falló." << endl;
}

bool testElemento(){
    Elemento e1(1, 1.1, 2.2, 3.3);
    ElementoVista e2(3, 20.0, 20.0);

    // Codifico e1.
    string codigo = "";
    Decodificador::push(codigo, &e1);

    // Decodifico en e2.
    pair<int, string> idCodigo;
    idCodigo = Decodificador::popElemento(codigo);
    e2.actualizar(idCodigo.second);
    if ((e2.getPosX() == e1.getPosX()) && (e2.getPosY() == e1.getPosY())) return true;
    return false;
}

int main(int argc, char const *argv[]) {
    testear(testElemento(), "elemento");
    return 0;
}
