#include "figura.hpp"
#include "ventana.hpp"
Figura::Figura(){
	//Initialize
	this->textura = NULL;
	this->mWidth = 0;
	this->mHeight = 0;
}

Figura::~Figura(){
	//Deallocate
	free();
}

bool Figura::loadFromFile(string path, SDL_Renderer* renderer){
	cout << "ESTO ES EL RENDERER " << renderer << endl;
	//Si existe una textura cargada de antes, se libera la memoria asociada a esa textura.
	free();
	//Se declara la textura que va a cargarse en la figura.
	SDL_Texture* nuevaTextura = NULL;
	//Se carga la imagen desde el path especificado.
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface == NULL){
		cout << "No se ha podido cargar la imagen " + path << IMG_GetError() << endl;
		return false;
	}else{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		//Se crea la textura a partir de la SDL_Surface
    nuevaTextura = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(nuevaTextura == NULL){
			cout <<  "No se ha podido crear la textura " +  path <<  SDL_GetError() << endl;
			return false;
		}
		else{
			//Se obtienen las dimensiones de la superficie, y se setean a la figura
			this->mWidth = loadedSurface->w;
			this->mHeight = loadedSurface->h;
		}
		//Se liberan los recursos de la SDL_Surface, dado que ya no se usan.
		SDL_FreeSurface(loadedSurface);
	}
	this->textura = nuevaTextura;
	//Se retorna un valor de éxito
	return textura!=NULL;
}

void Figura::free(){
	//Se libera la textura si es necesario, y se redefinen los atributos por default.
	if(textura != NULL){
		SDL_DestroyTexture(this->textura);
		this->textura = NULL;
		this->mWidth = 0;
		this->mHeight = 0;
	}
}

void Figura::render(int x, int y, SDL_Renderer* renderer){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	SDL_RenderCopy(renderer, textura, NULL, &renderQuad);
}

int Figura::getWidth()
{
	return mWidth;
}

int Figura::getHeight()
{
	return mHeight;
}
