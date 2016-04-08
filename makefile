# Cosas del compilador.
CXX = g++ -std=c++11
DEBUG = -g -O0
WAR = -Wall -pedantic
CXXFLAGS = $(DEBUG) $(WAR)

# Librerias.
LIBS = -lpthread

# Directorios de código fuente.
NET_PATH = src/net
LOGGER_PATH = src/logger
COLA_PATH = src/accesorios/colaConcurrente
XML_PATH = resources/lib

SRC = app:$(NET_PATH):$(NET_PATH)/cliente:$(NET_PATH)/servidor:\
	$(NET_PATH)/mensaje:$(COLA_PATH):$(LOGGER_PATH):$(XML_PATH)
vpath %.cpp $(SRC)

# Compilados.
OBJS_LIST = tinyxml2.o cliente.o servidor.o servidorParser.o gameSocket.o \
	mensaje.o logger.o clienteParser.o colaConcurrente.o
DIR_OBJS = compilados
OBJS = $(addprefix $(DIR_OBJS)/,$(OBJS_LIST))

# Binarios.
BIN = bin
CLIENTE = $(BIN)/cliente
SERVIDOR = $(BIN)/servidor

# Reglas:
all: makeDirs $(SERVIDOR)/mainServidor $(CLIENTE)/mainCliente

$(SERVIDOR)/mainServidor: $(DIR_OBJS)/mainServidor.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(SERVIDOR)/servidor $(LIBS)

$(CLIENTE)/mainCliente: $(DIR_OBJS)/mainCliente.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(CLIENTE)/cliente $(LIBS)

# Compilación de todos los .o, que es igual.
$(DIR_OBJS)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY: makeDirs clean

makeDirs:
	mkdir -p $(CLIENTE) $(SERVIDOR)
	mkdir -p $(DIR_OBJS)

clean:
	# Borrado de objetos y ejecutables, si los hay.
	rm -f $(OBJS)/*.o
	rm -f $(CLIENTE)/cliente
	rm -f $(SERVIDOR)/servidor
