#include "../net/decodificador.hpp"
#include "../juego/modelo/elemento.hpp"
#include <utility>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
    Elemento e1(20, 3.3, 3.3, 3.3);
    ElementoVista e2(3, 1.0, 1.0);

    // Codifico e1.
    string codigo = "";
    Decodificador::push(codigo, &e1);

    // Decodifico en e2.
    pair<int, string> idCodigo;
    idCodigo = Decodificador::popElemento(codigo);
    e2.actualizar(idCodigo.second);
    cout << "posX vista: " << e2.getPosX() << endl;
    cout << "posY vista: " << e2.getPosY() << endl;

    return 0;
}
