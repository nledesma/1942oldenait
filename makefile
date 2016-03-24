LIBS = -lpthread
DIRS = -Inet
WAR = -Wall -pedantic
DOMAIN_PATH = src/net/
all: program

program: main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o cliente.o gameSocket.o clienteParser.o fabricaMensajes.o
					g++ $(WAR) main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o cliente.o gameSocket.o clienteParser.o fabricaMensajes.o -o program  $(LIBS)


main.o: app/main.cpp $(DOMAIN_PATH)servidor/servidor.cpp $(DOMAIN_PATH)cliente/cliente.cpp
	g++ -c -o main.o app/main.cpp $(DIRS)

cliente.o: $(DOMAIN_PATH)cliente/cliente.cpp src/net/gameSocket.cpp $(DOMAIN_PATH)mensaje/mensaje.cpp
	g++ $(WAR) -c -o cliente.o $(DOMAIN_PATH)cliente/cliente.cpp

gameSocket.o: $(DOMAIN_PATH)gameSocket.cpp
	g++ $(WAR) -c -o gameSocket.o $(DOMAIN_PATH)gameSocket.cpp

clienteParser.o: $(DOMAIN_PATH)cliente/clienteParser.cpp $(DOMAIN_PATH)tinyxml2.cpp $(DOMAIN_PATH)mensaje/fabricaMensajes.cpp $(DOMAIN_PATH)cliente/cliente.cpp
	g++ $(WAR) -c -o clienteParser.o $(DOMAIN_PATH)cliente/clienteParser.cpp

fabricaMensajes.o: $(DOMAIN_PATH)mensaje/fabricaMensajes.cpp $(DOMAIN_PATH)mensaje/mensaje.cpp $(DOMAIN_PATH)mensaje/mensajeInt.cpp $(DOMAIN_PATH)mensaje/mensajeString.cpp $(DOMAIN_PATH)mensaje/mensajeChar.cpp $(DOMAIN_PATH)mensaje/mensajeDouble.cpp
	g++ $(WAR) -c -o fabricaMensajes.o $(DOMAIN_PATH)mensaje/fabricaMensajes.cpp

mensaje.o: $(DOMAIN_PATH)mensaje/mensaje.cpp
	g++ $(WAR) -c -o mensaje.o $(DOMAIN_PATH)mensaje/mensaje.cpp

mensajeChar.o: $(DOMAIN_PATH)mensaje/mensajeChar.cpp
	g++ $(WAR) -c -o mensajeChar.o $(DOMAIN_PATH)mensaje/mensajeChar.cpp

mensajeDouble.o: $(DOMAIN_PATH)mensaje/mensajeDouble.cpp
	g++ $(WAR) -c -o mensajeDouble.o $(DOMAIN_PATH)mensaje/mensajeDouble.cpp

mensajeInt.o: $(DOMAIN_PATH)mensaje/mensajeInt.cpp
	g++ $(WAR) -c -o mensajeInt.o $(DOMAIN_PATH)mensaje/mensajeInt.cpp

mensajeString.o: $(DOMAIN_PATH)mensaje/mensajeString.cpp
	g++ $(WAR) -c -o mensajeString.o $(DOMAIN_PATH)mensaje/mensajeString.cpp

servidor.o: $(DOMAIN_PATH)servidor/servidor.cpp $(DOMAIN_PATH)gameSocket.cpp $(DOMAIN_PATH)mensaje/mensaje.cpp
	g++ $(WAR) -c -o servidor.o $(DOMAIN_PATH)servidor/servidor.cpp

servidorParser.o: $(DOMAIN_PATH)servidor/servidorParser.cpp $(DOMAIN_PATH)tinyxml2.cpp
	g++ $(WAR) -c -o servidorParser.o $(DOMAIN_PATH)servidor/servidorParser.cpp

tinyxml2.o: $(DOMAIN_PATH)tinyxml2.cpp
	g++ $(WAR) -c -o tinyxml2.o $(DOMAIN_PATH)tinyxml2.cpp

clean:
	rm *.o
