#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

using namespace std;

class Temporizador{
public:

  Temporizador();

  void comenzar();
  void detener();
  void pausar();
  void reanudar();

  Uint32 getTicks();

  bool estaIniciado();
  bool estaPausado();

private:

  Uint32 ticksIniciales;

  Uint32 pausarTicks;

  bool pausado;
  bool iniciado;

};
