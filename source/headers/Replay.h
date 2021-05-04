#ifndef MINESWEEPER_REPLAY_H
#define MINESWEEPER_REPLAY_H

#include <SDL.h>
#include "Rect.h"

class Replay
{
public:
    static bool replay;

    Replay();
    ~Replay();

    void endScreen(const int& winW,const int& winH);

private:
    SDL_Event event;
    bool waitForResponse;
};

#endif //MINESWEEPER_REPLAY_H
