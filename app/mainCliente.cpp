#include <iostream>
#include "../src/net/servidor/servidor.hpp"
#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"

//Probando
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
    int n;

    cin >> lectura;
    while(!validarInt(lectura)) {
        cout << "El valor ingresado debe ser un número." << endl;
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

int validarPuerto(){
	int puerto;
	puerto = leerInt();
	while ((puerto <= 1024) || (puerto >= 65535)){
		cout << "Ingrese un número de puerto entre 1024 y 65535." << endl;
		puerto = leerInt();
	}
	return puerto;
}

bool esIpValida(string ip){
	unsigned int i = 0;
	const char* ipAux = ip.c_str();
	int cantidadPuntos = 0;
	while(i < ip.length()){
		if(ipAux[i] == '.'){
			cantidadPuntos++;
		}
		i++;
	}
	if((cantidadPuntos == 3)&&(ip.length()>=7)){
		return true;
	}
	return false;
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
        while (!(esIpValida(ip))){
        	cout << "La dirección IP ingresada no tiene un formato válido" << endl;
        	cin >> ip;
        }

        cout << "Ingrese un puerto: " << endl;
       	puerto = validarPuerto();

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
        cout << "Ingrese un alias" << endl;
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
    Cliente cliente;
    // Levanto las conexiones del archivo de conexiones guardadas.
    list<Conexion> c = ClienteParser::levantarConexiones();
    menuPrincipal(&cliente, &c);
    return 0;
}
