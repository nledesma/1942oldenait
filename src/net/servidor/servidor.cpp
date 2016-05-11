#include "servidor.hpp"

using namespace std;

Servidor::Servidor(int port, int cantidadDeClientes) : GameSocket() {
    try {
        iniciarSocket();
        inicializar(port);
    } catch (runtime_error &e) {
        Logger::instance()->logError(errno, "Se produjo un error en el BIND");
    }
    // ?
    setCantidadMaximaDeClientes(cantidadDeClientes);
    // desactivarServidor();
}

void Servidor::setCantidadMaximaDeClientes(int unaCantidadDeClientes) {
    cantidadMaximaDeClientes = unaCantidadDeClientes;
}

int Servidor::getCantidadMaximaDeClientes() {
    return cantidadMaximaDeClientes;
}

void Servidor::inicializar(int port) {
    setPuerto(port);
    this->setAddress(port); // Se setea el puerto en addr_info
    // Se vincula el socket al puerto indicado en addr_info
    if (bind(this->socketFd, (struct sockaddr *) &this->addr_info, sizeof(struct sockaddr_in)) == -1) {
        throw runtime_error("BIND_EXCEPTION");
    }
}

void Servidor::esperarJugadores(){
    pthread_mutex_lock(&this->mutexPartidaLlena);
    while (this->hayLugar()) {
        pthread_cond_wait(&this->condPartidaLlena, &this->mutexPartidaLlena);
    }
    pthread_mutex_unlock(&this->mutexPartidaLlena);
    cout << "Comenzando partida!" << endl;
}

void Servidor::setAddress(int port) {
    this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
    this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
    this->addr_info.sin_addr.s_addr = INADDR_ANY; // El socket se puede asociar a cualquier conexión
    memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

void Servidor::pasivar() {

    int resultadoListen = listen(this->socketFd, this->cantidadMaximaDeClientes);
    cout << "Esperando conexión ... " << endl;
    if (resultadoListen == -1) {
        throw runtime_error("LISTEN_EXCEPTION");
    }
    servidorActivado = true;
    pthread_create(&this->cicloAceptaciones, NULL, cicloAceptar, (void *) this);
}

void Servidor::iniciarCicloDesencolaciones(){
    pthread_create(&this->cicloDesencolaciones, NULL, cicloDesencolar, (void *) this );
}

void *Servidor::cicloAceptar(void *THIS) {
    Servidor *servidor = (Servidor *) THIS;
    int fdCliente;
    while (servidor->servidorActivo()) {
        try {
            fdCliente = servidor->aceptar();
            // Si hay lugar se lo agrega. Sino, se le avisa que no hay lugar.
            if (servidor->hayLugar()){
                // Se avisa que hay lugar para conectarse.
                servidor->enviarMensaje("OK", fdCliente);
                servidor->agregarCliente(fdCliente);
            } else {
                servidor->enviarMensaje("NO", fdCliente);
            }
        } catch (runtime_error &e) {
            if(servidor->servidorActivo()) {
                Logger::instance()->logError(errno, "Se produjo un error en el ACCEPT");
            }
        }
    }
    pthread_exit(NULL);
}

void Servidor::enviarEstadoInicial(int fdCliente) {
    cout << "enviando estado inicial" << endl;
    enviarMensaje(Decodificador::getCodigoEstadoInicial(escenario), fdCliente);
}

void *Servidor::atenderCliente(void *arg) {
    cout << "Atendiendo a un cliente." << endl;
    pair<Servidor *, int> *parServidorCliente = (pair<Servidor *, int> *) arg;
    Servidor *servidor = parServidorCliente->first;
    int fdCliente = parServidorCliente->second;
    pair<int, string> clienteMensaje;
    clienteMensaje.first = fdCliente;

    // Antes de atenderlo se espera a que se conecten todos.
    servidor->esperarPartida(fdCliente);
    servidor->enviarEstadoInicial(fdCliente);
    servidor->signalComienzaPartida();

    int recieveResult = ESTADO_INICIAL;
    // Validar que esté conectado?
    while (recieveResult != PEER_DESCONECTADO && recieveResult != PEER_ERROR && servidor->clienteConectado(fdCliente)) {
        string mensajeCliente;
        recieveResult = servidor->recibirMensaje(mensajeCliente, fdCliente);

        if(recieveResult != MENSAJEOK) {
            cout << "Se ha desconectado un cliente" << endl; // TODO loguear
        } else {
            clienteMensaje.second = mensajeCliente;
            servidor->encolarMensaje(clienteMensaje);
        }
    }

    servidor->quitarCliente(fdCliente);
    pthread_exit(NULL);
}

void Servidor::signalComienzaPartida(){
    pthread_mutex_lock(&this->mutexPartidaLlena);
    pthread_cond_signal(&this->condPartidaLlena);
    pthread_mutex_unlock(&this->mutexPartidaLlena);
}

// Ciclo que desencola la salida para cada cliente.
void * Servidor::responderCliente(void* arg){
    pair <Servidor *, int> *servidorPar = (pair <Servidor *, int>*) arg;
    Servidor * servidor = servidorPar->first;
    int clienteFd = servidorPar->second;

    while (servidor->servidorActivo() && servidor->clienteConectado(clienteFd)){
        servidor->desencolarSalidaCliente(clienteFd);
    }
    pthread_exit(NULL);
}

bool Servidor::clienteConectado(int clienteFd){
    return clientes[clienteFd].conectado;
}

void Servidor::desencolarSalidaCliente(int clienteFd){
    ColaConcurrente<string> *colaSalida = &(clientes[clienteFd].colaSalida);
    if(!colaSalida->vacia()){
        if (!servidorActivado || !clienteConectado(clienteFd)) return;
        string mensaje = colaSalida->pop();
        this->enviarMensaje(mensaje, clienteFd);
    }
}

int Servidor::aceptar() {
    int resulAccept = accept(socketFd, 0, 0);
    // Timeout de minuto y medio para recibir mensajes del cliente.
    struct timeval tv;
    tv.tv_sec = 90;
    tv.tv_usec = 0;
    setsockopt(resulAccept, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));

    if(this->servidorActivado) {
        Logger::instance()->logInfo("La conexión ha sido aceptada");
    }

    if (resulAccept == -1) {
        throw runtime_error("ACCEPT_EXCEPTION");
    }

    return resulAccept;
}

