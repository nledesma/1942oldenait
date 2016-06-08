#include <iostream>
#include "../src/net/servidor/servidor.hpp"
#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"
#include "../src/menu/Menu/menuPrincipal.hpp"
#include "../src/menu/Menu/menuDatosDeUsuario.hpp"
#include "../src/menu/Menu/menuModosDeJuego.hpp"
#include "../src/menu/Menu/menuConexiones.hpp"
#include "../src/juego/vista/textoDinamico.hpp"
#include "../src/menu/listaDeSeleccion.hpp"
using namespace std;

//TODO faltaria poner los botones con los otros modos de juego.

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

void levantarConexion(int numeroSeleccionado, Cliente * cliente,list<Conexion>* conexionesGuardadas){
    list<Conexion>::iterator it;
    int opcion = numeroSeleccionado;
    it = conexionesGuardadas->begin();
    advance(it, opcion);
    cliente->setAddress(it->ip,it->puerto);
    cliente->conectar();
}

void cargarMenuConexiones(Cliente * cliente, Ventana* ventana, MenuConexiones* menuConexiones) {
    list<Conexion> conexionesGuardadas = ClienteParser::levantarConexiones();
    list<Conexion>::iterator it;
    for(it = conexionesGuardadas.begin(); it != conexionesGuardadas.end(); it ++){
        string conexion = it->nombre + ". IP: " + it->ip + ". Puerto: " + to_string(it->puerto);
        menuConexiones->getListaDeSeleccion()->agregarOpcion(conexion);
    }
    bool quit = false;
    SDL_Event e;
    int x, y; // Para los clicks.

    while(!quit){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT) {
				quit = true;
			} else if(e.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState( &x, &y );
                menuConexiones->getListaDeSeleccion()->clickEn(x, y);
                int respuesta = menuConexiones->getBotonSiguiente()[0].handleEvent(&e);
                if(respuesta == 1){
                    int numeroSeleccionado = menuConexiones->getListaDeSeleccion()->getNroBotonSeleccionado();
                    levantarConexion(numeroSeleccionado, cliente, &conexionesGuardadas);
                }
            }
		}
        ventana->limpiar();
        menuConexiones->renderizar(ventana);
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
    menuConexiones->cerrar();
}

void cargarMenuModosDeJuego(Ventana* ventana, MenuModosDeJuego* menuModosDeJuego, Cliente* cliente){
    MenuConexiones* menuConexiones = new MenuConexiones(ventana);
	bool quit = false;
	SDL_Event e;
	while( !quit ){
		while( SDL_PollEvent( &e ) != 0 ){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta = menuModosDeJuego->getBotonEnColaboracion()[0].handleEvent(&e);
            if(respuesta == 1){
                menuModosDeJuego->cerrar();
                menuConexiones->cargarBotones(ventana);
                cargarMenuConexiones(cliente, ventana, menuConexiones);
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
    SDL_Color color = {255, 232, 32};
    TextoDinamico* textoDinamico = new TextoDinamico(25, color, ventana);
    textoDinamico->cambiarTexto("");
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while(SDL_PollEvent( &e ) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta = menuDatosDeUsuario->getBotonSiguiente()[0].handleEvent(&e);
			if(respuesta == 1){
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

int main(){

    Ventana* ventana = new Ventana(800, 800);
    ventana->iniciar();
    Cliente cliente(ventana);
    menuPrincipal(&cliente, ventana);
    return 0;
}