#ifndef MINESWEEPER_SOUND_H
#define MINESWEEPER_SOUND_H
#include <SDL_mixer.h>

class Sound {
public:
    static Mix_Music* openingMusic;//found
    static Mix_Music* winningMusic;//found
    static Mix_Music* losingMusic;//found
    static Mix_Music* bombOff;//found
    static Mix_Music* flagging;
    static bool soundOn;

    Sound();
    ~Sound();

    static void initSound();
    static void initError(Mix_Music* music);
    static void play(Mix_Music* music);
};
#endif //MINESWEEPER_SOUND_H
