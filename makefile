LIBS = -lpthread
DIRS = -Inet -IThread
WAR = -Wall -pedantic
NET_PATH = src/net/
THREAD_PATH = src/Thread/
LOGGER_PATH = src/
DEBUG = -g -O0
CC = g++ -std=c++11

all: program mainServidorViejo clean

program: main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o cliente.o gameSocket.o clienteParser.o fabricaMensajes.o logger.o
	$(CC) $(WAR) main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o cliente.o gameSocket.o clienteParser.o logger.o fabricaMensajes.o -o program  $(LIBS)

mainServidorViejo: mainServidorViejo.o tinyxml2.o cliente.o servidor.o servidorParser.o gameSocket.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o fabricaMensajes.o logger.o
	$(CC) $(DEBUG) $(WAR) mainServidorViejo.o tinyxml2.o cliente.o servidor.o servidorParser.o gameSocket.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o fabricaMensajes.o logger.o -o servidor $(LIBS)

mainServidorViejo.o: app/mainServidorViejo.cpp $(NET_PATH)servidor/servidor.cpp $(NET_PATH)cliente/cliente.cpp
	$(CC) $(DEBUG) -o mainServidorViejo.o app/mainServidorViejo.cpp $(DIRS) -c

main.o: app/main.cpp $(NET_PATH)servidor/servidor.cpp $(NET_PATH)cliente/cliente.cpp
	$(CC) $(DEBUG) -c -o main.o app/main.cpp $(DIRS)

cliente.o: $(NET_PATH)cliente/cliente.cpp src/net/gameSocket.cpp $(NET_PATH)mensaje/mensaje.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o cliente.o $(NET_PATH)cliente/cliente.cpp

gameSocket.o: $(NET_PATH)gameSocket.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o gameSocket.o $(NET_PATH)gameSocket.cpp

clienteParser.o: $(NET_PATH)cliente/clienteParser.cpp resources/lib/tinyxml2.cpp $(NET_PATH)mensaje/fabricaMensajes.cpp $(NET_PATH)cliente/cliente.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o clienteParser.o $(NET_PATH)cliente/clienteParser.cpp

fabricaMensajes.o: $(NET_PATH)mensaje/fabricaMensajes.cpp $(NET_PATH)mensaje/mensaje.cpp $(NET_PATH)mensaje/mensajeInt.cpp $(NET_PATH)mensaje/mensajeString.cpp $(NET_PATH)mensaje/mensajeChar.cpp $(NET_PATH)mensaje/mensajeDouble.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o fabricaMensajes.o $(NET_PATH)mensaje/fabricaMensajes.cpp

mensaje.o: $(NET_PATH)mensaje/mensaje.cpp
	$(CC) $(DEBUG) $(WAR) -c -o mensaje.o $(NET_PATH)mensaje/mensaje.cpp

mensajeChar.o: $(NET_PATH)mensaje/mensajeChar.cpp
	$(CC) $(DEBUG) $(WAR) -c -o mensajeChar.o $(NET_PATH)mensaje/mensajeChar.cpp

mensajeDouble.o: $(NET_PATH)mensaje/mensajeDouble.cpp
	$(CC) $(DEBUG) $(WAR) -c -o mensajeDouble.o $(NET_PATH)mensaje/mensajeDouble.cpp

mensajeInt.o: $(NET_PATH)mensaje/mensajeInt.cpp
	$(CC) $(DEBUG) $(WAR) -c -o mensajeInt.o $(NET_PATH)mensaje/mensajeInt.cpp

mensajeString.o: $(NET_PATH)mensaje/mensajeString.cpp
	$(CC) $(DEBUG) $(WAR) -c -o mensajeString.o $(NET_PATH)mensaje/mensajeString.cpp

servidor.o: $(NET_PATH)servidor/servidor.cpp $(NET_PATH)gameSocket.cpp $(NET_PATH)mensaje/mensaje.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o servidor.o $(NET_PATH)servidor/servidor.cpp

servidorParser.o: $(NET_PATH)servidor/servidorParser.cpp resources/lib/tinyxml2.cpp $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o servidorParser.o $(NET_PATH)servidor/servidorParser.cpp

tinyxml2.o: resources/lib/tinyxml2.cpp
	$(CC) $(DEBUG) $(WAR) -c -o tinyxml2.o resources/lib/tinyxml2.cpp

thread.o: $(THREAD_PATH)thread.cpp
	$(CC) $(DEBUG) $(WAR) -c -o thread.o $(THREAD_PATH)thread.cpp

threadAtender.o: $(THREAD_PATH)threadAtender.cpp $(NET_PATH)servidor/servidor.cpp
	$(CC) $(DEBUG) $(WAR) -c -o threadAtender.o $(THREAD_PATH)threadAtender.cpp

threadAceptar.o: $(THREAD_PATH)threadAceptar.cpp $(NET_PATH)servidor/servidor.cpp
	$(CC) $(DEBUG) $(WAR) -c -o threadAceptar.o $(THREAD_PATH)threadAceptar.cpp

logger.o: $(LOGGER_PATH)logger.cpp
	$(CC) $(DEBUG) $(WAR) -c -o logger.o $(LOGGER_PATH)logger.cpp

clean:
	rm *.o
