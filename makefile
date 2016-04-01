LIBS = -lpthread
DIRS = -Inet -IThread
WAR = -Wall -pedantic
NET_PATH = src/net/
THREAD_PATH = src/Thread/
LOGGER_PATH = src/
DEBUG = -g -O0

all: program mainServidor clean

program: main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o cliente.o gameSocket.o clienteParser.o fabricaMensajes.o logger.o
	g++ $(WAR) main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o cliente.o gameSocket.o clienteParser.o logger.o fabricaMensajes.o -o program  $(LIBS)

mainServidor: mainServidor.o tinyxml2.o cliente.o servidor.o servidorParser.o gameSocket.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o fabricaMensajes.o logger.o
	g++ $(DEBUG) $(WAR) mainServidor.o tinyxml2.o cliente.o servidor.o servidorParser.o gameSocket.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o fabricaMensajes.o logger.o -o servidor $(LIBS)

mainServidor.o: app/mainServidor.cpp $(NET_PATH)servidor/servidor.cpp $(NET_PATH)cliente/cliente.cpp
	g++ $(DEBUG) -o mainServidor.o app/mainServidor.cpp $(DIRS) -c

main.o: app/main.cpp $(NET_PATH)servidor/servidor.cpp $(NET_PATH)cliente/cliente.cpp
	g++ -c -o main.o app/main.cpp $(DIRS)

cliente.o: $(NET_PATH)cliente/cliente.cpp src/net/gameSocket.cpp $(NET_PATH)mensaje/mensaje.cpp $(LOGGER_PATH)logger.cpp
	g++ $(WAR) -c -o cliente.o $(NET_PATH)cliente/cliente.cpp

gameSocket.o: $(NET_PATH)gameSocket.cpp $(LOGGER_PATH)logger.cpp
	g++ $(WAR) -c -o gameSocket.o $(NET_PATH)gameSocket.cpp

clienteParser.o: $(NET_PATH)cliente/clienteParser.cpp resources/lib/tinyxml2.cpp $(NET_PATH)mensaje/fabricaMensajes.cpp $(NET_PATH)cliente/cliente.cpp $(LOGGER_PATH)logger.cpp
	g++ $(WAR) -c -o clienteParser.o $(NET_PATH)cliente/clienteParser.cpp

fabricaMensajes.o: $(NET_PATH)mensaje/fabricaMensajes.cpp $(NET_PATH)mensaje/mensaje.cpp $(NET_PATH)mensaje/mensajeInt.cpp $(NET_PATH)mensaje/mensajeString.cpp $(NET_PATH)mensaje/mensajeChar.cpp $(NET_PATH)mensaje/mensajeDouble.cpp $(LOGGER_PATH)logger.cpp
	g++ $(WAR) -c -o fabricaMensajes.o $(NET_PATH)mensaje/fabricaMensajes.cpp

mensaje.o: $(NET_PATH)mensaje/mensaje.cpp
	g++ $(WAR) -c -o mensaje.o $(NET_PATH)mensaje/mensaje.cpp

mensajeChar.o: $(NET_PATH)mensaje/mensajeChar.cpp
	g++ $(WAR) -c -o mensajeChar.o $(NET_PATH)mensaje/mensajeChar.cpp

mensajeDouble.o: $(NET_PATH)mensaje/mensajeDouble.cpp
	g++ $(WAR) -c -o mensajeDouble.o $(NET_PATH)mensaje/mensajeDouble.cpp

mensajeInt.o: $(NET_PATH)mensaje/mensajeInt.cpp
	g++ $(WAR) -c -o mensajeInt.o $(NET_PATH)mensaje/mensajeInt.cpp

mensajeString.o: $(NET_PATH)mensaje/mensajeString.cpp
	g++ $(WAR) -c -o mensajeString.o $(NET_PATH)mensaje/mensajeString.cpp

servidor.o: $(NET_PATH)servidor/servidor.cpp $(NET_PATH)gameSocket.cpp $(NET_PATH)mensaje/mensaje.cpp $(LOGGER_PATH)logger.cpp
	g++ $(DEBUG) $(WAR) -c -o servidor.o $(NET_PATH)servidor/servidor.cpp

servidorParser.o: $(NET_PATH)servidor/servidorParser.cpp resources/lib/tinyxml2.cpp $(LOGGER_PATH)logger.cpp
	g++ $(WAR) -c -o servidorParser.o $(NET_PATH)servidor/servidorParser.cpp

tinyxml2.o: resources/lib/tinyxml2.cpp
	g++ $(WAR) -c -o tinyxml2.o resources/lib/tinyxml2.cpp

thread.o: $(THREAD_PATH)thread.cpp
	g++ $(DEBUG) $(WAR) -c -o thread.o $(THREAD_PATH)thread.cpp

threadAtender.o: $(THREAD_PATH)threadAtender.cpp $(NET_PATH)servidor/servidor.cpp
	g++ $(DEBUG) $(WAR) -c -o threadAtender.o $(THREAD_PATH)threadAtender.cpp

threadAceptar.o: $(THREAD_PATH)threadAceptar.cpp $(NET_PATH)servidor/servidor.cpp
	g++ $(DEBUG) $(WAR) -c -o threadAceptar.o $(THREAD_PATH)threadAceptar.cpp

logger.o: $(LOGGER_PATH)logger.cpp
	g++ $(DEBUG) $(WAR) -c -o logger.o $(LOGGER_PATH)logger.cpp

clean:
	rm *.o
