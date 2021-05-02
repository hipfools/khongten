#include "headers/Rect.h"

SDL_Rect sdlRect;

Rect::Rect(int _x, int _y, int _w, int _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

Rect::~Rect(){}

bool Rect::clickedInsideRect(int clickedX, int clickedY) const
{
    return (clickedX >= x && clickedY >= y && clickedX <= (x + w) && clickedY <= (y + h));
}


SDL_Rect* Rect::getRect() const
{
    sdlRect = {x, y, w, h};
    return &sdlRect;
}