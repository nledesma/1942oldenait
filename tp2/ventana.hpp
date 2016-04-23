#ifndef VENTANA_HPP
#define VENTANA_HPP

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
using namespace std;
struct Elemento{
	int posX;
	int posY;
	string idSprite;
};

class Ventana{
	private:
		string idSpriteFondo;
		int ancho;
		int alto;
		list <Elemento> elementos;

	public:
		Ventana();
		string getIdSpriteFondo();
		void setIdSpriteFondo(string id);
		int getAncho();
		void setAncho(int ancho);
		int getAlto();
		void setAlto(int alto);
		list <Elemento> getElementos();
		void agregarElemento(Elemento elemento);

};

#endif
