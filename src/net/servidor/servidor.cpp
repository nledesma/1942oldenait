#include "servidor.hpp"

using namespace std;

/* Inicio del servidor */
Servidor::Servidor(int port, int cantidadDeClientes) : GameSocket() {
    partidaEnJuego = false;
    try {
        iniciarSocket();
        inicializar(port);
    } catch (runtime_error &e) {
        Logger::instance()->logError(errno, "Se produjo un error en el BIND");
    }

    setCantidadMaximaDeClientes(cantidadDeClientes);
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
    while (this->hayLugar() && servidorActivo()) {
        pthread_cond_wait(&this->condPartidaLlena, &this->mutexPartidaLlena);
    }
    pthread_mutex_unlock(&this->mutexPartidaLlena);
    if (servidorActivo()) {
        partidaEnJuego = true;
        cout << "Comenzando partida!" << endl;
    }
}

void Servidor::setAddress(int port) {
    this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
    this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
    this->addr_info.sin_addr.s_addr = INADDR_ANY; // El socket se puede asociar a cualquier conexión
    memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

void Servidor::pasivar() {

    int resultadoListen = listen(this->socketFd, this->cantidadMaximaDeClientes);
    if (resultadoListen == -1) {
        throw runtime_error("LISTEN_EXCEPTION");
    }
    servidorActivado = true;
    pthread_create(&this->cicloAceptaciones, NULL, cicloAceptar, (void *) this);
}

void Servidor::iniciarCicloDesencolaciones(){
    pthread_create(&this->cicloDesencolaciones, NULL, cicloDesencolar, (void *) this );
}

// Se fija si se dan las condiciones para que entre fdCliente y se elabora el
// mensaje de respuesta correspondiente.
string Servidor::evaluarIngreso(string nombre){
    if (partidaEnJuego){
        // Si la partida está activa entonces hay que ver si el nombre está activo.
        if (nombres.count(nombre) > 0){
            if (nombres[nombre]){
                return "El usuario con ese nombre ya está jugando.";
            } else {
                return "OK";
            }
        } else {
            return "La partida está llena.";
        }
    } else {
        // Si la partida no está activa hay que ver si el nombre está disponible.
        if (nombres.count(nombre) == 0){
            return "OK";
        } else {
            return "El nombre está en uso.";
        }
    }
}

bool Servidor::partidaActiva(){
    return partidaEnJuego;
}

void *Servidor::cicloAceptar(void *THIS) {
    Servidor *servidor = (Servidor *) THIS;
    int fdCliente;
    string nombre;
    while (servidor->servidorActivo()) {
        try {
            fdCliente = servidor->aceptar();
            servidor->recibirMensaje(nombre, fdCliente);
            string respuesta = servidor->evaluarIngreso(nombre);
            // En cualquier caso se le envía la respuesta.
            servidor->enviarMensaje(respuesta, fdCliente);
            if (respuesta == "OK"){
                // Si puede entrar, se lo agrega.
                servidor->agregarCliente(fdCliente, nombre);
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
    cout << "se envía el estado inicial." << endl;
    string estadoInicial = Decodificador::getCodigoEstadoInicial(escenario);
    // Se le agrega el número de avión que le corresponde al cliente.
    Decodificador::pushCantidad(estadoInicial, clientes[fdCliente].nroJugador);
    enviarMensaje(estadoInicial, fdCliente);
}

void *Servidor::atenderCliente(void *arg) {
    pair<Servidor *, int> *parServidorCliente = (pair<Servidor *, int> *) arg;
    Servidor *servidor = parServidorCliente->first;
    int fdCliente = parServidorCliente->second;
    pair<int, string> clienteMensaje;
    clienteMensaje.first = fdCliente;

    // Antes de atenderlo se espera a que se conecten todos.
    if(!servidor->partidaActiva()) servidor->esperarPartida(fdCliente);
    servidor->enviarEstadoInicial(fdCliente);
    if(!servidor->partidaActiva()) servidor->signalComienzaPartida();

    int recieveResult = ESTADO_INICIAL;
    while (servidor->validarEstadoConexion(recieveResult) && servidor->clienteConectado(fdCliente)) {
        string mensajeCliente;
        recieveResult = servidor->recibirMensaje(mensajeCliente, fdCliente);

        if(recieveResult != MENSAJEOK) {
            cout << "Se ha desconectado un cliente." << endl;
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
        int result = this->enviarMensaje(mensaje, clienteFd);
        if(result == CLIENTE_DESCONECTADO){
            cout << "Se ha desconectado el jugador " << clientes[clienteFd].nroJugador << endl;
            this->quitarCliente(clienteFd);
        }
    }
    usleep(100);
}

int Servidor::aceptar() {
    int resulAccept = accept(socketFd, 0, 0);

    if (resulAccept == -1) {
        throw runtime_error("ACCEPT_EXCEPTION");
    }
    // Timeout de minuto y medio para recibir mensajes del cliente.
    // struct timeval tv;
    // // TODO cambiar esto para que no se salga por inactividad.
    // tv.tv_sec = 10;
    // tv.tv_usec = 0;
    // setsockopt(resulAccept, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(struct timeval));

    //setsockopt(resulAccept, SOL_SOCKET, SO_SNDTIMEO, NULL, NULL);

    if(this->servidorActivado) {
        Logger::instance()->logInfo("La conexión ha sido aceptada");
    }

    return resulAccept;
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
    this->escenario->desactivar();
    pthread_cond_signal(&condPartidaLlena);
    cout << "Servidor cerrado" << endl;
    Logger::instance()->logInfo("El servidor ha sido cerrado");
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
    cout << "Faltan " << clientesFaltantes() << " jugadores." << endl;
    while(hayLugar() && servidorActivo()){
        string mensaje = "";
        // Enviamos la cantidad de clientes faltantes al cliente.
        Decodificador::pushCantidad(mensaje, clientesFaltantes());
        enviarMensaje(mensaje, fdCliente);
        // Espera un segundo antes de mandar de nuevo.
        usleep(5000);
    }
}

string Servidor::obtenerDireccion(int fdCliente){
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    getpeername(fdCliente, (sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
    int port = ntohs(client_addr.sin_port);
    char *clientAddress = inet_ntoa(client_addr.sin_addr);

    stringstream direccionCliente;
    direccionCliente << clientAddress << ":" << port;
    return direccionCliente.str();
}

void Servidor::agregarCliente(int fdCliente, string nombre) {

    datosCliente datos;
    datos.conectado = true;
    if (!partidaEnJuego){
        datos.nroJugador = (int) clientes.size() + 1;
        nroAvionSegunNombre[nombre] = datos.nroJugador;
        cout << "Se agrega al jugador " << nombre << " con el nro de avión " << datos.nroJugador << endl;
    } else {
        datos.nroJugador = nroAvion(nombre);
        cout << "Se conecta el jugador " << nombre << " al avión " << datos.nroJugador << endl;
    }
    datos.nombreJugador = nombre;
    if(this->escenario->estaActivo()){
        escenario->avion(datos.nroJugador)->setEstadoAnimacion(ESTADO_NORMAL);
    }
    nombres[nombre] = true;

    string dir = obtenerDireccion(fdCliente);
    cout << "Conectado a un cliente en la dirección " + dir << endl;
    Logger::instance()->logInfo("Conectado a un cliente en la dirección " + dir);
    // TODO no debería haber un mutex acá?
    direcciones.insert(pair<int, string>(fdCliente, dir));

    pthread_mutex_lock(&mutexAgregar);
    clientes.insert(pair<int, datosCliente>(fdCliente, datos));
    pthread_mutex_unlock(&mutexAgregar);

    pair<Servidor *, int> arg(this, fdCliente);

    pthread_create(&(clientes[fdCliente].th_entrada), NULL, atenderCliente, &arg);
    pthread_create(&(clientes[fdCliente].th_salida), NULL, responderCliente, &arg);
}

void Servidor::quitarCliente(int clienteFd) {
    nombres[clientes[clienteFd].nombreJugador] = false;
    list<Avion*>::iterator itAviones = this->escenario->getAviones().begin();
    advance(itAviones, clientes[clienteFd].nroJugador - 1);
    if(partidaEnJuego) {
        (*itAviones)->setEstadoAnimacion(DESCONECTADO);
    }
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
        usleep(500);
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
        if(intEvento != PRESIONA_X){
            this->escenario->pushEvento(evento);
        } else {
            this->cerrar();
        }
    }
    // Para evitar el envío de mensajes viejos al pasar de etapa nos fijamos si está activo.
    if (escenario->estaActivo()) {
        string codigoEstadoActual = Decodificador::getCodigoEstadoActual(this->escenario);
        this->broadcastMensaje(codigoEstadoActual);
    }
}

void Servidor::broadcastMensaje(string codigoEstadoEscenario) {
    for (map<int, datosCliente>::iterator iterador = getClientes().begin(); iterador != getClientes().end(); iterador++) {
        int clienteActual = iterador->first;
        encolarSalida(clienteActual, codigoEstadoEscenario);
    }
}

void Servidor::broadcastEvento(int evento) {
    string mensaje = "";
    Decodificador::pushCantidad(mensaje, evento);
    broadcastMensaje(mensaje);
}

/* Ejecución general */
void Servidor::ejecutar() {
    // Servidor aceptando conexiones
    try {
        pasivar();
    } catch(runtime_error &e) {
        Logger::instance()->logError(errno,"Se produjo un error en el listen");
    }

    esperarJugadores();
    // TODO lo ideal no sería esperar un segundo, sino esperar a recibir un
    // evento de todos los clientes avisando que ya cargaron el nivel.
    sleep(1);

    // Se puede haber cerrado el servidor antes de recibir a todos los jugadores.
    if (servidorActivo()) {
        // Comienza la partida.
        iniciarCicloDesencolaciones();
        escenario->jugar(servidorActivo());
    }

    while (servidorActivo() && escenario->quedanEtapas()) {
        broadcastEvento(AVANZAR_ETAPA);
        escenario->comenzarEtapa();
    }

    broadcastEvento(FINALIZAR_JUEGO);
    partidaEnJuego = false;
}

/* Getters y Setters */

void Servidor::setPuerto(int unPuerto) {
    puerto = unPuerto;
}

int Servidor::getPuerto() {
    return puerto;
}

map<int, datosCliente>& Servidor::getClientes(){
    return clientes;
}

void Servidor::setCantidadMaximaDeClientes(int unaCantidadDeClientes) {
    cantidadMaximaDeClientes = unaCantidadDeClientes;
}

int Servidor::getCantidadMaximaDeClientes() {
    return cantidadMaximaDeClientes;
}

EscenarioJuego* Servidor::getEscenario(){
    return this->escenario;
}

void Servidor::setEscenario(EscenarioJuego* unEscenario){
    string str = (cantidadMaximaDeClientes > 1 ? "es" : "");
    cout << "Se esperará a " << cantidadMaximaDeClientes << " jugador" << str << " para comenzar la partida" << endl;
    this->escenario = unEscenario;
}

bool Servidor::hayLugar(){
    return clientesFaltantes() > 0;
}

int Servidor::clientesFaltantes() {
    int clientesActuales;
    pthread_mutex_lock(&mutexAgregar);
    clientesActuales = clientes.size();
    pthread_mutex_unlock(&mutexAgregar);
    return cantidadMaximaDeClientes - clientesActuales;
}

int Servidor::nroAvion(string nombre){
    return nroAvionSegunNombre[nombre];
}
