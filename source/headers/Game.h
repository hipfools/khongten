#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "Board.h"
#include "Texture.h"

const int squareSize = 25;
const int unopenedCell = -1;
const int emptyCell = 0;
const int mine = 9;
const int flag = -2;
const int DELAY_TIME = 2000;

class Game {

public:
    static SDL_Window* window;
    static int widthOfGame;
    static int heightOfGame;
    static int numberOfMines;
    static SDL_Renderer* renderer;
    static bool isRunning; //control game state
    static TTF_Font* font;
    static bool win;
    static bool quit;

    Game();
    ~Game();

    void Init(const char* windowTitle, const int& windowPosX, const int& windowPosY, const int& windowWidth, const int& windowHeight);
    void createBoard();
    void printBoard();
    void handleEvents();
    void render();
    void shutDown();
    static void initError();
    void updateFlagsLeft() const;
    void printBackButton() const;

private:
    SDL_Event event;
    SDL_Rect desRect; //SDL_Rect for cells
    Texture* texture;

    Board* mineBoard;
    Board* displayBoard;

    int openedCellX;
    int openedCellY;
    int value;
    int openedCells;
    int flags;
    int nonBombBoxes;
    bool boardIsCreated;

    void updateGame();
    void openAround(const int& x, const int& y);
};

#endif //MINESWEEPER_GAME_H
