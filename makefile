LIBS = -lpthread
DIRS = -Inet -IThread
WAR = -Wall -pedantic
NET_PATH = src/net/
THREAD_PATH = src/Thread/
LOGGER_PATH = src/logger/
DEBUG = -g -O0
BIN = bin/
CLIENTE = $(BIN)/cliente/
SERVIDOR = $(BIN)/servidor/
CC = g++ -std=c++11
COMPILED_FILES&DIR = $(OBJS)tinyxml2.o $(OBJS)cliente.o $(OBJS)servidor.o $(OBJS)servidorParser.o $(OBJS)gameSocket.o $(OBJS)mensajeString.o $(OBJS)mensajeInt.o $(OBJS)mensajeChar.o $(OBJS)mensajeDouble.o $(OBJS)mensaje.o $(OBJS)fabricaMensajes.o $(OBJS)logger.o $(OBJS)clienteParser.o
COMPILED_FILES = tinyxml2.o cliente.o servidor.o servidorParser.o gameSocket.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o fabricaMensajes.o logger.o clienteParser.o

OBJS = compilados/

all: mainServidor mainCliente

mainServidor: mainServidor.o $(COMPILED_FILES)
	$(CC) $(DEBUG) $(WAR) $(OBJS)mainServidor.o $(COMPILED_FILES&DIR) -o $(SERVIDOR)servidor $(LIBS)

mainCliente: mainCliente.o $(COMPILED_FILES)
	$(CC) $(DEBUG) $(WAR) $(OBJS)mainCliente.o $(COMPILED_FILES&DIR) -o $(CLIENTE)cliente $(LIBS)

mainServidor.o: app/mainServidor.cpp $(NET_PATH)servidor/servidor.cpp $(NET_PATH)cliente/cliente.cpp
	$(CC) $(DEBUG) -o $(OBJS)mainServidor.o app/mainServidor.cpp $(DIRS) -c

mainCliente.o: app/mainCliente.cpp $(NET_PATH)cliente/cliente.cpp $(NET_PATH)cliente/clienteParser.cpp $(NET_PATH)gameSocket.cpp
	$(CC) $(DEBUG) -c -o $(OBJS)mainCliente.o app/mainCliente.cpp

cliente.o: $(NET_PATH)cliente/cliente.cpp src/net/gameSocket.cpp $(NET_PATH)mensaje/mensaje.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)cliente.o $(NET_PATH)cliente/cliente.cpp

gameSocket.o: $(NET_PATH)gameSocket.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)gameSocket.o $(NET_PATH)gameSocket.cpp

clienteParser.o: $(NET_PATH)cliente/clienteParser.cpp resources/lib/tinyxml2.cpp $(NET_PATH)mensaje/fabricaMensajes.cpp $(NET_PATH)cliente/cliente.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)clienteParser.o $(NET_PATH)cliente/clienteParser.cpp

fabricaMensajes.o: $(NET_PATH)mensaje/fabricaMensajes.cpp $(NET_PATH)mensaje/mensaje.cpp $(NET_PATH)mensaje/mensajeInt.cpp $(NET_PATH)mensaje/mensajeString.cpp $(NET_PATH)mensaje/mensajeChar.cpp $(NET_PATH)mensaje/mensajeDouble.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)fabricaMensajes.o $(NET_PATH)mensaje/fabricaMensajes.cpp

mensaje.o: $(NET_PATH)mensaje/mensaje.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)mensaje.o $(NET_PATH)mensaje/mensaje.cpp

mensajeChar.o: $(NET_PATH)mensaje/mensajeChar.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)mensajeChar.o $(NET_PATH)mensaje/mensajeChar.cpp

mensajeDouble.o: $(NET_PATH)mensaje/mensajeDouble.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)mensajeDouble.o $(NET_PATH)mensaje/mensajeDouble.cpp

mensajeInt.o: $(NET_PATH)mensaje/mensajeInt.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)mensajeInt.o $(NET_PATH)mensaje/mensajeInt.cpp

mensajeString.o: $(NET_PATH)mensaje/mensajeString.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)mensajeString.o $(NET_PATH)mensaje/mensajeString.cpp

servidor.o: $(NET_PATH)servidor/servidor.cpp $(NET_PATH)gameSocket.cpp $(NET_PATH)mensaje/mensaje.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)servidor.o $(NET_PATH)servidor/servidor.cpp

servidorParser.o: $(NET_PATH)servidor/servidorParser.cpp resources/lib/tinyxml2.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)servidorParser.o $(NET_PATH)servidor/servidorParser.cpp

tinyxml2.o: resources/lib/tinyxml2.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)tinyxml2.o resources/lib/tinyxml2.cpp

thread.o: $(THREAD_PATH)thread.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)thread.o $(THREAD_PATH)thread.cpp

threadAtender.o: $(THREAD_PATH)threadAtender.cpp $(NET_PATH)servidor/servidor.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)threadAtender.o $(THREAD_PATH)threadAtender.cpp

threadAceptar.o: $(THREAD_PATH)threadAceptar.cpp $(NET_PATH)servidor/servidor.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)threadAceptar.o $(THREAD_PATH)threadAceptar.cpp

logger.o: $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o $(OBJS)logger.o $(LOGGER_PATH)logger.cpp

clean:
	rm $(OBJS)*.o
