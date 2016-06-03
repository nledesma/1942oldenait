#ifndef INC_1942OLDENAIT_FIGURA_HPP
#define INC_1942OLDENAIT_FIGURA_HPP

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include <string>
#include "../../accesorios/codigo.hpp"
#include "../../logger/logger.hpp"

#define COLOR_BASE_R 255
#define COLOR_BASE_G 255
#define COLOR_BASE_B 255

#define COLOR_AZUL_R 100
#define COLOR_AZUL_G 100
#define COLOR_AZUL_B 255

#define COLOR_ROJO_R 255
#define COLOR_ROJO_G 100
#define COLOR_ROJO_B 100

#define COLOR_VERDE_R 100
#define COLOR_VERDE_G 255
#define COLOR_VERDE_B 100

#define PATH_IMG "../../resources/img/"

using namespace std;

class Figura{
private:
    //Textura de la figura
    SDL_Texture* textura;
    //Dimensiones de la figura
    int mWidth;
    int mHeight;
public:
    //Constructor
    Figura();
    //Destructor
    ~Figura();
    //Carga la imagen desde el path especificado, utilizando el renderer pasado por parámetro
    bool loadFromFile(string path, SDL_Renderer* renderer, int color = BASE);
    bool loadFromFilePNG(SDL_Renderer* renderer, string path);
    //Libera la memoria de la textura
    void free();
    //Renderiza la figura en el punto (x,y)
    void render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);

    bool loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer* renderer);
    void renderMenu(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
    //Getters
    int getWidth();
    int getHeight();
};
#endif //INC_1942OLDENAIT_FIGURA_HPP
