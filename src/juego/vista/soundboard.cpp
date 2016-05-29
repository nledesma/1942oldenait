#include "soundboard.hpp"

SoundBoard::SoundBoard() { }
SoundBoard::~SoundBoard() {
    this->cerrar();
}

bool SoundBoard::inicializar() {
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        return false;
    }
    Mix_AllocateChannels(20);
    return true;
}

void SoundBoard::cerrar() {
    Mix_HaltMusic();
    Mix_FreeChunk(this->disparo);
    Mix_FreeChunk(this->disparo_enemigo);
    Mix_FreeChunk(this->explosion);
    Mix_FreeChunk(this->loop);
    this->disparo = NULL;
    this->disparo_enemigo = NULL;
    this->explosion = NULL;
    this->loop = NULL;
    Mix_FreeMusic(this->musica);
    this->musica = NULL;
    Mix_Quit();
}

bool SoundBoard::cargarSonidos() {
    bool success = true;
    if (this->disparo != NULL)
        Mix_FreeChunk(this->disparo);
    if (this->disparo_enemigo != NULL)
        Mix_FreeChunk(this->disparo_enemigo);
    if (this->explosion != NULL)
        Mix_FreeChunk(this->explosion);
    if (this->loop != NULL)
        Mix_FreeChunk(this->loop);
    if (this->musica != NULL)
        Mix_FreeMusic(this->musica);
    this->disparo = NULL;
    this->disparo_enemigo = NULL;
    this->explosion = NULL;
    this->musica = NULL;

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

    string loopPath = basePath + LOOP;
    this->loop = Mix_LoadWAV(loopPath.c_str());
    Mix_VolumeChunk(this->loop, 60);
    if( this->loop == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void SoundBoard::reproducirDisparo(){
    Mix_PlayChannel( -1, this->disparo, 0 );
}
void SoundBoard::reproducirDisparoEnemigo(){
    Mix_PlayChannel( -1, this->disparo_enemigo, 0 );
}
void SoundBoard::reproducirExplosion(){
    Mix_PlayChannel( 1, this->explosion, 0 );
}
void SoundBoard::reproducirLoop(){
    Mix_PlayChannel( -1, this->loop, 0 );
}
void SoundBoard::toggleMusica(){
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( this->musica, -1 );
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