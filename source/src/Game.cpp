#include "headers/Game.h"
#include "headers/Replay.h"
#include "headers/Sound.h"

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>


SDL_Window* Game::window = nullptr;
int Game::widthOfGame = 0;
int Game::heightOfGame = 0;
int Game::numberOfMines = 0;
SDL_Renderer* Game::renderer = nullptr;
bool Game::isRunning = false;
TTF_Font* Game::font = nullptr;
bool Game::win = false;
bool Game::quit = false;

Game::Game() {}

Game::~Game() {}

void Game::Init(const char* windowTitle, const int& windowPosX, const int& windowPosY, const int& windowWidth, const int& windowHeight)
{

    //check SDL initialization
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        initError();
    }
    else
    {

        //create window
        window = SDL_CreateWindow(windowTitle, windowPosX, windowPosY, windowWidth, windowHeight,SDL_WINDOW_SHOWN);

        if (window == nullptr)
        {
            initError();
        }

        //create renderer
        SDL_Surface* icon = IMG_Load("C:/Users/hiep/CLionProjects/MineSweeper/source/image/icon.png");
        if (icon == nullptr) {
            std::cout << "Unable to load icon: " << SDL_GetError() << std::endl;
        }

        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//SDL_RENDERER_ACCELERATED : using only CPU to accelerate renderer

        if (renderer == nullptr)
        {
            initError();
        }


        isRunning = true; //allow game to create and print board in main.cpp
    }
    if (TTF_Init() != 0) //initializing SDL_ttf
    {
        initError();
    }
    else
    {
        font = TTF_OpenFont("C:/Users/hiep/CLionProjects/MineSweeper/source/font/arial.ttf", 100);
        if (font == nullptr)
        {
            initError();
        }
    }
    boardIsCreated = false;
}

void Game::createBoard()
{
    mineBoard = new  Board(); // board with mines, empty cells and values
    mineBoard->setValue(emptyCell);
    displayBoard = new Board(); // board on screen
    displayBoard->setValue(unopenedCell);

    mineBoard->random(); // place mines in customMines board

    openedCells = 0;
    flags = 0;
    nonBombBoxes = widthOfGame * heightOfGame - numberOfMines;
    boardIsCreated = true;
}

void Game::printBoard()
{
    texture = new Texture;
    desRect.w = squareSize;
    desRect.h = squareSize;

    SDL_SetWindowSize(window, widthOfGame * squareSize, heightOfGame * squareSize + 50);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    for (int i = 0; i < Game::widthOfGame; i++)
    {
        for (int j = 0; j < Game::heightOfGame; j++)
        {
            desRect.x = i * squareSize;
            desRect.y = j * squareSize;

            //draw all unopened cells
            SDL_RenderCopy(renderer, texture->getTexture(unopenedCell), nullptr, &desRect);
        }
    }

    updateFlagsLeft(); //show number of flags the first time

    SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        updateGame();
    }
}


