#include "ventana.hpp"

Ventana::Ventana(int ancho, int alto) {
    this->ancho = ancho;
    this->alto = alto;
    this->fondo = new Figura();
}

int Ventana::iniciar() {
    int success = 1;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::instance()->logError(errno, "Hubo un error al iniciar la ventana");
        cout << "Hubo un error para iniciar la ventana: " << SDL_GetError() << endl;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        //Se crea la ventana
        sdlWindow = SDL_CreateWindow("1942", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->ancho, this->alto,
                                     SDL_WINDOW_SHOWN);
        if (sdlWindow == NULL) {
            Logger::instance()->logError(errno, "Hubo un error al crear la ventana");
            cout << "Hubo un error al crear la ventana: " << SDL_GetError() << endl;
        }
    }
    gVentanaRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gVentanaRenderer == NULL) {
        cout << "No se pudo crear el renderer de la ventana, SDL Error: " << SDL_GetError() << endl;
    } else {
        SDL_SetRenderDrawColor(gVentanaRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    //Initialize SDL_ttf
    if(TTF_Init() == -1){
        cout << "SDL_ttf could not initialize! SDL_ttf Error:" << TTF_GetError() << endl;
        success = false;
    }

    return success;
}

void Ventana::cerrar() {
    this->fondo->free();
    SDL_DestroyRenderer(gVentanaRenderer);
    SDL_DestroyWindow(sdlWindow);
    gVentanaRenderer = NULL;
    sdlWindow = NULL;
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

int Ventana::getAncho() {
    return this->ancho;
}

void Ventana::setAncho(int ancho) {
    this->ancho = ancho;
}

int Ventana::getAlto() {
    return this->alto;
}

void Ventana::setAlto(int alto) {
    this->alto = alto;
}

SDL_Renderer *Ventana::getVentanaRenderer() {
    return this->gVentanaRenderer;
}

SDL_Window *Ventana::getSdlWindow() {
    return this->sdlWindow;
}
//TODO

void Ventana::renderizarFondo() {
    this->fondo->renderMenu(this->getVentanaRenderer(), 0, 0, NULL, 0, NULL, (SDL_RendererFlip)NULL);
}

Figura* Ventana::getFondo(){
    return this->fondo;
}

void Ventana::cargarFondo(){
    if(!this->fondo->loadFromFilePNG(this->getVentanaRenderer(), "../../resources/img/espacio.png")){
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }
}

void Ventana::limpiar(){
  SDL_SetRenderDrawColor(this->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(this->getVentanaRenderer());
}
