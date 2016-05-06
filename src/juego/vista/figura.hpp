#ifndef INC_1942OLDENAIT_FIGURA_HPP
#define INC_1942OLDENAIT_FIGURA_HPP

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>

using namespace std;

class Figura{
private:
    //Textura de la figura
    SDL_Texture* textura;
    //Dimensiones de la figura
    int mWidth;
    int mHeight;
public:
    static const color_base = {255,255,255};
    static const color_azul = {100,100,255};
    static const color_rojo = {255,100,100};
    static const color_verde = {100,255,100};
    //Constructor
    Figura();
    //Destructor
    ~Figura();
    //Carga la imagen desde el path especificado, utilizando el renderer pasado por parámetro
    bool loadFromFile(string path, SDL_Renderer* renderer, int color = 0);
    //Libera la memoria de la textura
    void free();
    //Renderiza la figura en el punto (x,y)
    void render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);
    //Getters
    int getWidth();
    int getHeight();
};
#endif //INC_1942OLDENAIT_FIGURA_HPP
