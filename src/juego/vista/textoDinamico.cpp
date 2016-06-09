#include "textoDinamico.hpp"

TextoDinamico::TextoDinamico(int tamanioFuente, SDL_Color color, string fuente, Ventana * ventana): Texto(tamanioFuente, color, fuente, ventana){

}

void TextoDinamico::recargarTexto() {
    if(caracteres != "") {
        // Si hay caracteres se carga el nuevo texto.
        this->cargarFuente(caracteres);
    } else {
        // Si no, se carga un espacio.
        this->cargarFuente(" ");
    }
}

// Esta función se utiliza para cambiar el texto sin eventos. Ej: puntaje.
void TextoDinamico::cambiarTexto(string textoNuevo) {
    if (caracteres != textoNuevo) {
        caracteres.assign(textoNuevo);
        recargarTexto();
    }
}

void TextoDinamico::manejarEvento(SDL_Event evento){
    bool cambiaElTexto = false;

    if(evento.type == SDL_KEYDOWN){
        // Para borrar.
		if(evento.key.keysym.sym == SDLK_BACKSPACE && caracteres.length() > 0) {
			caracteres.pop_back();
			cambiaElTexto = true;
		}
    } else if(evento.type == SDL_TEXTINPUT) {
        // Para ingreso de texto.
		caracteres += evento.text.text;
		cambiaElTexto = true;
	}

    if (cambiaElTexto) recargarTexto();
}

string TextoDinamico::getTexto() {
    return caracteres;
}
