//
// Created by niooi on 8/23/23.
//

#include "position.h"

//void position::SetThreateningCells(std::unordered_set<Cell *> tc) {
//    threateningCells.clear();
//    threateningCells.insert(tc.begin(), tc.end());
//}

position::position(TYPE PieceType, TEAM PieceTeam, Board *board)
{
    piecetype = PieceType;
    pieceteam = PieceTeam;
    this->board = board;
}

std::unordered_set<Cell *> position::GetDangerCells(Piece *piece)
{
    std::unordered_set<Cell*> t;
    //slightly differnet logic
    int row = piece->cell()->row;
    int column = piece->cell()->col;
    switch(piece->type)
    {
        case TYPE::KING:
        {
            Cell* start = piece->cell();

            Cell* tmp;

            for(int i = 0; i < 8; i++)
            {
                switch(i)
                {
                    case 0:
                        tmp = board->CellTopLeft(start);
                        break;
                    case 1:
                        tmp = board->CellTopRight(start);
                        break;
                    case 2:
                        tmp = board->CellBottomLeft(start);
                        break;
                    case 3:
                        tmp = board->CellBottomRight(start);
                        break;
                    case 4:
                        tmp = board->CellLeft(start);
                        break;
                    case 5:
                        tmp = board->CellRight(start);
                        break;
                    case 6:
                        tmp = board->CellBottom(start);
                        break;
                    case 7:
                        tmp = board->CellTop(start);
                        break;
                    default:
                        //no defalt for you
                        break;
                }
                if(tmp != nullptr)
                {
                    t.insert(tmp);
                }
            }

            break;
        }
        case TYPE::PAWN:
        {
            //a square 2 ahead of a pawn will never be under attack by it.

            for (int col_t = column - 1; col_t < column + 2; col_t++) {
                Cell *c;
                if ((c = board->CellAtGridPos(row + (piece->team == TEAM::WHITE ? -1 : 1), col_t)) != nullptr) {
                    if ((col_t != column)) {
                        t.insert(c);
                    }
                }
            }
            break;
        }

        case TYPE::KNIGHT:
        {
            //possible knight moves
            int r[]{2, 2, -2, -2, -1, 1, -1, 1};
            int c[]{-1, 1, -1, 1, 2, 2, -2, -2};

            for (int i = 0; i < 8; i++) {
                Cell *temp = board->CellAtGridPos(piece->cell()->row + r[i], piece->cell()->col + c[i]);
                if (temp != nullptr) {
                    t.insert(temp);
                }
            }
            break;
        }

        case TYPE::ROOK:
        {
            Cell* start = piece->cell();
            Cell* holder = start;
            for(int it = 0; it < 4; it++)
            {
                for(int i = 0; i < 8; i++)
                {
                    Cell* temp2;
                    switch(it)
                    {
                        case 0:
                            temp2 = board->CellTop(holder);
                            break;
                        case 1:
                            temp2 = board->CellRight(holder);
                            break;
                        case 2:
                            temp2 = board->CellBottom(holder);
                            break;
                        case 3:
                            temp2 = board->CellLeft(holder);
                            break;
                        default:
                            //no defalt for you
                            break;
                    }
                    if(temp2 != nullptr)
                    {
                        Piece* pieceatcell = board->PieceAtCell(temp2);
                        if(pieceatcell == nullptr)
                            t.insert(temp2);
                        else
                        {
                            t.insert(temp2);
                            break;
                        }
                        holder = temp2;
                    }
                    else
                        break;
                }
                holder = start;
            }
            break;
        }

        case TYPE::BISHOP:
        {
            Cell* start = piece->cell();
            Cell* holder = start;
            for(int it = 0; it < 4; it++)
            {
                for(int i = 0; i < 8; i++)
                {
                    Cell* temp2;
                    switch(it)
                    {
                        case 0:
                            temp2 = board->CellTopLeft(holder);
                            break;
                        case 1:
                            temp2 = board->CellTopRight(holder);
                            break;
                        case 2:
                            temp2 = board->CellBottomLeft(holder);
                            break;
                        case 3:
                            temp2 = board->CellBottomRight(holder);
                            break;
                        default:
                            //no defalt for you
                            break;
                    }
                    if(temp2 != nullptr)
                    {
                        Piece* pieceatcell = board->PieceAtCell(temp2);
                        if(pieceatcell == nullptr)
                            t.insert(temp2);
                        else
                        {
                            t.insert(temp2);
                            break;
                        }
                        holder = temp2;
                    }
                    else
                        break;
                }

                holder = start;
            }
            break;
        }

            //i am god copy paste coder
        case TYPE::QUEEN:
        {
            Cell* start = piece->cell();
            Cell* holder = start;
            for(int it = 0; it < 8; it++)
            {
                for(int i = 0; i < 8; i++)
                {
                    Cell* temp2;
                    switch(it)
                    {
                        case 0:
                            temp2 = board->CellTopLeft(holder);
                            break;
                        case 1:
                            temp2 = board->CellTopRight(holder);
                            break;
                        case 2:
                            temp2 = board->CellBottomLeft(holder);
                            break;
                        case 3:
                            temp2 = board->CellBottomRight(holder);
                            break;
                        case 4:
                            temp2 = board->CellLeft(holder);
                            break;
                        case 5:
                            temp2 = board->CellRight(holder);
                            break;
                        case 6:
                            temp2 = board->CellBottom(holder);
                            break;
                        case 7:
                            temp2 = board->CellTop(holder);
                            break;
                        default:
                            //no defalt for you
                            break;
                    }
                    if(temp2 != nullptr)
                    {
                        Piece* pieceatcell = board->PieceAtCell(temp2);
                        if(pieceatcell == nullptr)
                            t.insert(temp2);
                        else
                        {
                            t.insert(temp2);
                            break;
                        }
                        holder = temp2;
                    }
                    else
                        break;
                }

                holder = start;
            }
            break;
        }

    }

    return t;
}

void position::Update()
{
    //BEWARE OF MEMORY ISSUES!
    threateningCells.clear();
    memset(map, 0, sizeof(map));
    std::unordered_set<Cell*> attacking;
    for(Piece* p : pieces)
    {
        //remove piece if its type has changed(eg pawn)
        if(piecetype == PAWN)
        {
            if(p->type != PAWN)
            {
                pieces.erase(p);
                continue;
            }
        }
//        if(!p->IsDead && !(p->cell()->row < 8 && p->cell()->row >=0))
//        {
//            pieces.erase(p);
//            continue;
//        }
        if(!p->IsDead)
        {
            map[p->cell()->row][p->cell()->col] = 1;
        }
        attacking = GetDangerCells(p);
        threateningCells.insert(attacking.begin(), attacking.end());
    }
}

TYPE position::PieceType()
{
    return piecetype;
}

TEAM position::PieceTeam()
{
    return pieceteam;
}

void position::AddPiece(Piece *p) {
    pieces.insert(p);
}

std::unordered_set<Cell *> position::ThreateningCells() {
    return threateningCells;
}

bool position::CellInDangerCells(Cell *c) {
    return threateningCells.find(c) != threateningCells.end();
}

void position::clearvec() {
    pieces.clear();
}
