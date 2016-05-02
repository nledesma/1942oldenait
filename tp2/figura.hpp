#ifndef Figura_HPP
#define Figura_HPP

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
		vector<int > COLOR_BASE;
		vector<int> COLOR_AZUL;
		vector<int> COLOR_ROJO;
		vector<int> COLOR_VERDE;
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

#endif