map<int, datosCliente>& Servidor::getClientes(){
    return clientes;
}

void Servidor::cerrar() {
    this->desactivarServidor();

    for (map<int, datosCliente>::iterator iterador = getClientes().begin(); iterador != getClientes().end(); iterador++) {
        int clienteActual = iterador->first;
        shutdown(clienteActual, 0);
        close(clienteActual);
        iterador->second.colaSalida.avisar();
    }

    cerrarSocket();

    // Cerramos las colas.
    colaDeMensajes.avisar();

    cout << "Servidor cerrado" << endl;
    Logger::instance()->logInfo("El servidor ha sido cerrado");
}

void Servidor::setPuerto(int unPuerto) {
    puerto = unPuerto;
}

int Servidor::getPuerto() {
    return puerto;
}

void Servidor::esperar() {
    sleep(10);
    for (map<int, datosCliente>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++) {
        pthread_join(iterador->second.th_entrada, NULL);
        pthread_join(iterador->second.th_salida, NULL);
    }
}

bool Servidor::servidorActivo() {
    return this->servidorActivado;
}

void Servidor::desactivarServidor() {
  pthread_mutex_lock(&mutexActivarServidor);
  servidorActivado = false;
  pthread_mutex_unlock(&mutexActivarServidor);

}

void Servidor::encolarMensaje(pair<int, string> clienteMensaje) {
    this->colaDeMensajes.push(clienteMensaje);
}

// Envía al cliente la cantidad de jugadores faltantes para empezar periódicamente.
void Servidor::esperarPartida(int fdCliente) {
    cout << "esperando partida" << endl;
    int clientesActuales;
    while(hayLugar()){
        string mensaje = "";

        // Nos fijamos cuántos clientes hay conectados.
        pthread_mutex_lock(&mutexAgregar);
        clientesActuales = clientes.size();
        pthread_mutex_unlock(&mutexAgregar);

        Decodificador::pushCantidad(mensaje, cantidadMaximaDeClientes - clientesActuales);

        // Enviamos la cantidad de clientes faltantes.
        enviarMensaje(mensaje, fdCliente);
        // Espera un segundo antes de mandar de nuevo.
        sleep(1);
    }
    // Cuando ya no hay lugar, se termina la función.
}

