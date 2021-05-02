#include "headers/Replay.h"
#include "headers/Texture.h"
#include "headers/Game.h"
#include "headers/Sound.h"

#include <SDL.h>

const Rect yesButton(210, 614, 79, 53);
const Rect noButton(316, 614, 79, 53);
bool Replay::replay;

Replay::Replay()
{
}


Replay::~Replay()
{
}

void Replay::endScreen(const int& winW, const int& winH)
{
    if (!Game::quit)
    {
        waitForResponse = true;

        SDL_SetWindowSize(Game::window, winW, winH);
        SDL_SetWindowPosition(Game::window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        if (Game::win) // player wins
        {
            Sound::play(Sound::winningMusic);
            Texture::drawBackgroundTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/screen_win.png");
        }
        else // player loses
        {
            Sound::play(Sound::losingMusic);
            Texture::drawBackgroundTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/screen_lose.png");
        }

        while (waitForResponse)
        {
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        replay = false;
                        waitForResponse = false;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (yesButton.clickedInsideRect(event.button.x, event.button.y))
                        {
                            replay = true;
                            waitForResponse = false;
                        }
                        else if (noButton.clickedInsideRect(event.button.x, event.button.y))
                        {
                            replay = false;
                            waitForResponse = false;
                        }
                    default:
                        break;
                }
            }
        }
    }
    else //player quit
    {
        replay = false;
    }
}