#include <iostream>
#include "../src/net/servidor/servidor.hpp"
#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"
#include "../src/menu/Menu/menuPrincipal.hpp"
#include "../src/menu/Menu/menuDatosDeUsuario.hpp"
#include "../src/menu/Menu/menuModosDeJuego.hpp"
#include "../src/juego/vista/textoDinamico.hpp"
using namespace std;

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
    cout << "Menu de conexiones: " << endl;
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
void cargarMenuModosDeJuego(Ventana* ventana, MenuModosDeJuego* menuModosDeJuego, Cliente* cliente){
	bool quit = false;
	SDL_Event e;
	while( !quit ){
		while( SDL_PollEvent( &e ) != 0 ){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta = menuModosDeJuego->getBotonEnColaboracion()[0].handleEvent(&e);
            if(respuesta == 1){
                cout << "Esta por conectar" << endl;
                cliente->conectar();
            }
			menuModosDeJuego->getBotonPorEquipos()[0].handleEvent(&e);
			menuModosDeJuego->getBotonModoPractica()[0].handleEvent(&e);

		}
		ventana->limpiar();
		//Renderizar
		menuModosDeJuego->renderizar(ventana);
		SDL_RenderPresent(ventana->getVentanaRenderer());
	}
	menuModosDeJuego->cerrar();
}

void cargarMenuDatosDeUsuario(Ventana* ventana, MenuDatosDeUsuario* menuDatosDeUsuario, Cliente* cliente){
	MenuModosDeJuego* menuModosDeJuego = new MenuModosDeJuego();
    SDL_Color colorNegro = { 0, 0, 0 };
    TextoDinamico* textoDinamico = new TextoDinamico(25, colorNegro, ventana);
    textoDinamico->cambiarTexto("");
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while(SDL_PollEvent( &e ) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta2 = menuDatosDeUsuario->getBotonSiguiente()[0].handleEvent(&e);
			if(respuesta2 == 1){
				cout << "ABRIR MENU MODOS DE JUEGO" << endl;
				menuDatosDeUsuario->cerrar();
				menuModosDeJuego->cargarBotones(ventana);
				cargarMenuModosDeJuego(ventana, menuModosDeJuego, cliente);
			}
			ventana->limpiar();
			//Renderizado
            textoDinamico->manejarEvento(e);
            cliente->setAlias(textoDinamico->getTexto());

		}
		ventana->limpiar();
		//Renderizado
		menuDatosDeUsuario->renderizar(ventana);
        textoDinamico->renderizar(300, 350);
		SDL_RenderPresent(ventana->getVentanaRenderer());
	}
}

void menuPrincipal(Cliente * cliente, Ventana* ventana) {
	MenuPrincipal* menuPrincipal = new MenuPrincipal();
	MenuDatosDeUsuario* menuDatosDeUsuario = new MenuDatosDeUsuario();

	menuPrincipal->cargarBotones(ventana);
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta = menuPrincipal->getBotonJugar()[0].handleEvent(&e);
			if(respuesta == 1){
				menuPrincipal->cerrar();
				//Arranca el menu de datos del usuario.
				menuDatosDeUsuario->cargarBotones(ventana);
				cargarMenuDatosDeUsuario(ventana, menuDatosDeUsuario, cliente);
			}
			int respuestaSalir = menuPrincipal->getBotonSalir()[0].handleEvent(&e);
			if(respuestaSalir == 1){
				menuPrincipal->cerrar();
				ventana->cerrar();
			}
			ventana->limpiar();
			//Renderizado
			menuPrincipal->renderizar(ventana);
			SDL_RenderPresent(ventana->getVentanaRenderer());
		}
	}
	menuDatosDeUsuario->cerrar();

    //Free y cerrado de SDL
    menuPrincipal->cerrar();
    ventana->cerrar();
}
    //TODO
    // int opcion = -1;
    // while (opcion != 3){
    //     imprimirMenu();
    //     opcion = leerInt();
    //     separador();
    //     cout << "Opción elegida: " << opcion << endl;
    //     switch (opcion) {
    //         case 1:
    //             menuConexiones(cliente, conexionesGuardadas);
    //             break;
    //         case 2:
    //             if (cliente->conectado()){
    //                 cliente->cerrar();
    //             } else {
    //                 cout << "El cliente no está conectado." << endl;
    //             }
    //             break;
    //         case 3:
    //             break;
    //         default:
    //             cout << "Opcion invalida. Seleccione una opción válida y pulse ENTER para continuar." << endl;
    //             break;
    //     }
    // }
//}

int main(){
    Ventana* ventana = new Ventana(800, 800);
    ventana->iniciar();
    Cliente* cliente = new Cliente("127.0.0.1", 8000, ventana);
    menuPrincipal(cliente, ventana);
    return 0;
}
