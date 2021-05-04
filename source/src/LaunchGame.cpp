#include "headers/LaunchGame.h"
#include "headers/Sound.h"

#include <iostream>
#include <SDL.h>


const int MAX_INPUT_LENGTH = 4;
const int MAX_WIDTH = 40;
const int MAX_HEIGHT = 40;

const Rect beginnerButton(145, 362, 315, 63);
const Rect intermediateButton(145, 451, 315, 63);
const Rect expertButton(145, 540, 315, 63);
const Rect customButton(145, 629, 315, 63);
const Rect widthInput(300, 560, 100, 30);
const Rect heightInput(300, 600, 100, 30);
const Rect mineInput(300, 640, 100, 30);
const Rect playButton(255, 730, 150, 60);
const Rect notifyBox(0, 690, 600, 30);
const Rect speakerButton(254, 757, 87, 68);


LaunchGame::LaunchGame()
{
    waitForInput = true;
    customW = "";
    customH = "";
    customMines = "";
    wClicked = false;
    hClicked = false;
    mClicked = false;
    chosenLine = Texture::loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/line_clicked.png");
    unchosenLine = Texture::loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/line_unclicked.png");
    emptyLine = Texture::loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/line_empty.png");
}

LaunchGame::~LaunchGame()
{
    SDL_DestroyTexture(chosenLine);
    SDL_DestroyTexture(unchosenLine);
    SDL_DestroyTexture(emptyLine);

    std::cout << "Screen is cleaned !!!..." << std::endl;
}

void LaunchGame::Start()
{
    bool _wait = true;

    //draw screen 1
    Texture::drawBackgroundTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/screen_1.png");

    //if sound is turned off, show speaker_off
    if (!Sound::soundOn) {
        SDL_Rect newSpeaker = {228, 731, 143, 120};
        SDL_Texture *soundOnImage = Texture::loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/speaker_off.png");
        SDL_RenderCopy(Game::renderer, soundOnImage, nullptr, &newSpeaker);
        SDL_RenderPresent(Game::renderer);
        SDL_DestroyTexture(soundOnImage);
    }

    while (_wait) { //waitForInput for action
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: //player hit x
                    SDL_Quit();
                    Game::isRunning = false;
                    Game::quit = true;
                    waitForInput = false;
                    _wait = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) { //left click
                        if (beginnerButton.clickedInsideRect(event.button.x, event.button.y)) {
                            Game::widthOfGame = 9;
                            Game::heightOfGame = 9;
                            Game::numberOfMines = 10;
                            Game::isRunning = true;
                            return;
                        } else if (intermediateButton.clickedInsideRect(event.button.x, event.button.y)) {
                            Game::widthOfGame = 16;
                            Game::heightOfGame = 16;
                            Game::numberOfMines = 40;
                            Game::isRunning = true;
                            return;
                        } else if (expertButton.clickedInsideRect(event.button.x, event.button.y)) {
                            Game::widthOfGame = 30;
                            Game::heightOfGame = 16;
                            Game::numberOfMines = 99;
                            Game::isRunning = true;
                            return;
                        } else if (customButton.clickedInsideRect(event.button.x, event.button.y)) {
                            customScreen(); //switch to custom screen

                            while (waitForInput) { //taking input
                                SDL_StartTextInput(); //allow text input

                                handleCustomInput();
                                renderCustomInput();

                                SDL_StopTextInput(); //close text input
                            }

                            cleanCustomInput();
                            return;
                        } else if (speakerButton.clickedInsideRect(event.button.x, event.button.y)) {
                            SDL_Rect newSpeaker = {228, 731, 143, 120};
                            SDL_Texture* soundOnImage;
                            if (Sound::soundOn) { //if sound is on, switch to sound off when speaker is clicked
                                Mix_VolumeMusic(0);
                                soundOnImage = Texture::loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/speaker_off.png");
                                SDL_RenderCopy(Game::renderer, soundOnImage, nullptr, &newSpeaker);
                                SDL_RenderPresent(Game::renderer);
                                Sound::soundOn = false;
                                SDL_DestroyTexture(soundOnImage);
                                break;
                            } else { //switch to sound on
                                Mix_VolumeMusic(30);
                                soundOnImage = Texture::loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/speaker_on.png");
                                SDL_RenderCopy(Game::renderer, soundOnImage, nullptr, &newSpeaker);
                                SDL_RenderPresent(Game::renderer);
                                Sound::soundOn = true;
                                SDL_DestroyTexture(soundOnImage);
                                break;
                            }

                        }
                    }
                default:
                    break;
            }
        }
    }
}


void LaunchGame::customScreen()
{
    //draw custom screen
    Texture::drawBackgroundTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/screen_custom.png");
}


void LaunchGame::handleCustomInput()
{
    while (SDL_PollEvent(&event))
    {
        updateInput();
    }
}

