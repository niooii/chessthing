//
// Created by niooi on 8/22/23.
//

#ifndef OPENGL_STRUCTS_H
#define OPENGL_STRUCTS_H

#include "Pieces/Piece.h"

struct Move {
    Move(Piece* piece, Cell* cell) : p(piece), c(cell){};
    Piece* p;
    Cell* c;
};

struct MoveLog {

    const char* PieceMovedID;
    const char* PieceKilledID;
    const char* PromotedPieceID;
    const char* MovedFrom;
    const char* MovedTo;
};

#endif //OPENGL_STRUCTS_H
