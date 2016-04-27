#include <iostream>
#include <time.h>
#include <cmath>
#include <SDL2/SDL.h>
#include "figura.hpp"

using namespace std;
class Elemento{
private:
  int spriteId;
  float posX;
  float posY;
  Figura* figuraElemento;
public:
  Elemento(float posX, float posY);
  int getSpriteId();
  float generarNumeroAleatorio(float a, float b);
  int cargarImagen(string path, SDL_Renderer* renderer);
  void render(SDL_Renderer* renderer);
};