void Game::updateGame()
{
    switch (event.type)
    {
        case SDL_QUIT: // player hit X
            isRunning = false;
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.y > heightOfGame * squareSize) { //mouse clicked in black space
                break;
            }
            // otherwise
            openedCellX = event.button.x / squareSize;
            openedCellY = event.button.y / squareSize;

            value = mineBoard->getValue(openedCellX, openedCellY);

            if (event.button.button == SDL_BUTTON_LEFT) //left click
            {
                if (displayBoard->getValue(openedCellX, openedCellY) == unopenedCell) // if cell has not been opened
                {
                    if (value == mine) // cell is bomb
                    {
                        Sound::play(Sound::bombOff);

                        for (int i = 0; i < Game::widthOfGame; i++)
                        {
                            for (int j = 0; j < Game::heightOfGame; j++)
                            {
                                if (mineBoard->getValue(i, j) == mine)
                                {
                                    desRect.x = i * squareSize;
                                    desRect.y = j * squareSize;
                                    // show all mines
                                    SDL_RenderCopy(renderer, texture->getTexture(mine), nullptr, &desRect);
                                }
                            }
                        }
                        isRunning = false;
                    }
                    else if (value != emptyCell) //cell is surrounded by bomb
                    {
                        displayBoard->updateValue(openedCellX, openedCellY, value); // update value board to values 1,2...

                        openedCells++;
                        desRect.x = openedCellX * squareSize;
                        desRect.y = openedCellY * squareSize;

                        //show cell with number of bombs around
                        SDL_RenderCopy(renderer, texture->getTexture(value), nullptr, &desRect);
                    }
                    else if (value == emptyCell)
                    {
                        displayBoard->updateValue(openedCellX, openedCellY, emptyCell);

                        openedCells++;
                        desRect.x = openedCellX * squareSize;
                        desRect.y = openedCellY * squareSize;

                        SDL_RenderCopy(renderer, texture->getTexture(emptyCell), nullptr, &desRect);
                        //openAround other empty cells around
                        openAround(openedCellX, openedCellY);
                    }
                }
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) //right click
            {
                if (displayBoard->getValue(openedCellX, openedCellY) == unopenedCell) // place flags
                {
                    Sound::play(Sound::flagging);

                    displayBoard->updateValue(openedCellX, openedCellY, flag);

                    flags++;
                    desRect.x = openedCellX * squareSize;
                    desRect.y = openedCellY * squareSize;

                    SDL_RenderCopy(renderer, texture->getTexture(flag), nullptr, &desRect);
                }
                else if (displayBoard->getValue(openedCellX, openedCellY) == flag) // remove flags
                {
                    Sound::play(Sound::flagging);

                    displayBoard->updateValue(openedCellX, openedCellY, unopenedCell);

                    flags--;
                    desRect.x = openedCellX * squareSize;
                    desRect.y = openedCellY * squareSize;

                    SDL_RenderCopy(renderer, texture->getTexture(unopenedCell), nullptr, &desRect);
                }

                updateFlagsLeft();
            }
            break;
        default:
            break;
    }
    if (openedCells == nonBombBoxes) // all non-bomb cells are opened
    {
        win = true;
        isRunning = false;
    }
}

void Game::render() //render updates
{
    SDL_RenderPresent(renderer);
    if (!isRunning)
    {
        SDL_Delay(DELAY_TIME);
    }
}

void Game::shutDown()
{
    if (!Replay::replay) //player doesn't want to play again
    {
        if (boardIsCreated)
        {
            delete mineBoard;
            delete displayBoard;
            delete texture;
        }

        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    else // delete previous game
    {
        widthOfGame = 0;
        heightOfGame = 0;
        numberOfMines = 0;
        isRunning = true;

        delete mineBoard;
        delete displayBoard;
        delete texture;

        boardIsCreated = false;
    }
}

void Game::initError()
{
    std::cout << "Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
}

void Game::openAround(const int& x, const int& y)
{
    int neighborX, neighborY;
    int neighborValue;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i != 0 || j != 0)
            {
                neighborX = x + i;
                neighborY = y + j;

                if (neighborX >= 0 && neighborX < widthOfGame && neighborY >= 0 && neighborY < heightOfGame)
                {
                    neighborValue = mineBoard->getValue(neighborX, neighborY);

                    if (displayBoard->getValue(neighborX, neighborY) == unopenedCell)
                    {
                        displayBoard->updateValue(neighborX, neighborY, neighborValue);

                        openedCells++;
                        desRect.x = neighborX * squareSize;
                        desRect.y = neighborY * squareSize;

                        SDL_RenderCopy(renderer, texture->getTexture(neighborValue), nullptr, &desRect);

                        if (mineBoard->getValue(neighborX, neighborY) == emptyCell) //if cell is empty, open around cell
                        {
                            openAround(neighborX, neighborY);
                        }
                    }
                }
            }
        }
    }
}


void Game::updateFlagsLeft() const {

    SDL_Texture* flagCount = Texture::loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/flagbox.png");

    SDL_Color White = {255, 255, 255};

    std::string numberOfFlags = "FLAG(S) LEFT : " + std::to_string(numberOfMines - flags);
    const char * c = numberOfFlags.c_str();

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, c, White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect;
    Message_rect.x = (widthOfGame * squareSize) / 2 - 70;
    Message_rect.y = (heightOfGame * squareSize) + 10;
    Message_rect.w = 140;
    Message_rect.h = 30;


    SDL_RenderCopy(renderer, flagCount, nullptr, &Message_rect);
    SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, Message, nullptr, &Message_rect);


    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    SDL_DestroyTexture(flagCount);
}