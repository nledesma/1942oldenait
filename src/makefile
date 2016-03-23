LIBS = -lpthread
DIRS = -Inet

all: program

program: main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o mainServidor.o cliente.o gameSocket.o clienteParser.o fabricaMensajes.o
					g++ -Wall -pedantic -o program main.o tinyxml2.o servidorParser.o servidor.o mensajeString.o mensajeInt.o mensajeChar.o mensajeDouble.o mensaje.o mainServidor.o cliente.o gameSocket.o clienteParser.o fabricaMensajes.o


main.o: main.cpp net/cliente.hpp net/servidor.cpp net/cliente.cpp
					 g++ -c -o main.o main.cpp $(LIBS) $(DIRS)

cliente.o: net/cliente.cpp net/gameSocket.cpp net/mensaje.cpp
						g++ -Wall -pedantic -c -o cliente.o net/cliente.cpp

gameSocket.o: net/gameSocket.cpp
							g++ -Wall -pedantic -c -o gameSocket.o net/gameSocket.cpp

clienteParser.o: net/clienteParser.cpp net/tinyxml2.cpp net/fabricaMensajes.cpp net/cliente.cpp
									g++ -Wall -pedantic -c -o clienteParser.o net/clienteParser.cpp

fabricaMensajes.o: net/fabricaMensajes.cpp net/mensaje.cpp net/mensajeInt.cpp net/mensajeString.cpp net/mensajeChar.cpp net/mensajeDouble.cpp
									g++ -Wall -pedantic -c -o fabricaMensajes.o net/fabricaMensajes.cpp

mainServidor.o: net/mainServidor.cpp net/cliente.cpp net/servidor.cpp net/mensaje.cpp net/servidorParser.cpp
								g++ -Wall -pedantic -c -o mainServidor.o net/mainServidor.cpp $(LIBS)

mensaje.o: net/mensaje.cpp
						g++ -Wall -pedantic -c -o mensaje.o net/mensaje.cpp

mensajeChar.o: net/mensajeChar.cpp
							g++ -Wall -pedantic -c -o mensajeChar.o net/mensajeChar.cpp

mensajeDouble.o: net/mensajeDouble.cpp
									g++ -Wall -pedantic -c -o mensajeDouble.o net/mensajeDouble.cpp

mensajeInt.o: net/mensajeInt.cpp
							g++ -Wall -pedantic -c -o mensajeInt.o net/mensajeInt.cpp

mensajeString.o: net/mensajeString.cpp
								g++ -Wall -pedantic -c -o mensajeString.o net/mensajeString.cpp

servidor.o: net/servidor.cpp net/gameSocket.cpp net/mensaje.cpp
						g++ -Wall -pedantic -c -o servidor.o net/servidor.cpp $(LIBS) $(DIRS)

servidorParser.o: net/servidorParser.cpp net/tinyxml2.cpp
									g++ -Wall -pedantic -c -o servidorParser.o net/servidorParser.cpp

tinyxml2.o: net/tinyxml2.cpp
						g++ -Wall -pedantic -c -o tinyxml2.o net/tinyxml2.cpp

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
