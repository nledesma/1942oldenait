#include <iostream>
#include <cstdlib>
#include "../src/net/servidor/servidor.hpp"
#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"
#include "../src/menu/Menu/menuPrincipal.hpp"
#include "../src/menu/Menu/menuDatosDeUsuario.hpp"
#include "../src/menu/Menu/menuConexionPuerto.hpp"
#include "../src/menu/Menu/menuConexionManual.hpp"
#include "../src/menu/Menu/menuConexiones.hpp"
#include "../src/menu/Menu/menuPorEquipos.hpp"
#include "../src/juego/vista/textoDinamico.hpp"
#include "../src/menu/listaDeSeleccion.hpp"
using namespace std;

void cargarMenuPrincipal(Cliente * cliente, Ventana* ventana);
void cargarMenuDatosDeUsuario(Ventana* ventana, MenuDatosDeUsuario* menuDatosDeUsuario, Cliente* cliente);
void cargarMenuConexiones(Cliente * cliente, Ventana* ventana, MenuConexiones* menuConexiones, MenuDatosDeUsuario* menuDatosDeUsuario);
void cargarMenuConexionManual(Cliente* cliente, Ventana* ventana, MenuConexiones* menuConexiones, MenuDatosDeUsuario* menuDatosDeUsuario);

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

void cargarMenuPuerto(string ip, Cliente* cliente, Ventana* ventana, MenuConexionManual* menu){
    MenuConexionPuerto* menuConexionPuerto = new MenuConexionPuerto();
    SDL_Color color = {255, 232, 32};
    TextoDinamico* textoDinamicoPuerto = new TextoDinamico(25, color,  STAR_WARS_FONT, ventana);
    textoDinamicoPuerto->cambiarTexto("");
    menuConexionPuerto->cargarBotones(ventana);
    bool quit = false;
	SDL_Event e;
	while(!quit){
		while(SDL_PollEvent( &e ) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta = menuConexionPuerto->getBotonSiguiente()[0].manejarEvento(&e);
			if(respuesta == 1 || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN)){
				menu->cerrar();

                const char* puertoChar = textoDinamicoPuerto->getTexto().c_str();
                int puerto = atoi (puertoChar);
                cliente->setAddress(ip, puerto);
                cliente->conectar();
                quit = true;
			}
			ventana->limpiar();
			//Renderizado
            textoDinamicoPuerto->manejarEvento(e);

		}
		ventana->limpiar();
		//Renderizado
		menuConexionPuerto->renderizar(ventana);
        textoDinamicoPuerto->renderizar(300, 250);
		SDL_RenderPresent(ventana->getVentanaRenderer());
	}
    menuConexionPuerto->cerrar();

}

void cargarMenuConexionManual(Cliente* cliente, Ventana* ventana, MenuConexiones* menuConexiones, MenuDatosDeUsuario* menuDatosDeUsuario){
    MenuConexionManual* menuConexionManual = new MenuConexionManual();
    TextoDinamico* textoDinamicoIP = new TextoDinamico(25, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    textoDinamicoIP->cambiarTexto("");
    menuConexionManual->cargarBotones(ventana);
    bool quit = false;
	SDL_Event e;
	while(!quit){
		while(SDL_PollEvent( &e ) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta = menuConexionManual->getBotonSiguiente()[0].manejarEvento(&e);
			if(respuesta == 1 || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN)){
				menuConexiones->cerrar();
                cargarMenuPuerto(textoDinamicoIP->getTexto(), cliente, ventana, menuConexionManual);
			}
            int respuestaAtras = menuConexionManual->getBotonAtras()[0].manejarEvento(&e);
            if(respuestaAtras == 1){
                menuConexiones->cerrar();
                menuConexiones = new MenuConexiones(ventana);
                cargarMenuConexiones(cliente, ventana, menuConexiones, menuDatosDeUsuario);
            }
			ventana->limpiar();
			//Renderizado
            textoDinamicoIP->manejarEvento(e);

		}
		ventana->limpiar();
		//Renderizado
		menuConexionManual->renderizar(ventana);
        textoDinamicoIP->renderizar(300, 250);
		SDL_RenderPresent(ventana->getVentanaRenderer());
	}
    menuConexionManual->cerrar();

}

