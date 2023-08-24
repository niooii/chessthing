//
// Created by niooi on 8/20/23.
//

#ifndef OPENGL_CELL_H
#define OPENGL_CELL_H

#include <SDL.h>

class Cell {
private:
    SDL_Color initColor{};
    SDL_Color color{};
    SDL_Color highlightColor{};

    bool highlighted{false};

public:
    int row{}, col{};
    Cell(SDL_FRect Rect, SDL_Color FillColor, int Row, int Col) : rect(Rect), color(FillColor), row(Row), col(Col) {
        initColor = FillColor;
    }
    SDL_FRect rect{};

    SDL_Color Color();

    void Highlight(SDL_Color Highlightcolor);
    void Unhighlight();

//    int Row();
//    int Column();

    void SetColor(SDL_Color Col);
    void RevertToOriginalColor();

    void DrawCentered(SDL_Renderer* Renderer);
};


#endif //OPENGL_CELL_H
