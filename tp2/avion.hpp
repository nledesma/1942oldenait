#include <SDL2/SDL.h>
#include <iostream>
#include "disparo.hpp"

using namespace std;

class Avion{
private: 
	string idSprite;
	int velocidadDesplazamiento;
	Disparo disparo;
	string idSpriteAnimacion;
	string idSpriteDisparo;

public:
	Avion(string idSprite,int velocidadDesplazamiento,string idSpriteAnimacion, Disparo unDisparo);
	~Avion();
	void setDisparo(Disparo unDisparo);
	Disparo getDisparo();
	string getIdSprite();
	void setIdSprite(string idSprite);
	int getVelocidadDesplazamiento();
	void setVelocidadDesplazamiento(int velocidadDesplazamiento);
	string getIdSpriteAnimacion();
	void setIdSpriteAnimacion(string idSpriteAnimacion);
	void mover(int tecla);
	void disparar();
};