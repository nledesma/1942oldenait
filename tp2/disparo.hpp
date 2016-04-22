#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Disparo {
private: 
	string tipo;
	int velocidad;
	string idSprite;
public:
	Disparo();
	~Disparo();
	void setTipo(string tipo);
	string getTipo();
	void setVelocidad(int velocidad);
	int getVelocidad();
	void setIdSprite(string idSprite);
	string getIdSprite();
};