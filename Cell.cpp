//
// Created by niooi on 8/20/23.
//

#include <iostream>
#include "Cell.h"

void Cell::Highlight(SDL_Color Highlightcolor)
{
    highlightColor = Highlightcolor;
    highlighted = true;
}

void Cell::Unhighlight()
{
    highlighted = false;
}

void Cell::DrawCentered(SDL_Renderer *Renderer)
{   (highlighted ? SDL_SetRenderDrawColor(Renderer, highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a) : SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a));

    SDL_RenderFillRectF(Renderer, &rect);
}

SDL_Color Cell::Color()
{
    return color;
}

void Cell::SetColor(SDL_Color Col) {
    color = Col;
}

void Cell::RevertToOriginalColor() {
    color = initColor;
}

//int Cell::Row() {
//    //std::cout << row << '\n';
//    return row;
//}
//
//int Cell::Column() {
//    return col;
//}
