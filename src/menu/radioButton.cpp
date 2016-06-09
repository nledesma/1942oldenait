#include "radioButton.hpp"

RadioButton::RadioButton(SDL_Renderer* renderer){
    this->figuraRadioButton = new Figura();
    this->seleccionado = false;
    cargarSprite(renderer);
    setearSprites();
}

RadioButton::~RadioButton(){}
int RadioButton::getSprite(){
    if(seleccionado){
        return 1;
    }else{
        return 0;
    }
}

void RadioButton::cargarSprite(SDL_Renderer* renderer){
    this->figuraRadioButton->loadFromFilePNG(renderer, "SpritesBotones/radioButton");
}

void RadioButton::setearSprites(){
    //Radio Button no seleccionado
    this->spritesAnimacion[0].x = 0;
    this->spritesAnimacion[0].y = 0;
    this->spritesAnimacion[0].w = RADIO_BUTTON_ANCHO;
    this->spritesAnimacion[0].h = RADIO_BUTTON_ALTO;

    this->spritesAnimacion[1].x = RADIO_BUTTON_ANCHO;
    this->spritesAnimacion[1].y = 0;
    this->spritesAnimacion[1].w = RADIO_BUTTON_ANCHO;
    this->spritesAnimacion[1].h = RADIO_BUTTON_ALTO;
}

void RadioButton::renderizar(int x, int y, SDL_Renderer* renderer){
    this->figuraRadioButton->render(x, y, renderer, &spritesAnimacion[getSprite()]);
}

void RadioButton::seleccionar(){
    seleccionado = true;
}

void RadioButton::deseleccionar(){
    seleccionado = false;
}

int RadioButton::getRadio(){
    return RADIO_BOTON;
}
