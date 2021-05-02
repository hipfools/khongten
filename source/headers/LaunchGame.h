#ifndef MINESWEEPER_LAUNCHGAME_H
#define MINESWEEPER_LAUNCHGAME_H

#include <string>
#include <SDL_image.h>

#include "Game.h"
#include "Rect.h"


class LaunchGame
{

public:
    LaunchGame();
    ~LaunchGame();
    void Start();
    void customScreen();
    void handleCustomInput();
    void renderCustomInput();
    void cleanCustomInput();

private:
    SDL_Event event{};
    bool waitForInput;
    std::string customW, customH, customMines; // custom input in string to render
    bool wClicked, hClicked, mClicked; // which box is clicked
    SDL_Texture* chosenLine;
    SDL_Texture* unchosenLine;
    SDL_Texture* emptyLine;
    char inputChar{};

    void updateInput();
};
#endif //MINESWEEPER_LAUNCHGAME_H
