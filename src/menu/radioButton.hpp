#ifndef RADIOBUTTON_HPP
#define RADIOBUTTON_HPP
#include "../juego/vista/texto.hpp"
class RadioButton{
    private:
        Figura* figuraRadioButton;
        SDL_Rect spritesAnimacion[2];
        bool seleccionado;
    public:
        RadioButton(SDL_Renderer* renderer);
        ~RadioButton();
        const int RADIO_BUTTON_ANCHO = 36;
		const int RADIO_BUTTON_ALTO = 36;
        int getSprite();
        void cargarSprite(SDL_Renderer* renderer);
        void setearSprites();
        void renderizar(int x, int y, SDL_Renderer* renderer);
        void manejarEvento();

};
#endif
