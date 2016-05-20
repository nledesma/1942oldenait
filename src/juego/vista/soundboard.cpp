#include "soundboard.hpp"

SoundBoard::SoundBoard() { }
SoundBoard::~SoundBoard() { }

bool SoundBoard::inicializar() {
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        return false;
    return true;
}

void SoundBoard::cerrar() {
    Mix_HaltMusic();
    Mix_FreeChunk(this->disparo);
    Mix_FreeChunk(this->disparo_enemigo);
    Mix_FreeChunk(this->explosion);
    this->disparo = NULL;
    this->disparo_enemigo = NULL;
    this->explosion = NULL;
    Mix_FreeMusic(this->musica);
    this->musica = NULL;

    Mix_Quit();
}

bool SoundBoard::cargarSonidos() {
    bool success = true;
    string basePath = PATH_SOUND;

    string musicaPath = basePath + MUSICA;
    this->musica = Mix_LoadMUS(musicaPath.c_str());
    Mix_VolumeMusic(60);
    if( this->musica == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    string disparoPath = basePath + DISPARO;
    this->disparo = Mix_LoadWAV(disparoPath.c_str());
    Mix_VolumeChunk(this->disparo, 60);
    if( this->disparo == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    string disparoEnemigoPath = basePath + DISPARO_ENEMIGO;
    this->disparo_enemigo = Mix_LoadWAV(disparoEnemigoPath.c_str());
    Mix_VolumeChunk(this->disparo_enemigo, 60);
    if( this->disparo_enemigo == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    string explosionPath = basePath + EXPLOSION;
    this->explosion = Mix_LoadWAV(explosionPath.c_str());
    Mix_VolumeChunk(this->explosion, 60);
    if( this->explosion == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void SoundBoard::reproducirDisparo(void* THIS){
    SoundBoard *soundBoard = (SoundBoard *) THIS;
    Mix_PlayChannel( -1, soundBoard->disparo, 0 );

}
void SoundBoard::reproducirDisparoEnemigo(void* THIS){
    SoundBoard *soundBoard = (SoundBoard *) THIS;
    Mix_PlayChannel( -1, soundBoard->disparo_enemigo, 0 );

}
void SoundBoard::reproducirExplosion(void* THIS){
    SoundBoard *soundBoard = (SoundBoard *) THIS;
    Mix_PlayChannel( -1, soundBoard->explosion, 0 );
}
void SoundBoard::toggleMusica(void* THIS){
    SoundBoard *soundBoard = (SoundBoard *) THIS;
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( soundBoard->musica, -1 );
    }
    else
    {
        if( Mix_PausedMusic() == 1 )
        {
            Mix_ResumeMusic();
        }
        else
        {
            Mix_PauseMusic();
        }
    }
}