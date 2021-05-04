#ifndef MINESWEEPER_RECT_H
#define MINESWEEPER_RECT_H

#include <SDL.h>

class Rect
{
public:
    int x, y, w, h;

    Rect(int _x, int _y, int _w, int _h);
    ~Rect();

    bool clickedInsideRect(int clickedX, int clickedY) const;
    SDL_Rect* getRect() const;
};

#endif //MINESWEEPER_RECT_H
