#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "avion.hpp"
#include "ventana.hpp"

using namespace std;

struct fondo{
	string idSpriteFondo;
	int ancho;
	int alto;
};

class Escenario{
	private:
		int ancho;
		int alto;
		Ventana ventana;
		list<Avion*> aviones;

	public:
		Escenario(int ancho, int alto, Ventana ventana);
		~Escenario();
		int getAncho();
		int getAlto();
		Ventana getVentana();
		list<Avion*> getAviones();
		void agregarAvion(Avion* avion);
};