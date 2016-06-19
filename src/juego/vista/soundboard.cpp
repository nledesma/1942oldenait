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
    Mix_FreeChunk(this->r2d2Yeah);
    this->disparo = NULL;
    this->disparo_enemigo = NULL;
    this->explosion = NULL;
    this->loop = NULL;
    this->r2d2Yeah = NULL;
    Mix_FreeMusic(this->musica);
    this->musica = NULL;
    Mix_FreeMusic(this->musica);
    this->musicaMenu = NULL;
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
    if (this->r2d2Yeah != NULL)
        Mix_FreeChunk(this->r2d2Yeah);
    if (this->musica != NULL)
        Mix_FreeMusic(this->musica);
    if (this->musicaMenu != NULL)
        Mix_FreeMusic(this->musicaMenu);
    this->disparo = NULL;
    this->disparo_enemigo = NULL;
    this->explosion = NULL;
    this->musica = NULL;
    this->musicaMenu = NULL;
    this->r2d2Yeah = NULL;

    string basePath = PATH_SOUND;

    string musicaPath = basePath + MUSICA;
    this->musica = Mix_LoadMUS(musicaPath.c_str());
    Mix_VolumeMusic(60);
    if( this->musica == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    string musicaMenuPath = basePath + MUSICA_MENU;
    this->musicaMenu = Mix_LoadMUS(musicaMenuPath.c_str());
    Mix_VolumeMusic(60);
    if( this->musicaMenu == NULL )
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
    Mix_VolumeChunk(this->disparo_enemigo, 40);
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

    string r2d2Path = basePath + R2R2YEAH;
    this->r2d2Yeah = Mix_LoadWAV(r2d2Path.c_str());
    Mix_VolumeChunk(this->r2d2Yeah, 60);
    if( this->r2d2Yeah == NULL )
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

void SoundBoard::reproducirR2D2yeah(){
    Mix_PlayChannel( -1, this->r2d2Yeah, 0 );
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

void SoundBoard::toggleOnMusica(){
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
    }
}

void SoundBoard::toggleOffMusica(){
    if( Mix_PlayingMusic() == 1 ) {
        if( Mix_PausedMusic() == 0 )
        {
            Mix_PauseMusic();
        }
    }
}

void SoundBoard::toggleMusicaMenu(){
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( this->musicaMenu, -1 );
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

void SoundBoard::playMusica() {
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( this->musica, -1 );
    }
}

void SoundBoard::playMusicaMenu() {
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( this->musicaMenu, -1 );
    }
}


void SoundBoard::stopMusica() {
    if( Mix_PlayingMusic() == 1 )
    {
        Mix_HaltMusic();
    }
}
