#include <iostream>
#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"

using namespace std;

void menuMensajes(Cliente * cliente);
void menuPrincipal(Cliente * cliente);
void menuXml(Cliente * cliente);

void menuMensajes(Cliente * cliente) {
    cout << "Ingrese el id del mensaje que desea enviar. Para volver al menú anterior, ingrese 0: " <<endl;
    list<Mensaje*>::iterator iterador;
    int indice = 1;
    for (iterador = cliente->getMensajes().begin(); iterador != cliente->getMensajes().end(); iterador++ ) {
        cout << indice << ". Mensaje ID = " << (*iterador)->getId() << endl;
        ++indice;
    }
    int opcionElegida;
    cin >> opcionElegida;
    if (opcionElegida != 0) {
        iterador = cliente->getMensajes().begin();
        advance (iterador,opcionElegida - 1);
        cliente->enviarMensajePorId(opcionElegida);
        Mensaje * unMensaje;
        cliente->recibirMensaje(unMensaje);
        cout<<"Recibi el mensaje" << unMensaje->strValor() << endl;
        delete unMensaje;
    } else {
        menuPrincipal(cliente);
    }
}

void menuPrincipal(Cliente * cliente) {
    int opcion = -1;
    while (opcion != 3){
        cout << "Bienvenido, Elija la opcion que desee:" << endl;
        cout << "1. Conectar" << endl;
        cout << "2. Desconectar" << endl;
        cout << "3. Salir" << endl;
        cout << "4. Enviar mensaje <id>" << endl;
        cout << "5. Ciclar " << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                cliente->conectar();
                break;
            case 2:
                cliente->cerrar();
                break;
            case 3:
                break;
            case 4:
                //Por cada uno de los mensajes que hay en el archivo de configuracion, es decir deberia
                //existir un for que envie cada mensaje ...
                menuMensajes(cliente);
                break;
            case 5:
                int tiempo;
                //Envia mensajes en forma iterativa durante una cantiadad determinada de milisegundos.
                cout << "Ingrese el tiempo (ms): " << endl;
                cin >> tiempo;
                cliente->ciclarMensajes(tiempo);
                break;
            default: cout<< "Opcion invalida. Pulse ENTER para continuar y volver a elegir" << endl;
        }
    }
}

void menuXml() {
  cout<<"Ingrese la ruta donde se encuenta la ruta de configuracion del cliente" << endl;
  string filePath;
  cin >> filePath;
  ClienteParser clienteParser;
  cout << "Aca llega" << endl;
  Cliente * cliente = clienteParser.deserializador(filePath);
  menuPrincipal(cliente);
  delete cliente;
}

int main(){
    cout << "Aca llega" << endl;
    // TODO Esto debería pasarse por argv y argc.
    menuXml();
    return 0;
}
