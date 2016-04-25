#include "contenedorTextura.hpp"
#include "ventana.hpp"
ContenedorTextura::ContenedorTextura(){
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	gRenderer = NULL;
}

ContenedorTextura::~ContenedorTextura(){
	//Deallocate
	free();
}

bool ContenedorTextura::loadFromFile(string path, SDL_Renderer* renderer){
	cout << "ESTO ES EL RENDERER " << renderer << endl; 
	this->gRenderer = renderer;
	//Get rid of preexisting texture
	free();
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL){
		cout << "No se ha podido cargar la imagen " + path << IMG_GetError() << endl;
	}	else{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL){
			cout <<  "No se ha podido crear la textura " +  path <<  SDL_GetError() << endl;
		}
		else{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	//Return success
	return newTexture;
}

void ContenedorTextura::free(){
	//Free texture if it exists
	if(mTexture != NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void ContenedorTextura::render(int x, int y){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int ContenedorTextura::getWidth()
{
	return mWidth;
}

int ContenedorTextura::getHeight()
{
	return mHeight;
}

SDL_Renderer* ContenedorTextura::getRenderer(){
	return this->gRenderer;
}
