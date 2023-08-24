//
// Created by niooi on 8/19/23.
//

#include "Board.h"

Board::Board(int Rows, int Cols, SDL_Color Color1, SDL_Color Color2, SDL_FRect GridArea) : r(Rows), c(Cols) {
    for(int i = 0; i < Rows; i++)
    {
        cells.emplace_back();
        for(int j = 0; j < Cols; j++)
        {
            cells.at(i).emplace_back(Cell({0,0,0,0},{0,0,0,0}, i, j));
        }
    }

    for(int i = 0; i < Rows; i++)
    {
        for(int j = 0; j < Cols; j++)
        {
            float cw = (GridArea.w/Cols);
            float ch = (GridArea.h/Rows);
            float cx = GridArea.x + (float)j * cw;
            float cy = GridArea.y + (float)i * ch;
            cells[i][j] = Cell({cx, cy, cw, ch},
                               //amazing ternary here
                               (j % 2 == (i % 2 == 0 ? 0 : 1) ? Color1 : Color2), i, j);
        }
    }

    for(int j = 0; j < Cols * 2; j++)
    {
        float cw = (GridArea.w/Cols)/2;
        float ch = (GridArea.h/Rows)/2;
        float cx = GridArea.x + (float)j * cw;
        float cy = cells[0][0].rect.y - ch;
        Cell c_t{{cx, cy, cw, ch}, {255,255,255,255}, -1, j};
        BlackCaptured.emplace_back(c_t);
    }

    for(int j = 0; j < Cols * 2; j++)
    {
        float cw = (GridArea.w/Cols)/2;
        float ch = (GridArea.h/Rows)/2;
        float cx = GridArea.x + (float)j * cw;
        float cy = cells[7][0].rect.y + ch * 2;
        Cell c_t{{cx, cy, cw, ch}, {255,255,255,255}, -1, j};
        WhiteCaptured.emplace_back(c_t);
    }
}

void Board::DrawCentered(SDL_Renderer* Renderer) {
    for(auto& cellvec : cells)
    {
        for(auto& cell : cellvec)
        {
            cell.DrawCentered(Renderer);
        }
    }

    for(auto& cell : WhiteCaptured)
    {
        cell.DrawCentered(Renderer);
    }

    for(auto& cell : BlackCaptured)
    {
        cell.DrawCentered(Renderer);
    }

    for(auto& piece : pieces)
    {
        Cell* c = piece.cell();
        piece.DrawCentered(Renderer, c->rect.x + c->rect.w/2, c->rect.y + c->rect.h/2);
    }
}

Cell* Board::CellAtAbsPos(int x, int y) {
    //you dont need to optimize you dont need it dont optimize don od it
    for(auto& cellvec : cells)
    {
        for(auto& cell : cellvec)
        {
            if(x >= cell.rect.x && x <= (cell.rect.x + cell.rect.w)
            && y >= cell.rect.y && y <= (cell.rect.y + cell.rect.h))
                return &cell;
        }
    }
    return nullptr;
}

Cell* Board::CellAtGridPos(int row, int col) {
    //you dont need to optimize you dont need it dont optimize don od it
    if(row > r - 1 || col > c - 1 || row < 0 || col < 0)
        return nullptr;
    return &cells[row][col];
}

void Board::AddPiece(TYPE Type, TEAM Team, int row, int col) {
    Cell* cell = CellAtGridPos(row, col);

    if(cell == nullptr)
        return;
    std::string id;
    switch(Type)
    {
        case TYPE::PAWN:
            id = "p" + std::to_string(p_c++);
            break;

        case TYPE::KING:
            id = "k";
            break;

        case TYPE::QUEEN:
            id = "q" + std::to_string(q_c++);
            break;

        case TYPE::BISHOP:
            id = "b" + std::to_string(b_c++);
            break;

        case TYPE::KNIGHT:
            id = "k" + std::to_string(k_c++);
            break;

        case TYPE::ROOK:
            id = "r" + std::to_string(r_c++);
            break;
    }

    Piece p(Type, Team, id);
    p.SetCell(cell);

    pieces.push_back(p);
}

