#ifndef SOUNDBOARD_HPP
#define SOUNDBOARD_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>

#define PATH_SOUND "../../resources/sound/"
#define DISPARO "laser.wav"
#define DISPARO_ENEMIGO "tieLaser.wav"
#define EXPLOSION "explosion.wav"
#define MUSICA "empire_strikes_back.wav"

using namespace std;

class SoundBoard {
private:
    Mix_Music* musica = NULL;
    Mix_Chunk* disparo = NULL;
    Mix_Chunk* disparo_enemigo = NULL;
    Mix_Chunk* explosion = NULL;
    bool reproduciendoMusica;
public:
    SoundBoard();
    ~SoundBoard();
    bool inicializar();
    bool cargarSonidos();
    static void reproducirDisparo(void* THIS);
    static void reproducirDisparoEnemigo(void* THIS);
    static void reproducirExplosion(void* THIS);
    static void toggleMusica(void* THIS);
    void cerrar();
};


#endif //SOUNDBOARD_HPP
