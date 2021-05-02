#ifndef MINESWEEPER_TEXTURE_H
#define MINESWEEPER_TEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

const int MAX_TEXT_LENGTH = 7;

class Texture {

public:
    Texture();
    ~Texture();

    static SDL_Texture* loadTexture(const char* imageTitle);
    static void drawBackgroundTexture(const char* imageTitle);
    static void drawTexture(SDL_Texture* texture, const int& x, const int& y);
    static void drawText(const std::string& input, SDL_Rect *desRect);

    SDL_Texture* getTexture(const int& t);

private:
    SDL_Texture* unopenedCell;
    SDL_Texture* emptyCell;
    SDL_Texture* flag;
    SDL_Texture* mine;
    SDL_Texture* num1;
    SDL_Texture* num2;
    SDL_Texture* num3;
    SDL_Texture* num4;
    SDL_Texture* num5;
    SDL_Texture* num6;
    SDL_Texture* num7;
    SDL_Texture* num8;

};
#endif //MINESWEEPER_TEXTURE_H
