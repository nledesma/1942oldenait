# Cosas del compilador.
CXX = g++ -std=c++11
DEBUG = -g -O0
WAR = -Wall -pedantic
CXXFLAGS = $(DEBUG) $(WAR)

# Librerias.
LIBS = -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Directorios de código fuente.
NET_PATH = src/net
LOGGER_PATH = src/logger
COLA_PATH = src/accesorios/colaConcurrente
TEMPORIZADOR_PATH = src/accesorios
COLISIONES_PATH = src/accesorios/colisiones
XML_PATH = resources/lib
JUEGO_MODELO_PATH = src/juego/modelo
JUEGO_VISTA_PATH = src/juego/vista
TRAYECTORIA_PATH = src/juego/modelo/trayectoriasEnemigos
MENU_PATH = src/menu

SRC = app:$(NET_PATH):$(NET_PATH)/cliente:$(NET_PATH)/servidor:\
	$(NET_PATH)/mensaje:$(COLA_PATH):$(LOGGER_PATH):$(XML_PATH): \
	$(JUEGO_MODELO_PATH):$(JUEGO_VISTA_PATH):$(TEMPORIZADOR_PATH): \
	$(TRAYECTORIA_PATH):$(COLISIONES_PATH):$(MENU_PATH):$(MENU_PATH)/Menu:$(MENU_PATH)/Boton
vpath %.cpp $(SRC)

# Compilados.
OBJS_LIST = tinyxml2.o cliente.o servidor.o servidorParser.o gameSocket.o \
	logger.o colaConcurrente.o avion.o disparo.o clienteParser.o etapa.o etapaVista.o \
	elemento.o escenarioJuego.o avionVista.o disparoVista.o elementoVista.o \
	escenarioVista.o figura.o ventana.o decodificador.o temporizador.o parserXML.o \
	soundboard.o avionEnemigo.o avionPequenio.o avionDeEscuadron.o avionMediano.o \
	avionGrande.o desplazamiento.o giro.o tipoMovimiento.o trayectoriaCuadrada.o \
	trayectoria.o trigonomaster.o fabricaEnemigos.o enemigoVista.o enemigoPequenio.o \
	enemigoMediano.o enemigoDeEscuadron.o enemigoGrande.o movimientoAvionGrandeEtapa1.o \
	movimientoAvionGrandeEtapa2.o trayectoriaAvionGrande.o trayectoriaRandom.o powerUp.o \
	powerUpParseado.o fabricaPowerUps.o powerUpBonificacion.o powerUpDosAmetralladoras.o \
	powerUpDestruirEnemigos.o powerUpAvionesSecundarios.o punto.o superficie.o celda.o \
	colisionable.o grilla.o trayectoriaIdaYvuelta.o trayectoriaRulo.o boton.o botonEnColaboracion.o \
	botonJugar.o botonModoPractica.o botonPorEquipos.o botonSalir.o botonSiguiente.o \
	menu.o menuDatosDeUsuario.o menuModosDeJuego.o menuPrincipal.o menuConexiones.o texto.o \
	textoDinamico.o radioButton.o listaDeSeleccion.o

DIR_OBJS = compilados
OBJS = $(addprefix $(DIR_OBJS)/,$(OBJS_LIST))

# Binarios.
BIN = bin
CLIENTE = $(BIN)/cliente
SERVIDOR = $(BIN)/servidor
OPCIONES = $(BIN)/opciones

# Reglas:
all: makeDirs $(SERVIDOR)/mainServidorJuego $(CLIENTE)/mainClienteMenu $(OPCIONES)/mainOpciones

$(SERVIDOR)/mainServidorJuego: $(DIR_OBJS)/mainServidorJuego.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(SERVIDOR)/servidor $(LIBS)

$(CLIENTE)/mainClienteMenu: $(DIR_OBJS)/mainClienteMenu.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(CLIENTE)/cliente $(LIBS)

$(OPCIONES)/mainOpciones: $(DIR_OBJS)/mainOpciones.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(OPCIONES)/opciones $(LIBS)

# Compilación de todos los .o, que es igual.
$(DIR_OBJS)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY: makeDirs clean

makeDirs:
	mkdir -p $(CLIENTE) $(SERVIDOR) $(OPCIONES)
	mkdir -p $(DIR_OBJS)

clean:
	# Borrado de objetos y ejecutables, si los hay.
	rm -f $(OBJS)/*.o
	rm -f $(CLIENTE)/cliente
	rm -f $(SERVIDOR)/servidor
	rm -f $(OPCIONES)/opciones
