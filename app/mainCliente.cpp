#include <iostream>
#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"

#define DEFAULT_XML "../../resources/xml/clienteDefault.xml"

using namespace std;

void menuMensajes(Cliente * cliente);
void menuPrincipal(Cliente * cliente);
void menuXml(Cliente * cliente);

void menuMensajes(Cliente * cliente) {
    string opcionElegida;
    do {
        // Impresión de mensajes a elegir.
        cout << "Ingrese el id del mensaje que desea enviar. Para volver al menú anterior, ingrese 0: " <<endl;
        list<Mensaje*>::iterator iterador;
        for (iterador = cliente->getMensajes().begin(); iterador != cliente->getMensajes().end(); iterador++ ) {
            cout << "ID = " << (*iterador)->getId() << " - Mensaje: " << (*iterador)->getValor() << endl;
        }

        cin >> opcionElegida;

        // Envío de mensaje.
        // TODO chequear que la opción corresponde a un id existente, porque muere.
        if (opcionElegida != "0") {
            cliente->enviarMensajePorId(opcionElegida);
            Mensaje * unMensaje;
            cliente->recibirMensaje(unMensaje);
            cout<< "Recibi el mensaje " << unMensaje->getValor() << endl;
            delete unMensaje;
        }
    } while (opcionElegida != "0");
}

void menuPrincipal(Cliente * cliente) {
    int opcion = -1;
    while (opcion != 3){
        cout << "-----------------------------------------------------" << endl;
        cout << "Bienvenido, Elija la opcion que desee:" << endl;
        cout << "1. Conectar" << endl;
        cout << "2. Desconectar" << endl;
        cout << "3. Salir" << endl;
        cout << "4. Enviar mensaje <id>" << endl;
        cout << "5. Ciclar " << endl;
        cout << "-----------------------------------------------------" << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                if (cliente->conectado()){
                    cout << "El cliente ya está conectado." << endl;
                } else {
                    cliente->conectar();
                }
                break;
            case 2:
                if (cliente->conectado()){
                    cliente->cerrar();
                } else {
                    cout << "El cliente no está conectado." << endl;
                }
                break;
            case 3:
                break;
            case 4:
                menuMensajes(cliente);
                break;
                case 5:
                int tiempo;
                // Envia mensajes en forma iterativa durante una cantiadad determinada de milisegundos.
                cout << "Ingrese el tiempo (ms): " << endl;
                cin >> tiempo;
                cliente->ciclarMensajes(tiempo);
                break;
            default:
                cout<< "Opcion invalida. Pulse ENTER para continuar y volver a elegir" << endl;
                break;
        }
    }
}

void menuXml(string rutaXML) {
    ClienteParser clienteParser;
    Cliente * cliente = clienteParser.deserializador(rutaXML);
    menuPrincipal(cliente);
    delete cliente;
}

int main(int argc, char* argv[]){
    string rutaXMLCliente;

    if (argc < 2){
        cout << "Argumentos insuficientes, se utilizará el XML por defecto" << endl;
        Logger::instance()->logWarning("No se ingresó la cantidad de parámetros suficientes. Se inicializa el cliente con el XML por defecto");
        rutaXMLCliente = (DEFAULT_XML);
    } else {
        rutaXMLCliente = argv[1];
    }

    menuXml(rutaXMLCliente);
    return 0;
}
