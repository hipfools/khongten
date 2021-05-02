#include "headers/Sound.h"


#include <iostream>
#include <SDL.h>

Mix_Music* Sound::openingMusic;
Mix_Music* Sound::flagging;
Mix_Music* Sound::bombOff;
Mix_Music* Sound::winningMusic;
Mix_Music* Sound::losingMusic;
bool Sound::soundOn;

Sound::Sound() {
    initSound();

    openingMusic = Mix_LoadMUS("C:/Users/hiep/CLionProjects/MineSweeper/source/audio/opening.wav");
    initError(openingMusic);

    winningMusic = Mix_LoadMUS("C:/Users/hiep/CLionProjects/MineSweeper/source/audio/winning.wav");
    initError(winningMusic);

    losingMusic = Mix_LoadMUS("C:/Users/hiep/CLionProjects/MineSweeper/source/audio/losing.wav");
    initError(losingMusic);

    bombOff = Mix_LoadMUS("C:/Users/hiep/CLionProjects/MineSweeper/source/audio/bomb.wav");
    initError(bombOff);

    flagging = Mix_LoadMUS("C:/Users/hiep/CLionProjects/MineSweeper/source/audio/flagging.wav");
    initError(flagging);

    soundOn = true;
}

Sound::~Sound() {
    Mix_FreeMusic(openingMusic);
    Mix_FreeMusic(winningMusic);
    Mix_FreeMusic(losingMusic);
    Mix_FreeMusic(bombOff);
    Mix_FreeMusic(flagging);
    Mix_Quit();
}

void Sound::initSound() {

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void Sound::initError(Mix_Music* music) {
    if (music == nullptr) {
        std::cout << Mix_GetError() << std::endl;
    }
}

void Sound::play(Mix_Music *music) {
    if (music == openingMusic) {
        Mix_PlayMusic(music, -1);
    } else {
        Mix_PlayMusic(music, 0);
    }
}