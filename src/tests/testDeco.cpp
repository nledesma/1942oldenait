#include "../net/decodificador.hpp"
#include "../juego/modelo/elemento.hpp"
#include "../juego/modelo/avion.hpp"
#include "../juego/vista/elementoVista.hpp"
#include <utility>
#include <iostream>
using namespace std;
/* Esto no es cppUnit. Esto es impresentable */

bool testElemento(){
    Elemento e1(20, 3.3, 3.3, 3.3);
    ElementoVista e2(3, 1.0, 1.0);

    // Codifico e1.
    string codigo = "";
    Decodificador::push(codigo, &e1);

    // Decodifico en e2.
    pair<int, string> idCodigo;
    idCodigo = Decodificador::popElemento(codigo);
    e2.actualizar(idCodigo.second);
    if (e2.getPosX() == 3.3 && e2.getPosY() == 3.3) return true;
    return false;
}

int main(int argc, char const *argv[]) {

    if (testElemento()){
        cout << "Test elemento exitoso" << endl;
    } else {
        cout << "Test elemento falló" << endl;
    }

    
    return 0;
}
