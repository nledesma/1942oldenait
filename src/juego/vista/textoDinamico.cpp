#include "textoDinamico.hpp"
TextoDinamico::TextoDinamico(int tamanioFuente, SDL_Color color): Texto(tamanioFuente, color){

}

void TextoDinamico::cambiarTexto(Ventana* ventana){
    this->texto->loadFromRenderedText(this->caracteres, this->color, this->fuente, ventana->getVentanaRenderer());
}

void TextoDinamico::manejarEvento(SDL_Event evento, Ventana* ventana){
    bool renderText = false;
    if(evento.type == SDL_KEYDOWN){
		if(evento.key.keysym.sym == SDLK_BACKSPACE && caracteres.length() > 0){
            cout << "hola" << endl;
            //lop off character
			caracteres.pop_back();
			renderText = true;
		}

    }else if(evento.type == SDL_TEXTINPUT){
            cout << "entro" << endl;
			caracteres += evento.text.text;
			renderText = true;
	}
         cout << "hola2" << endl;


    //Rerender text if needed
    if(renderText){
        //cambiarTexto(ventana);
    	//Text is empty
        //Text is not empty
		if(caracteres!= "" ){
			//Render new text
            //cambiarTexto
			this->texto->loadFromRenderedText(caracteres.c_str(), this->color, this->fuente, ventana->getVentanaRenderer());
		}
		//Text is empty
		else{
			//Render space texture
			this->texto->loadFromRenderedText( " ", this->color, this->fuente, ventana->getVentanaRenderer());
		}
    }
    cout << "Alias: " << caracteres << endl;

}
