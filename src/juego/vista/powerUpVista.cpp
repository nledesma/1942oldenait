#include "powerUpVista.hpp"

void PowerUpVista::cargarImagen(SDL_Renderer * renderer){
	cout << "El path del sprite es: " << this->pathSprite << endl;
	cout << "FIGURA POWER UP: " << this->figuraPowerUp << endl;
    this->figuraPowerUp->loadFromFile(this->pathSprite, renderer);
}

void PowerUpVista::render(float posX, float posY, int estadoAnimacion, SDL_Renderer* renderer){
    this->estadoAnimacion = estadoAnimacion;
    this->figuraPowerUp->render((int)posX, (int)posY, renderer, &clipsAnimacion[estadoAnimacion]);
}

void PowerUpVista::cerrar() {
    this->figuraPowerUp->free();
}