void Servidor::agregarCliente(int fdCliente) {
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    getpeername(fdCliente, (sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
    int port = ntohs(client_addr.sin_port);
    char *clientAddress = inet_ntoa(client_addr.sin_addr);

    stringstream direccionCliente;
    direccionCliente << clientAddress << ":" << port;

    datosCliente datos;
    datos.conectado = true;
    datos.nroJugador = (int) clientes.size() + 1;
    datos.nombreJugador = "unNombre";

    cout << "Conectado a un cliente en la dirección " + direccionCliente.str() << endl;
    Logger::instance()->logInfo("Conectado a un cliente en la dirección " + direccionCliente.str());
    direcciones.insert(pair<int, string>(fdCliente, direccionCliente.str()));

    pthread_mutex_lock(&mutexAgregar);
    clientes.insert(pair<int, datosCliente>(fdCliente, datos));
    pthread_mutex_unlock(&mutexAgregar);

    pair<Servidor *, int> arg(this, fdCliente);

    // Recibo su nombre.
    string nombre;
    recibirMensaje(nombre, fdCliente);
    clientes[fdCliente].nombreJugador = nombre;

    pthread_create(&(clientes[fdCliente].th_entrada), NULL, atenderCliente, &arg);
    pthread_create(&(clientes[fdCliente].th_salida), NULL, responderCliente, &arg);
}

void Servidor::quitarCliente(int clienteFd) {
    clientes[clienteFd].conectado = false;
    clientes[clienteFd].colaSalida.avisar();
    string msj = "Cliente en la dirección " + direcciones[clienteFd] + " desconectado.";
    cout << msj << endl;
    Logger::instance()->logInfo(msj);
    pthread_join(clientes[clienteFd].th_salida, NULL);
    pthread_join(clientes[clienteFd].th_entrada, NULL);
    this->clientes.erase(clienteFd);
}

void *Servidor::cicloDesencolar(void *THIS) {
    Servidor *servidor = (Servidor *) THIS;
    while (servidor->servidorActivo()) {
        servidor->desencolar();
        usleep(5000);
    }
    pthread_exit(NULL);
}

void Servidor::encolarSalida(int clienteFd, string mensaje){
    clientes[clienteFd].colaSalida.push(mensaje);
}

void Servidor::desencolar() {
    if (! colaDeMensajes.vacia()){
        pair<int, string> clienteMensaje = colaDeMensajes.pop();
        if (!servidorActivado) return;
        int intEvento = Decodificador::popInt(clienteMensaje.second);
        int intJugador = clientes[clienteMensaje.first].nroJugador;
        pair <int, int> evento(intJugador, intEvento);
        this->escenario->pushEvento(evento);
    }
    string codigoEstadoActual = Decodificador::getCodigoEstadoActual(this->escenario);
    this->broadcastEstadoEscenario(codigoEstadoActual);
}

void Servidor::broadcastEstadoEscenario(string codigoEstadoEscenario) {
    for (map<int, datosCliente>::iterator iterador = getClientes().begin(); iterador != getClientes().end(); iterador++) {
        int clienteActual = iterador->first;
        encolarSalida(clienteActual, codigoEstadoEscenario);
    }
}

bool Servidor::validarChar(string valor) {
    return (valor.length() == 1);
}

bool Servidor::validarInt(string valor) {
    if  (valor.empty() || ((!isdigit(valor[0])) && (valor[0] != '-') && (valor[0] != '+')))
        return false;
    char * p ;
    strtol(valor.c_str(), &p, 10) ;

    return (*p == 0) ;
}

bool Servidor::validarDouble(string valor) {
    if  (valor.empty() || ((!isdigit(valor[0])) && (valor[0] != '-') && (valor[0] != '+')))
        return false;
    char * p ;
    strtod(valor.c_str(), &p) ;

    return (*p == 0) ;
}

bool Servidor::validarTipo(int tipo, string valor) {

    bool esValido;
    switch (tipo) {
        case T_STRING:
            esValido = true;
            break;
        case T_CHAR:
            esValido = validarChar(valor);
            break;
        case T_INT:
            esValido = validarInt(valor);
            break;
        case T_DOUBLE:
            esValido = validarDouble(valor);
            break;
        default:
            esValido = false;
    }
    return esValido;
}

bool Servidor::hayLugar(){
    int clientesActuales;
    pthread_mutex_lock(&mutexAgregar);
    clientesActuales = clientes.size();
    pthread_mutex_unlock(&mutexAgregar);
    return clientesActuales < cantidadMaximaDeClientes;
}

/*
void Servidor::iniciarEscenario(){
  Escenario* escenario = new Escenario(800, 600);
  this->escenario = escenario;
  cout << "Se creo el escenario" << endl;
}
*/

EscenarioJuego* Servidor::getEscenario(){
    return this->escenario;
}

void Servidor::setEscenario(EscenarioJuego* unEscenario){
    this->escenario = unEscenario;
}

void Servidor::imprimirDatosInicialesEscenario(){
    // string codigo = Decodificador::getCodigoEstadoInicial(this->escenario);
    // Decodificador::imprimirBytes(codigo);
    // string cosasEscenario = Decodificador::popEscenarioInicial(codigo);
    // cout << "Ancho: " <<Decodificador::popInt(cosasEscenario)<< endl;
    // cout << "Alto: " <<Decodificador::popInt(cosasEscenario)<< endl;
    // cout << "Sprite: " <<cosasEscenario<< endl;
    //
    // int cantidadAviones = Decodificador::popInt(codigo);
    // cout << "Cantidad de aviones: " << cantidadAviones << endl;
    //
    // string cosasAvion;
    // for (int i = 0; i < cantidadAviones; i ++){
    //     cosasAvion = Decodificador::popAvionInicial(codigo);
    //     cout << "Avion pos x: " << Decodificador::popFloat(cosasAvion) << endl;
    //     cout << "Avion pos y: " << Decodificador::popFloat(cosasAvion) << endl;
    //     cout << "Sprite: " <<cosasAvion<< endl;
    // }
    //
}
