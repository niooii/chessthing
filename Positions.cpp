//
// Created by niooi on 8/23/23.
//

#include "Positions.h"

Positions::Positions() = default;

void Positions::Init(Board *board)
{
    posvec.clear();
    //there are a trillion reasons why a bug could happen here
    for(Piece& p : board->Pieces())
    {
        bool has{false};
        position* toadd;
        for(position& pos : posvec)
        {
            if(pos.PieceType() == p.type && pos.PieceTeam() == p.team)
            {
                has = true;
                toadd = &pos;
                break;
            }
        }
        if(has)
        {
            toadd->AddPiece(&p);
        }
        else
        {
            posvec.emplace_back(p.type, p.team, board);
            posvec.at(posvec.size()-1).AddPiece(&p);
        }
    }
    for(position& pos : posvec)
    {
        pos.Update();
    }
}

void Positions::Update(TYPE piecetype, TEAM pieceteam)
{
    for(position& p : posvec)
    {
        if(p.PieceType() == piecetype && p.PieceTeam() == pieceteam)
        {
            p.Update();
        }
    }
}

std::unordered_set<Cell *> Positions::DangerCells(TEAM Enemy) {
    std::unordered_set<Cell*> cells;
    for(position& posobj : posvec)
    {
        if(posobj.PieceTeam() == Enemy)
        {
            std::unordered_set<Cell*> t = posobj.ThreateningCells();
            cells.insert(t.begin(), t.end());
        }
    }
    return cells;
}

void Positions::AddNew(Piece *p)
{
    for(position& pos : posvec)
    {
        if(pos.PieceType() == p->type && pos.PieceTeam() == p->team)
        {
            pos.AddPiece(p);
        }
    }
}

std::unordered_set<TYPE> Positions::TypesAttackingCell(Cell *c, TEAM AttackingTeam)
{
    std::unordered_set<TYPE> types;

    for(position& p : posvec)
    {
        if(p.PieceTeam() == AttackingTeam && p.CellInDangerCells(c))
        {
            types.insert(p.PieceType());
        }
    }

    return types;
}

void Positions::Reset()
{
    for(position& p : posvec)
    {
        p.clearvec();
    }
    posvec.clear();
}