//TODO
void agregarJugador(MenuPorEquipos* menuPorEquipos, Cliente* cliente){
    int equipoElegido = menuPorEquipos->getListaDeSeleccion()->getNroBotonSeleccionado();
    cout << "EQUIPO ELEGIDO: " << equipoElegido << endl;
    // No es un evento, pero es un entero y fiaca.
    cliente->enviarEvento(equipoElegido);
}

// TODO test.
void cargarMenuPorEquipos(Cliente* cliente, Ventana* ventana){
    MenuPorEquipos* menuPorEquipos = new MenuPorEquipos(ventana);

    menuPorEquipos->getListaDeSeleccion()->agregarOpcion("Equipo 1");
    menuPorEquipos->getListaDeSeleccion()->agregarOpcion("Equipo 2");

    menuPorEquipos->cargarBotones(ventana);
    bool quit = false;
    SDL_Event e;
    int x, y; // Para los clicks.

    while(!quit){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT) {
				quit = true;
			} else if(e.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState( &x, &y );
                menuPorEquipos->getListaDeSeleccion()->clickEn(x, y);
                int respuesta = menuPorEquipos->getBotonSiguiente()[0].manejarEvento(&e);
                if (respuesta == 1) {
                    agregarJugador(menuPorEquipos, cliente);
                    quit = true;
                    // levantarConexion(numeroSeleccionado, cliente, &conexionesGuardadas, ventana, menuConexiones);
                }
            } else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN) {
                // TODO Refactorizar.
                agregarJugador(menuPorEquipos, cliente);
                quit = true;
                //levantarConexion(numeroSeleccionado, cliente, &conexionesGuardadas, ventana, menuConexiones);
            }
		}
        ventana->limpiar();
        menuPorEquipos->renderizar(ventana);
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
    menuPorEquipos->cerrar();
}

void levantarConexion(int numeroSeleccionado, Cliente * cliente,list<Conexion>* conexionesGuardadas, Ventana* ventana, MenuConexiones* menuConexiones, MenuDatosDeUsuario* menuDatosDeUsuario){
    list<Conexion>::iterator it;
    int opcion = numeroSeleccionado;
    if (opcion == 6) {
        cargarMenuConexionManual(cliente, ventana, menuConexiones, menuDatosDeUsuario);
    } else {
        it = conexionesGuardadas->begin();
        advance(it, opcion);
        cliente->setAddress(it->ip, it->puerto);
        if (cliente->conectar()) {
            // Si nos pudimos conectar, le preguntamos al servidor si la partida está en curso y si es por equipos.
            string respuesta;
            cliente->recibirMensaje(respuesta);
            bool enCurso = Decodificador::popBool(respuesta);
            bool porEquipos = Decodificador::popBool(respuesta);
            if (!enCurso && porEquipos) {
                cargarMenuPorEquipos(cliente, ventana);
            }
            // Después de la elección de  equipo, si la hubo, se procede con el juego.
            cliente->ejecutar();
        }
    }
}

