LIBS = -lpthread
DIRS = -Inet
WAR = -Wall -pedantic
all: program

program: main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o cliente.o gameSocket.o clienteParser.o fabricaMensajes.o
					g++ $(WAR) main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o cliente.o gameSocket.o clienteParser.o fabricaMensajes.o -o program  $(LIBS)


main.o: main.cpp net/cliente.hpp net/servidor.cpp net/cliente.cpp
	g++ -c -o main.o main.cpp $(DIRS)

cliente.o: net/cliente.cpp net/gameSocket.cpp net/mensaje.cpp
	g++ $(WAR) -c -o cliente.o net/cliente.cpp

gameSocket.o: net/gameSocket.cpp
	g++ $(WAR) -c -o gameSocket.o net/gameSocket.cpp

clienteParser.o: net/clienteParser.cpp net/tinyxml2.cpp net/fabricaMensajes.cpp net/cliente.cpp
	g++ $(WAR) -c -o clienteParser.o net/clienteParser.cpp

fabricaMensajes.o: net/fabricaMensajes.cpp net/mensaje.cpp net/mensajeInt.cpp net/mensajeString.cpp net/mensajeChar.cpp net/mensajeDouble.cpp
	g++ $(WAR) -c -o fabricaMensajes.o net/fabricaMensajes.cpp

mensaje.o: net/mensaje.cpp
	g++ $(WAR) -c -o mensaje.o net/mensaje.cpp

mensajeChar.o: net/mensajeChar.cpp
	g++ $(WAR) -c -o mensajeChar.o net/mensajeChar.cpp

mensajeDouble.o: net/mensajeDouble.cpp
	g++ $(WAR) -c -o mensajeDouble.o net/mensajeDouble.cpp

mensajeInt.o: net/mensajeInt.cpp
	g++ $(WAR) -c -o mensajeInt.o net/mensajeInt.cpp

mensajeString.o: net/mensajeString.cpp
	g++ $(WAR) -c -o mensajeString.o net/mensajeString.cpp

servidor.o: net/servidor.cpp net/gameSocket.cpp net/mensaje.cpp
	g++ $(WAR) -c -o servidor.o net/servidor.cpp

servidorParser.o: net/servidorParser.cpp net/tinyxml2.cpp
	g++ $(WAR) -c -o servidorParser.o net/servidorParser.cpp

tinyxml2.o: net/tinyxml2.cpp
	g++ $(WAR) -c -o tinyxml2.o net/tinyxml2.cpp

clean:
	rm *.o *.exe


					#
					# all: tp
					#
					# tp: main.o entrada_salida.o evento.o evento_test.o resultado.o
					# 	g++ -Wall -pedantic -o tp main.o entrada_salida.o evento.o evento_test.o resultado.o
					#
					# entrada_salida.o: EntradaSalida.cpp EntradaSalida.hpp evento.hpp
					# 	g++ -Wall -pedantic -c -o entrada_salida.o EntradaSalida.cpp
					#
					# evento.o: evento.cpp evento.hpp
					# 	g++ -Wall -pedantic -c -o evento.o Evento.cpp
					#
					# evento_test.o: EventoTest.cpp EventoTest.hpp Resultado.hpp
					# 	g++ -Wall -pedantic -c -o evento_test.o EventoTest.cpp
					#
					# resultado.o: Resultado.cpp Resultado.hpp
					# 	g++ -Wall -pedantic -c -o resultado.o Resultado.cpp
					#
					# main.o: main.cpp Evento.hpp EntradaSalida.hpp
					# 	g++ -Wall -pedantic -c -o main.o main.cpp
					#
					# clean:
					# 	rm *.o *.exe
