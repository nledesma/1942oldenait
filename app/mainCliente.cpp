#include <iostream>
#include "../src/net/servidor/servidor.hpp"
#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"

bool validarInt(string valor) {
    if  (valor.empty() || ((!isdigit(valor[0])) && (valor[0] != '-') && (valor[0] != '+')))
        return false;
    char * p ;
    strtol(valor.c_str(), &p, 10) ;

    return (*p == 0) ;
}

int leerInt(){
    string lectura;
    stringstream ss;
    cin >> lectura;
    int n;
    while(!validarInt(lectura)) {
        cout << "No se ingresó un número." << endl;
        cin >> lectura;
    }
    ss << lectura;
    ss >> n;
    return n;
}

void separador(){
    cout << "-----------------------------------------------------" << endl;
}

void imprimirMenu(){
    separador();
    cout << "Bienvenido, Elija la opcion que desee:" << endl;
    cout << "1. Conectar" << endl;
    cout << "2. Desconectar" << endl;
    cout << "3. Salir" << endl;
    separador();
}

void conexionManual(Cliente* cliente){
    string ip;
    int puerto;
    string alias;

    if (cliente->conectado()){
        cout << "El cliente ya está conectado." << endl;
    } else {
        cout << "Ingrese IP: " << endl;
        cin >> ip;
        cout << "Ingrese un puerto: " << endl;
        cin >> puerto;
        cliente->setAddress(ip, puerto);
        cout << "Ingrese un alias: ";
        cin >> alias;
        cliente->setAlias(alias);
        cout << "Se ha ingresado el alias " << alias << endl;
        cliente->conectar();
    }
}


void menuConexiones(Cliente * cliente,list<Conexion>* conexionesGuardadas) {
    separador();
    cout << "Menu de conexiones: " << endl;
    separador();
    int n = conexionesGuardadas->size();
    // Se imprime el menu.
    list<Conexion>::iterator it;
    int i = 1;
    for(it = conexionesGuardadas->begin(); it != conexionesGuardadas->end(); it ++){
        cout << i << ": " << it->nombre << ". IP: " << it->ip << ". Puerto: " << it->puerto << endl;
        i++;
    }
    cout << n + 1 << ": Conexión Manual." << endl;
    cout << n + 2 << ": Cancelar." << endl;
    separador();

    // Se lee la opción.
    int opcion = -1;
    opcion = leerInt();
    separador();

    while (opcion < 1 || opcion > n + 2) {
        cout << "Opción no válida" << endl;
        opcion = leerInt();
        separador();
    }

    // Se conecta.
    if (opcion == n + 1){
        conexionManual(cliente);
    } else if (opcion != n + 2){

        it = conexionesGuardadas->begin();
        advance(it, opcion - 1);
        cout << "ingrese un alias" << endl;
        string alias;
        cin >> alias;
        cliente->setAlias(alias);
        cliente->setAddress(it->ip,it->puerto);
        cliente->conectar();
    }
}


using namespace std;
void menuPrincipal(Cliente * cliente, list<Conexion>* conexionesGuardadas) {
    int opcion = -1;
    while (opcion != 3){
        imprimirMenu();
        opcion = leerInt();
        separador();
        cout << "Opción elegida: " << opcion << endl;
        switch (opcion) {
            case 1:
                menuConexiones(cliente, conexionesGuardadas);
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
            default:
                cout << "Opcion invalida. Seleccione una opción válida y pulse ENTER para continuar." << endl;
                break;
        }
    }
}

int main(){
    // TODO Habria que hacer otro constructor que no reciba estos parametros.
    Cliente* cliente = new Cliente("127.0.0.1", 8000);
    // Levanto las conexiones del archivo de conexiones guardadas.
    list<Conexion> c = ClienteParser::levantarConexiones();
    menuPrincipal(cliente, &c);
    return 0;
}