void cargarMenuConexiones(Cliente * cliente, Ventana* ventana, MenuConexiones* menuConexiones, MenuDatosDeUsuario* menuDatosDeUsuario) {
    list<Conexion> conexionesGuardadas = ClienteParser::levantarConexiones();
    list<Conexion>::iterator it;
    for(it = conexionesGuardadas.begin(); it != conexionesGuardadas.end(); it ++){
        string conexion = it->nombre + ". IP: " + it->ip + ". Puerto: " + to_string(it->puerto);
        menuConexiones->getListaDeSeleccion()->agregarOpcion(conexion);
    }
    menuConexiones->getListaDeSeleccion()->agregarOpcion("CONEXION MANUAL");
    menuConexiones->cargarBotones(ventana);
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
                int respuesta = menuConexiones->getBotonSiguiente()[0].manejarEvento(&e);
                if (respuesta == 1) {
                    int numeroSeleccionado = menuConexiones->getListaDeSeleccion()->getNroBotonSeleccionado();
                    levantarConexion(numeroSeleccionado, cliente, &conexionesGuardadas, ventana, menuConexiones, menuDatosDeUsuario);
                }
                int respuestaAtras = menuConexiones->getBotonAtras()[0].manejarEvento(&e);
                if(respuestaAtras == 1){
                    menuConexiones->cerrar();
                    cargarMenuDatosDeUsuario(ventana, menuDatosDeUsuario, cliente);
                    quit = true;
                }
            } else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN) {
                // TODO Refactorizar.
                int numeroSeleccionado = menuConexiones->getListaDeSeleccion()->getNroBotonSeleccionado();
                levantarConexion(numeroSeleccionado, cliente, &conexionesGuardadas, ventana, menuConexiones, menuDatosDeUsuario);
            }
		}
        ventana->limpiar();
        menuConexiones->renderizar(ventana);
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
    menuConexiones->cerrar();
}

void cargarMenuDatosDeUsuario(Ventana* ventana, MenuDatosDeUsuario* menuDatosDeUsuario, Cliente* cliente){
	MenuConexiones* menuConexiones = new MenuConexiones(ventana);
    TextoDinamico* textoDinamico = new TextoDinamico(25, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    textoDinamico->cambiarTexto("");
    menuDatosDeUsuario->cargarBotones(ventana);
	bool quit = false;
	SDL_Event e;
    SDL_StartTextInput();
	while(!quit){
		while(SDL_PollEvent( &e ) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta = menuDatosDeUsuario->getBotonSiguiente()[0].manejarEvento(&e);
			if(respuesta == 1 ||  (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN)){
				menuDatosDeUsuario->cerrar();
				cargarMenuConexiones(cliente, ventana, menuConexiones, menuDatosDeUsuario);
                quit = true;
			}
            int respuestaAtras = menuDatosDeUsuario->getBotonAtras()[0].manejarEvento(&e);
            if(respuestaAtras == 1){
                quit = true;
                menuDatosDeUsuario->cerrar();
                cargarMenuPrincipal(cliente, ventana);
            }

			ventana->limpiar();
			//Renderizado
            textoDinamico->manejarEvento(e);
            cliente->setAlias(textoDinamico->getTexto());

		}
		ventana->limpiar();
		//Renderizado
		menuDatosDeUsuario->renderizar(ventana);
        textoDinamico->renderCentrado(350);
		SDL_RenderPresent(ventana->getVentanaRenderer());
	}
    SDL_StopTextInput();
}

void cargarMenuPrincipal(Cliente * cliente, Ventana* ventana) {
	MenuPrincipal* menuPrincipal = new MenuPrincipal();
	MenuDatosDeUsuario* menuDatosDeUsuario = new MenuDatosDeUsuario();

	menuPrincipal->cargarBotones(ventana);
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT) {
				quit = true;
			}
			int respuesta = menuPrincipal->getBotonJugar()[0].manejarEvento(&e);
			if(respuesta == 1 || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN)) {
				menuPrincipal->cerrar();
				//Arranca el menu de datos del usuario.
				menuDatosDeUsuario->cargarBotones(ventana);
				cargarMenuDatosDeUsuario(ventana, menuDatosDeUsuario, cliente);
                quit = true;
                menuDatosDeUsuario->cerrar();
                menuPrincipal->cerrar();
			}
			int respuestaSalir = menuPrincipal->getBotonSalir()[0].manejarEvento(&e);
			if(respuestaSalir == 1) {
				menuPrincipal->cerrar();
				ventana->cerrar();
                quit = true;
			}
			ventana->limpiar();
			//Renderizado
			menuPrincipal->renderizar(ventana);
			SDL_RenderPresent(ventana->getVentanaRenderer());
		}
	}
    ventana->cerrar();
}

int main(){

    Ventana* ventana = new Ventana(800, 800);
    ventana->iniciar();
    Cliente cliente(ventana);
    cargarMenuPrincipal(&cliente, ventana);
    return 0;
}
