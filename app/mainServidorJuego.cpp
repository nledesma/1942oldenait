#include <iostream>
#include "../src/net/servidor/servidor.hpp"
#include "../src/net/servidor/servidorParser.hpp"
#include "../src/logger/logger.hpp"
#include <stdio.h>
using namespace std;

#define DEFAULT_XML "../../resources/xml/nivelDefault.xml"

void* apagarServidor(void* servidor){

    char caracter;

    Servidor *servidor1 = (Servidor *) servidor;
    do{
        cout << "Presione 'S' para salir" << endl;
        cin >> caracter;
    } while((caracter != 's')&&(caracter != 'S'));

    if((caracter == 's')||(caracter == 'S')){
        servidor1->cerrar();
    }
    pthread_exit(NULL);
}

void ejecutar(Servidor* servidor){

    pthread_t apagar;
    pthread_create(&apagar, NULL, apagarServidor, servidor);
    // Servidor aceptando conexiones
    try{
        servidor->pasivar();
    }catch(runtime_error &e){
        Logger::instance()->logError(errno,"Se produjo un error en el listen");
    }
    servidor->esperarJugadores();

    // Se puede haber cerrado el servidor antes de recibir jugadores.
    if (servidor->servidorActivo()) {
        sleep(2);
        servidor->getEscenario()->mainLoop(servidor->servidorActivo());
        servidor->iniciarCicloDesencolaciones();
    }

    pthread_join(apagar, NULL);
    Logger::instance()->cerrar();
    Logger::resetInstance();
    pthread_exit(NULL);

}


bool archivoExiste (const string& archivo) {
    if (FILE *file = fopen(archivo.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[]){
    string rutaXMLServidor;
    bool defaultFallo = false;

    if (argc < 2) {
        string war = "No se especificó archivo de configuración. Se utilizará el XML por defecto.";
        cout << war << endl;
        Logger::instance()->logWarning(war);
        rutaXMLServidor = (DEFAULT_XML);
        defaultFallo = !archivoExiste(DEFAULT_XML);
    } else {
        if (archivoExiste(argv[1])) {
            rutaXMLServidor = argv[1];
        } else {
            cout << "El parámetro ingresado no es válido. Se inicializa el servidor con el XML por defecto" << endl;
            Logger::instance()->logWarning("El parámetro ingresado no es válido. Se inicializa el servidor con el XML por defecto.");
            rutaXMLServidor = (DEFAULT_XML);
            defaultFallo = !archivoExiste(DEFAULT_XML);
        }
    }

    if (defaultFallo) {
        stringstream ss;
        ss << "No se encontró el archivo de configuración por defecto. No es posible iniciar el servidor." << endl;
        ss << "Presione enter para salir.";
        cout << ss.str();
        Logger::instance()->logError(0, ss.str());
        cin.get();
        return 1;
    }

    Servidor* servidor;
    servidor = ServidorParser::deserializarEscenario(rutaXMLServidor);
    if (servidor != NULL){
        ejecutar(servidor);
        delete servidor;
        return 0;
    }
    Logger::instance()->logWarning("Hubo un error al inicializar el servidor desde el archivo XML");
    cout << "Hubo un error al iniciar el servidor. Presione cualquier tecla para finalizar el programa" << endl;
    cin.get();
    Logger::instance()->cerrar();

}
