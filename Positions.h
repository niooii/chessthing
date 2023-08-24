//
// Created by niooi on 8/23/23.
//

#ifndef OPENGL_POSITIONS_H
#define OPENGL_POSITIONS_H

#include <arrayfire.h>
#include <vector>
#include "Enums.h"
#include "position.h"

class Positions {
private:
    std::vector<position> posvec;

public:
    Positions();
    void Reset();
    void Init(Board* board);
    std::unordered_set<Cell*> DangerCells(TEAM Enemy);
    void Update(TYPE piecetype, TEAM teamtype);
    void AddNew(Piece* p);
    std::unordered_set<TYPE> TypesAttackingCell(Cell *c, TEAM AttackingTeam);
    af::array AsTensor();
};


#endif //OPENGL_POSITIONS_H
