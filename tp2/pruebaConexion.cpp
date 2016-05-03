#include <iostream>
#include "servidor.hpp"
#include "cliente.hpp"

using namespace std;
void menuPrincipal(Cliente * cliente) {
    char opcion = '-';
    string aliasUsuario;
    while (opcion != '3'){
        cout << "-----------------------------------------------------" << endl;
        cout << "Bienvenido, Elija la opcion que desee:" << endl;
        cout << "1. Conectar" << endl;
        cout << "2. Desconectar" << endl;
        cout << "3. Salir" << endl;
        cout << "-----------------------------------------------------" << endl;
        cin >> opcion;
        cout << "-----------------------------------------------------" << endl;
        cout << "Opción elegida: " << opcion << endl;
        switch (opcion) {
            case '1':
                if (cliente->conectado()){
                    cout << "El cliente ya está conectado." << endl;
                } else {
                    cliente->conectar();
                    if(cliente->conectado()){
                        cout << "Ingrese un alias: ";
                        cin >> aliasUsuario;
                        cout << "Se ha ingresado el alias " << aliasUsuario << endl;
                    }
                }
                break;
            case '2':
                if (cliente->conectado()){
                    cliente->cerrar();
                } else {
                    cout << "El cliente no está conectado." << endl;
                }
                break;
            case '3':
                break;
            default:
                cout<< "Opcion invalida. Seleccione una opción válida y pulse ENTER para continuar." << endl;
                break;
        }
    }
}
int main(){
  Cliente* cliente = new Cliente("127.0.0.1", 8080);
  menuPrincipal(cliente);
  return 0;
}
