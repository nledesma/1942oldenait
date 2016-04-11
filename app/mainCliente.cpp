#include <iostream>
#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"

#define DEFAULT_XML "../../resources/xml/clienteDefault.xml"

using namespace std;

void menuMensajes(Cliente * cliente);
void menuPrincipal(Cliente * cliente);
void menuXml(Cliente * cliente);

void mostrarMensajes(Cliente * cliente){

  list<Mensaje*>::iterator iterador;
  for (iterador = cliente->getMensajes().begin(); iterador != cliente->getMensajes().end(); iterador++ ) {
      cout << "ID = " << (*iterador)->getId() << " - Mensaje: " << (*iterador)->getValor() << endl;
  }
}
void menuMensajes(Cliente * cliente) {
    string opcionElegida = "";
    do {
        // Impresión de mensajes a elegir.
        cout << "-----------------------------------------------------" << endl;
        cout << "Ingrese el id del mensaje que desea enviar. Para volver al menú anterior, ingrese 0: " <<endl;
        mostrarMensajes(cliente);
        cout << "-----------------------------------------------------" << endl;
        cin >> opcionElegida;
        // Envío de mensaje.
        if (opcionElegida != "0") {
            int resultado = cliente->enviarMensajePorId(opcionElegida);
            if(resultado == MENSAJE_INEXISTENTE){
              cout << "El id ingresado es incorrecto, seleccione nuevamente: " << endl;
              opcionElegida = "0";
              menuMensajes(cliente);
            }
            if(resultado != MENSAJE_INEXISTENTE){
              if (resultado != PEER_ERROR) {
                  Mensaje * unMensaje;
                  resultado = cliente->recibirMensaje(unMensaje);
                  if (resultado != PEER_ERROR && resultado != PEER_DESCONECTADO){
                      string msj =  "Recibi el mensaje: " + unMensaje->getValor();
                      cout << msj << endl;
                      Logger::instance()->logInfo(msj);
                      delete unMensaje;
                  } else if (resultado == PEER_DESCONECTADO) {
                      cout << "Falló la recepción porque el servidor se desconectó. Se procede a desconectar del servidor" << endl;
                      opcionElegida = "0";
                  } else {
                      cout << "Falló la recepción porque hubo un error de conexión. Se procede a desconectar del servidor" << endl;
                      opcionElegida = "0";
                  }
                  } else {
                    cout << "Falló el envío porque hubo un error de conexión. Se procede a desconectar del servidor" << endl;
                    opcionElegida = "0";
                  }
              }
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
        cout << "-----------------------------------------------------" << endl;
        cout << "Opción elegida: " << opcion << endl;
        int result;
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
                if (cliente->conectado()){
                  menuMensajes(cliente);
                } else {
                    Logger::instance()->logWarning("No se pueden enviar mensajes sin haber establecido una conexión previamente");
                    cout << "No se ha podido enviar mensajes pues el cliente no se encuentra conectado" << endl;
                }
                break;
                case 5:
                int tiempo;
                // Envia mensajes en forma iterativa durante una cantiadad determinada de milisegundos.
                cout << "Ingrese el tiempo (ms): " << endl;
                cin >> tiempo;
                result = cliente->ciclarMensajes(tiempo);
                if (result == PEER_DESCONECTADO){
                    cout << "La acción no pudo completarse porque el servidor se desconectó." << endl;
                } else if (result == PEER_ERROR){
                    cout << "La acción no pudo completarse porque hubo un error en la conexión. Se cierra la conexión con el servidor" << endl;
                } else {
                    cout << "Ciclo de envío de mensajes realizado exitosamente." << endl;
                }
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
    if(cliente == NULL) {
      cout << "Error cargando el archivo provisto. Se procederá con la configuración por defecto." << endl;
      cliente = clienteParser.deserializador(DEFAULT_XML);
        if (cliente == NULL) {
          cout << "Hubo un error al iniciar el programa. Presione cualquier tecla para cerrar" << endl;
          cin.get();
        } else {
          menuPrincipal(cliente);
          delete cliente;
        }
      } else {
        menuPrincipal(cliente);
        delete cliente;
      }
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
