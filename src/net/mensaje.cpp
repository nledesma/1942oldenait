#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

template <class T>


class Mensaje{
	private:
		int id;
		string tipo;
		T valor;
	public:

		Mensaje(int unId, T unValor, string unTipo);
		void setId(int unId);
		int getId();
		void setValor(T unValor);
		T getValor();
		string getTipo();
		void setTipo(string unTipo);

};

template <class T>
Mensaje<T>::Mensaje(int unId, T unValor, string unTipo) {
	id = unId;
	valor = unValor;
	tipo = unTipo;
}

template <class T>
void Mensaje<T>::setId(int unId) {
	id = unId;
}

template <class T>
int Mensaje<T>::getId() {
	return id;
} 
template <class T>
void Mensaje<T>::setValor(T unValor) {
	valor = unValor;
}
template <class T>
T Mensaje<T>::getValor() {
	return valor;
}

template <class T>
string Mensaje<T>::getTipo(){
	return tipo;
}

template <class T>
void Mensaje<T>::setTipo(string unTipo) {
	tipo = unTipo;
}

