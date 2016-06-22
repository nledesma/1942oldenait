#include "figura.hpp"
#include "ventana.hpp"

// Vectores

Figura::Figura(){
    //Initialize
    this->textura = NULL;
    this->mWidth = 0;
    this->mHeight = 0;
}

Figura::~Figura(){
    free();
}

bool Figura::loadFromFilePNG(SDL_Renderer* renderer, string path){
	free();
	SDL_Texture* newTexture = NULL;
    string basePath = PATH_IMG;
    string fullPath = basePath + path + ".png";
	SDL_Surface* loadedSurface = IMG_Load(fullPath.c_str());
	if(loadedSurface == NULL){
		cout << "SDL_image Error:" << IMG_GetError() << endl;
	}
	else{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == NULL){
			cout << "SDL Error:" << SDL_GetError() << endl;
		}
		else{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	textura = newTexture;
	return textura != NULL;
}

bool Figura::loadFromFile(string path, SDL_Renderer* renderer, int color){
    //Si existe una textura cargada de antes, se libera la memoria asociada a esa textura.
    free();
    //Se declara la textura que va a cargarse en la figura.
    SDL_Texture* nuevaTextura = NULL;
    //Se carga la imagen desde el path especificado.
    string basePath = PATH_IMG;
    string fullPath = basePath + path + ".bmp";
    SDL_Surface* loadedSurface = SDL_LoadBMP(fullPath.c_str());
    if(loadedSurface == NULL){
        Logger::instance()->logError(errno, "No se ha podido cargar la imagen" + path);
        //cout << "No se ha podido cargar la imagen " + path << IMG_GetError() << endl;
        return false;
    }else{
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Se crea la textura a partir de la SDL_Surface
        nuevaTextura = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(nuevaTextura == NULL){
          Logger::instance()->logError(errno, "No se ha podido crear la textura" + path);
            //cout <<  "No se ha podido crear la textura " +  path <<  SDL_GetError() << endl;
            return false;
        }
        else{
            //Se obtienen las dimensiones de la superficie, y se setean a la figura
            switch (color) {
                case BASE:
                    SDL_SetTextureColorMod( nuevaTextura, (Uint8) COLOR_BASE_R, (Uint8) COLOR_BASE_G, (Uint8) COLOR_BASE_B );
                    break;
                case AZUL:
                    SDL_SetTextureColorMod( nuevaTextura, (Uint8) COLOR_AZUL_R, (Uint8)COLOR_AZUL_G, (Uint8)COLOR_AZUL_B );
                    break;
                case ROJO:
                    SDL_SetTextureColorMod( nuevaTextura, (Uint8) COLOR_ROJO_R, (Uint8)COLOR_ROJO_G, (Uint8)COLOR_ROJO_B );
                    break;
                case VERDE:
                    SDL_SetTextureColorMod( nuevaTextura, (Uint8) COLOR_VERDE_R, (Uint8) COLOR_VERDE_G, (Uint8) COLOR_VERDE_B );
                    break;
                case AMARILLO:
                    SDL_SetTextureColorMod( nuevaTextura, (Uint8) COLOR_AMARILLO_R, (Uint8)COLOR_AMARILLO_G, (Uint8)COLOR_AMARILLO_B );
                    break;
                case VIOLETA:
                    SDL_SetTextureColorMod( nuevaTextura, (Uint8) COLOR_VIOLETA_R, (Uint8) COLOR_VIOLETA_G, (Uint8) COLOR_VIOLETA_B );
                    break;
                default:
                    SDL_SetTextureColorMod( nuevaTextura, (Uint8) COLOR_BASE_R, (Uint8) COLOR_BASE_G, (Uint8) COLOR_BASE_B );
            }
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
    if(this->textura != NULL){
        SDL_DestroyTexture(this->textura);
        this->textura = NULL;
        this->mWidth = 0;
        this->mHeight = 0;
    }
}

void Figura::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip){
    SDL_Rect renderQuad = { x, y, this->mWidth, this->mHeight };

    if(clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, this->textura, clip, &renderQuad);
}

bool Figura::loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer* renderer){
    // Liberamos texturas preexistentes.
	free();
	// Se renderiza una superficie auxiliar con el texto.
	SDL_Surface* textSurface = TTF_RenderUTF8_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL) {
		cout << "No se ha podido renderizar el texto sobre la superficie. SDL_ttf Error: " << TTF_GetError() << endl;
	} else {
		// Se crea la textura a partir de la superficie.
        textura = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (textura == NULL) {
			cout << "No se ha podido crear la textura a partir de la superficie. SDL Error: " << SDL_GetError() << endl;
		} else {
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		// Se libera la superficie auxiliar.
		SDL_FreeSurface(textSurface);
	}

	return textura != NULL;
}

void Figura::renderMenu(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	// Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	// Set clip rendering dimensions
	if(clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	// Render to screen
	SDL_RenderCopyEx(renderer, textura, clip, &renderQuad, angle, center, flip);
}


int Figura::getWidth(){
    return mWidth;
}

int Figura::getHeight(){
    return mHeight;
}
