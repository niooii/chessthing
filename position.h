//
// Created by niooi on 8/23/23.
//

#ifndef OPENGL_POSITION_H
#define OPENGL_POSITION_H

#include "Enums.h"
#include "Pieces/Piece.h"
#include "Board.h"
#include <iostream>
#include <unordered_set>

class position {
private:
    TYPE piecetype;
    TEAM pieceteam;
    //needed for claculation and stuff
    Board* board;
    std::unordered_set<Piece*> pieces;
    std::unordered_set<Cell*> threateningCells;

    bool map[8][8] {0};

    std::unordered_set<Cell*> GetDangerCells(Piece* p);

public:
    position(TYPE PieceType, TEAM PieceTeam, Board* board);

    void Update();
    std::unordered_set<Cell*> ThreateningCells();

    TYPE PieceType();
    TEAM PieceTeam();

    void AddPiece(Piece* p);
    bool CellInDangerCells(Cell* c);
    void clearvec();

    //void SetThreateningCells(std::unordered_set<Cell*> tc);

};


#endif //OPENGL_POSITION_H
