//
// Created by niooi on 8/19/23.
//

#ifndef OPENGL_PIECE_H
#define OPENGL_PIECE_H

#include <SDL.h>
#include "../Textures.h"
#include "../Cell.h"
#include "../Enums.h"
#include <string>

class Piece {
protected:
    SDL_Rect dest{};
    SDL_Texture* tex;

    SDL_Point boardPos{};
    SDL_FPoint absPos{};

    int points;
    int row;
    int col;
    std::string identifier;

    Cell* cell_;

public:
    TYPE type;
    TEAM team;
    bool IsDead{false};

    Piece(TYPE type, TEAM team, std::string id);
    ~Piece();



    int Points();
    SDL_FPoint AbsPos();
    void SetAbsPos(SDL_FPoint p);
    void DrawCentered(SDL_Renderer* Renderer, int x, int y);
    Cell* cell();
    void SetCell(Cell* c);
    void Move(Cell* c);
    std::string id();
    void SetScale(float scaleX, float scaleY);
    void ChangeTo(TYPE type, std::string id);

};


#endif //OPENGL_PIECE_H