void Board::HighlightCell(Cell *cell, SDL_Color color)
{
    cell->Highlight(color);
}

void Board::UnhighlightAll()
{
    for(auto& cellvec : cells)
    {
        for(auto& cell : cellvec)
        {
            cell.Unhighlight();
        }
    }
}

void Board::SetHoveredCell(Cell *c)
{
    if(hoveredCell != nullptr)
        hoveredCell->Unhighlight();
    hoveredCell = c;
    if(hoveredCell != nullptr)
    {
        SDL_Color t = hoveredCell->Color();
        t.a = 150;
        hoveredCell->Highlight(t);
    }

}

Piece* Board::PieceAtCell(Cell *c)
{
    if(c == nullptr)
        return nullptr;
    else
    {
        for(Piece& p : pieces)
        {
            if(p.cell() == c)
                return &p;
        }
        return nullptr;
    }
}

std::vector<Piece> &Board::Pieces()
{
    return pieces;
}

int Board::rows() {
    return r;
}

int Board::columns() {
    return c;
}

Cell *Board::CellLeft(Cell *c) {
    return CellAtGridPos(c->row, c->col-1);
}

Cell *Board::CellRight(Cell *c) {
    return CellAtGridPos(c->row, c->col+1);
}

Cell *Board::CellTop(Cell *c) {
    return CellAtGridPos(c->row - 1, c->col);
}

Cell *Board::CellBottom(Cell *c) {
    return CellAtGridPos(c->row + 1, c->col);
}

Cell *Board::CellTopLeft(Cell *c) {
    return CellAtGridPos(c->row - 1, c->col - 1);
}

Cell *Board::CellTopRight(Cell *c) {
    return CellAtGridPos(c->row - 1, c->col + 1);
}

Cell *Board::CellBottomLeft(Cell *c) {
    return CellAtGridPos(c->row + 1, c->col - 1);
}

Cell *Board::CellBottomRight(Cell *c) {
    return CellAtGridPos(c->row + 1, c->col + 1);
}

void Board::KillPiece(Piece *p) {
    Cell* c;
    if(p->team == WHITE)
    {
        c = &BlackCaptured[BlackCapturedNum++];
    }
    else
    {
        c = &WhiteCaptured[WhiteCapturedNum++];
    }
    p->SetCell(c);
    p->SetScale(0.5, 0.5);
    p->IsDead = true;
}

Cell *Board::TempCell()
{
    return &WhiteCaptured[0];
}

void Board::Reset()
{
    WhiteCapturedNum = 0;
    BlackCapturedNum = 0;
    p_c = 0;
    q_c = 0;
    b_c = 0;
    k_c = 0;
    r_c = 0;
}

void Board::ChangePiece(Piece *p, TYPE type) {
    std::string id;
    switch(type)
    {
        case TYPE::PAWN:
            id = "p" + std::to_string(p_c++);
            break;

        case TYPE::KING:
            id = "k";
            break;

        case TYPE::QUEEN:
            id = "q" + std::to_string(q_c++);
            break;

        case TYPE::BISHOP:
            id = "b" + std::to_string(b_c++);
            break;

        case TYPE::KNIGHT:
            id = "k" + std::to_string(k_c++);
            break;

        case TYPE::ROOK:
            id = "r" + std::to_string(r_c++);
            break;
    }
    p->ChangeTo(type, id);
}

std::vector<std::vector<Cell>>& Board::AllCells() {
    return cells;
}

void Board::RevertAllCellColors()
{
    for(std::vector<Cell>& cvec : cells)
    {
        for(Cell& cell : cvec)
        {
            cell.RevertToOriginalColor();
        }
    }
}