void LaunchGame::updateInput()
{
    switch (event.type)
    {
        case SDL_QUIT://hit x
            Game::isRunning = false;
            Game::quit = true;
            waitForInput = false; //stop taking input
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (widthInput.clickedInsideRect(event.button.x, event.button.y))
                {
                    wClicked = true;
                    hClicked = false;
                    mClicked = false;
                }
                else if (heightInput.clickedInsideRect(event.button.x, event.button.y))
                {
                    wClicked = false;
                    hClicked = true;
                    mClicked = false;
                }
                else if (mineInput.clickedInsideRect(event.button.x, event.button.y))
                {
                    wClicked = false;
                    hClicked = false;
                    mClicked = true;
                }
                // check if input is allowed when play button is clicked
                else if (playButton.clickedInsideRect(event.button.x, event.button.y))
                {
                    if (Game::widthOfGame == 0 || Game::heightOfGame == 0 || Game::numberOfMines == 0)
                    {
                        SDL_RenderCopy(Game::renderer, emptyLine, nullptr, notifyBox.getRect());
                        Texture::drawText("Please fill in all the boxes with valid numbers", notifyBox.getRect());
                    }
                    else if (Game::widthOfGame > MAX_WIDTH || Game::heightOfGame > MAX_HEIGHT)
                    {
                        SDL_RenderCopy(Game::renderer, emptyLine, nullptr, notifyBox.getRect());
                        Texture::drawText("The maximum number for width and height is 40",
                                          notifyBox.getRect());
                    }
                    else if (Game::widthOfGame * Game::heightOfGame < Game::numberOfMines)
                    {
                        SDL_RenderCopy(Game::renderer, emptyLine, nullptr, notifyBox.getRect());
                        Texture::drawText("Too many mines. Try again with a smaller number", notifyBox.getRect());
                    }
                    else
                    {
                        waitForInput = false; // input is allowed
                    }
                }
                else
                {
                    wClicked = false;
                    hClicked = false;
                    mClicked = false;
                }
            }
            break;
        case SDL_TEXTINPUT: //handling input
            inputChar = event.text.text[0];

            if (inputChar >= '0' && inputChar <= '9') //only allow numbers
            {
                if (wClicked && customW.length() < MAX_INPUT_LENGTH)
                {
                    customW += event.text.text;
                    Game::widthOfGame *= 10;
                    Game::widthOfGame += (int)(inputChar - 48);
                }
                else if (hClicked && customH.length() < MAX_INPUT_LENGTH)
                {
                    customH += event.text.text;
                    Game::heightOfGame *= 10;
                    Game::heightOfGame += (int)(inputChar - 48);
                }
                else if (mClicked && customMines.length() < MAX_INPUT_LENGTH)
                {
                    customMines += event.text.text;
                    Game::numberOfMines *= 10;
                    Game::numberOfMines += (int)(inputChar - 48);
                }
            }
            break;
        case SDL_KEYDOWN: //handling keyboard
            if (wClicked && event.key.keysym.sym == SDLK_BACKSPACE && customW.length() > 0) //player delete customW
            {
                customW.pop_back();
                Game::widthOfGame /= 10;
            }
            else if (hClicked && event.key.keysym.sym == SDLK_BACKSPACE && customH.length() > 0) //player delete customH
            {
                customH.pop_back();
                Game::heightOfGame /= 10;
            }
            else if (mClicked && event.key.keysym.sym == SDLK_BACKSPACE && customMines.length() > 0) //player delete customMines
            {
                customMines.pop_back();
                Game::numberOfMines /= 10;
            }
            else if (event.key.keysym.sym == SDLK_TAB || event.key.keysym.sym == SDLK_DOWN) //tab or down key is pressed
            {
                if (wClicked)
                {
                    wClicked = false;
                    hClicked = true;
                    mClicked = false;
                }
                else if (hClicked)
                {
                    wClicked = false;
                    hClicked = false;
                    mClicked = true;
                }
                else if (mClicked)
                {
                    wClicked = true;
                    hClicked = false;
                    mClicked = false;
                }
            }
            else if (event.key.keysym.sym == SDLK_UP) //up key is pressed
            {
                if (wClicked)
                {
                    wClicked = false;
                    hClicked = false;
                    mClicked = true;
                }
                else if (hClicked)
                {
                    wClicked = true;
                    hClicked = false;
                    mClicked = false;
                }
                else if (mClicked)
                {
                    wClicked = false;
                    hClicked = true;
                    mClicked = false;
                }
            }
            break;
        default:
            break;
    }
}

void LaunchGame::renderCustomInput()
{
    if (wClicked) //when customW box is clicked
    {
        Texture::drawTexture(chosenLine, widthInput.x - 1, widthInput.y - 1);
        SDL_RenderCopy(Game::renderer, emptyLine, nullptr, widthInput.getRect()); //update delete
        Texture::drawText(customW, widthInput.getRect());
    }
    else //when customW box is not clicked
    {
        Texture::drawTexture(unchosenLine, widthInput.x - 1, widthInput.y - 1);
    }
    if (hClicked)
    {
        Texture::drawTexture(chosenLine, heightInput.x - 1, heightInput.y - 1);
        SDL_RenderCopy(Game::renderer, emptyLine, nullptr, heightInput.getRect());
        Texture::drawText(customH, heightInput.getRect());
    }
    else
    {
        Texture::drawTexture(unchosenLine, heightInput.x - 1, heightInput.y - 1);
    }
    if (mClicked)
    {
        Texture::drawTexture(chosenLine, mineInput.x - 1, mineInput.y - 1);
        SDL_RenderCopy(Game::renderer, emptyLine, nullptr, mineInput.getRect());
        Texture::drawText(customMines, mineInput.getRect());
    }
    else
    {
        Texture::drawTexture(unchosenLine, mineInput.x - 1, mineInput.y - 1);
    }
}

void LaunchGame::cleanCustomInput()
{
    waitForInput = true;
    customW = "";
    customH = "";
    customMines = "";
    wClicked = false;
    hClicked = false;
    mClicked = false;
}