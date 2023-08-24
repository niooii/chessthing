//
// Created by niooi on 8/22/23.
//

#ifndef OPENGL_ENUMS_H
#define OPENGL_ENUMS_H

enum TYPE
{
    PAWN,
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    NONE
};

enum TEAM
{
    WHITE,
    BLACK
};

enum STATE
{
    IN_PROGRESS,
    WHITE_CHECKMATE,
    BLACK_CHECKMATE,
    STALEMATE,
    FATAL,
};

#endif //OPENGL_ENUMS_H
