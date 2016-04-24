#ifndef CONTENEDORTEXTURA_HPP
#define CONTENEDORTEXTURA_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class ContenedorTextura{
	public:
		//Initializes variables
		ContenedorTextura();
		//Deallocates memory
		~ContenedorTextura();
		//Loads image at specified path
		bool loadFromFile(string path);
		//Deallocates texture
		void free();
		//Renders texture at given point
		void render( int x, int y );
		//Gets image dimensions
		int getWidth();
		int getHeight();
	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
    SDL_Renderer* gRenderer;
		//Image dimensions
		int mWidth;
		int mHeight;
};
#endif
