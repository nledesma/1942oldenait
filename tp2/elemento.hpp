#include <iostream>
#include <time.h>
#include <cmath>
#include <SDL2/SDL.h>
#include "figura.hpp"

using namespace std;
class Elemento{
private:
  string spriteId;
  float posX;
  float posY;
  float velocidadDesplazamientoY;
  Figura* figuraElemento;
public:
  Elemento(float posX, float posY, float velocidadDesplazamientoY,string spriteId);
  string getSpriteId();
  float generarNumeroAleatorio(float a, float b);
  int cargarImagen(string path, SDL_Renderer* renderer);
  void render(SDL_Renderer* renderer);
  float getPosX();
  float getPosY();
  float getVelocidadDesplazamientoY();
  void mover(float timeStep);
};
