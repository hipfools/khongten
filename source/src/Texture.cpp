#include "headers/Texture.h"
#include "headers/Game.h"

Texture::Texture()
{
    unopenedCell = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/square_unopened.png");
    emptyCell = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/square_empty.png");
    flag = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/flag.png");
    mine = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/square_mine.png");
    num1 = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/num_1.png");
    num2 = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/num_2.png");
    num3 = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/num_3.png");
    num4 = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/num_4.png");
    num5 = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/num_5.png");
    num6 = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/num_6.png");
    num7 = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/num_7.png");
    num8 = loadTexture("C:/Users/hiep/CLionProjects/MineSweeper/source/image/num_8.png");
}

Texture::~Texture()
{
    SDL_DestroyTexture(unopenedCell);
    SDL_DestroyTexture(emptyCell);
    SDL_DestroyTexture(flag);
    SDL_DestroyTexture(mine);
    SDL_DestroyTexture(num1);
    SDL_DestroyTexture(num2);
    SDL_DestroyTexture(num3);
    SDL_DestroyTexture(num4);
    SDL_DestroyTexture(num5);
    SDL_DestroyTexture(num6);
    SDL_DestroyTexture(num7);
    SDL_DestroyTexture(num8);
}

SDL_Texture* Texture::loadTexture(const char* imageTitle)
{
    SDL_Surface* surface = IMG_Load(imageTitle);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}

void Texture::drawBackgroundTexture(const char* imageTitle)
{
    SDL_Texture* texture = loadTexture(imageTitle);

    SDL_RenderCopy(Game::renderer, texture, nullptr, nullptr);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(Game::renderer);
}

void Texture::drawTexture(SDL_Texture* texture, const int& x, const int& y)
{
    SDL_Rect desRect;

    desRect.x = x;
    desRect.y = y;

    SDL_QueryTexture(texture, nullptr, nullptr, &desRect.w, &desRect.h);
    SDL_RenderCopy(Game::renderer, texture, nullptr, &desRect);
    SDL_RenderPresent(Game::renderer);
}

void Texture::drawText(const std::string& input, SDL_Rect* desRect)
{
    SDL_Color textColor = { 0,0,0};
    std::string text = "__"; //left alignment
    text += input;

    while (text.length() < MAX_TEXT_LENGTH)
    {
        text += "_";
    }

    text += "_";

    SDL_Surface* surface = TTF_RenderText_Solid(Game::font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

    SDL_RenderCopy(Game::renderer, texture, nullptr, desRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_RenderPresent(Game::renderer);
}

SDL_Texture* Texture::getTexture(const int& t)
{
    SDL_Texture* texture = nullptr;

    switch (t)
    {
        case -2:
            texture = flag;
            break;
        case -1:
            texture = unopenedCell;
            break;
        case 0:
            texture = emptyCell;
            break;
        case 1:
            texture = num1;
            break;
        case 2:
            texture = num2;
            break;
        case 3:
            texture = num3;
            break;
        case 4:
            texture = num4;
            break;
        case 5:
            texture = num5;
            break;
        case 6:
            texture = num6;
            break;
        case 7:
            texture = num7;
            break;
        case 8:
            texture = num8;
            break;
        case 9:
            texture = mine;
            break;
        default:
            break;
    }

    return texture;
}