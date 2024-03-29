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
#define MUSICA_MENU "empire_strikes_back2.wav"
#define LOOP "falconFly.wav"
#define R2R2YEAH "R2D2-yeah.wav"


using namespace std;

class SoundBoard {
private:
    Mix_Music* musica = NULL;
    Mix_Music* musicaMenu = NULL;
    Mix_Chunk* disparo = NULL;
    Mix_Chunk* disparo_enemigo = NULL;
    Mix_Chunk* explosion = NULL;
    Mix_Chunk* loop = NULL;
    Mix_Chunk* r2d2Yeah = NULL;
    bool reproduciendoMusica;
public:
    SoundBoard();
    ~SoundBoard();
    bool inicializar();
    bool cargarSonidos();
    void reproducirDisparo();
    void reproducirDisparoEnemigo();
    void reproducirExplosion();
    void reproducirLoop();
    void reproducirR2D2yeah();
    void toggleMusica();
    void toggleOnMusica();
    void toggleOffMusica();
    void playMusica();
    void toggleMusicaMenu();
    void playMusicaMenu();
    void stopMusica();
    void cerrar();
};


#endif //SOUNDBOARD_HPP
