#include "figura.hpp"
#include "ventana.hpp"

// Vectores

const vector<int> color_base = {255,255,255};
const vector<int> color_azul = {100,100,255};
const vector<int> color_rojo = {255,100,100};
const vector<int> color_verde = {100,255,100};

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

bool Figura::loadFromFile(string path, SDL_Renderer* renderer, int color){
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
            switch (color) {
                case BASE:
                    SDL_SetTextureColorMod( nuevaTextura, Figura::color_base[0], Figura::color_base[1], Figura::color_base[2] );
                    break;
                case AZUL:
                    SDL_SetTextureColorMod( nuevaTextura, Figura::color_azul[0], Figura::color_azul[1], Figura::color_azul[2] );
                    break;
                case ROJO:
                    SDL_SetTextureColorMod( nuevaTextura, Figura::color_rojo[0], Figura::color_rojo[1], Figura::color_rojo[2] );
                    break;
                case VERDE:
                    SDL_SetTextureColorMod( nuevaTextura, Figura::color_verde[0], Figura::color_verde[1], Figura::color_verde[2] );
                    break;
                default:
                    SDL_SetTextureColorMod( nuevaTextura, Figura::color_base[0], Figura::color_base[1], Figura::color_base[2] );
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
    if(textura != NULL){
        SDL_DestroyTexture(this->textura);
        this->textura = NULL;
        this->mWidth = 0;
        this->mHeight = 0;
    }
}

void Figura::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip){
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, this->mWidth, this->mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy( renderer, this->textura, clip, &renderQuad );
}

int Figura::getWidth()
{
    return mWidth;
}

int Figura::getHeight()
{
    return mHeight;
}
