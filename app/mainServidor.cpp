#include "../src/net/servidor/servidorParser.hpp"
#include <string>
#include <pthread.h>

#define DEFAULT_XML "../../resources/xml/servidorDefault.xml"

using namespace std;

void* apagarServidor(void* servidor){

    char caracter;

    Servidor *servidor1 = (Servidor *) servidor;
    cout << "Presione 'S' para salir" << endl;
    cin >> caracter;

    if((caracter == 's')||(caracter == 'S')){
        servidor1->cerrar();
    }
    pthread_exit(NULL);
}

void ejecutar(Servidor* servidor){
    pthread_t apagar;

    //void* unServidor = (void*) servidor;
    pthread_create(&apagar,NULL,apagarServidor,servidor);
    // Servidor aceptando conexiones
    try{
        servidor->pasivar();
    }catch(runtime_error &e){
        Logger::instance()->logError(errno,"Se produjo un error en el listen");
    }
    //servidor->esperar();
    //servidor->cerrar();
    pthread_join(apagar, NULL);
    Logger::instance()->cerrar();
    //Logger::resetInstance();
    pthread_exit(NULL);
}    

int main(int argc, char *argv[]){
    string rutaXMLServidor;

    if (argc < 2){
        cout << "Argumentos insuficientes, se utilizará el XML por defecto" << endl;
        Logger::instance()->logWarning("No se ingresó la cantidad de parámetros suficientes. Se inicializa el servidor con el XML por defecto.");
        rutaXMLServidor = (DEFAULT_XML);
    } else {
        rutaXMLServidor = argv[1];
    }
    /* Se crea el servidor. */
    Servidor * servidor;
    ServidorParser servidorParser;
    servidor = servidorParser.deserializar(rutaXMLServidor);

    if (servidor != NULL){
        ejecutar(servidor);
        delete servidor;
        return 0;
    }
    
    Logger::instance()->logWarning("Error cargando el archivo provisto. Se procederá con la configuración por defecto.");
    cout << "Error cargando el archivo provisto. Se procederá con la configuración por defecto." << endl;
    servidor = servidorParser.deserializar(DEFAULT_XML);

    if (servidor != NULL){
        ejecutar(servidor);
        delete servidor;
        return 0;
    }

    Logger::instance()->logWarning("Hubo un error al inicializar el servidor desde el archivo XML por default");
    cout << "Hubo un error al iniciar el servidor. Presione cualquier tecla para finalizar el programa" << endl;
    cin.get();
    
    return 0;
}


