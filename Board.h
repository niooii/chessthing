//
// Created by niooi on 8/19/23.
//

#ifndef OPENGL_BOARD_H
#define OPENGL_BOARD_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Pieces/Piece.h"
#include "Cell.h"

//struct cell_
//{
//    cell_(SDL_FRect Rect, SDL_Color FillColor) : rect(Rect), color(FillColor) {}
//    SDL_FRect rect;
//    SDL_Color color;
//    Piece* piece{nullptr};
//};


class Board {
private:
std::vector<std::vector<Cell>> cells;

std::vector<Cell> WhiteCaptured;
int WhiteCapturedNum{};
std::vector<Cell> BlackCaptured;
int BlackCapturedNum{};

std::vector<Piece> pieces;

Cell* hoveredCell{nullptr};
Piece* activePiece{nullptr};

int p_c{}, q_c{}, b_c{}, k_c{}, r_c{};

int r;
int c;


public:
    Board(int Rows, int Cols, SDL_Color Color1, SDL_Color Color2, SDL_FRect GridArea);
    void DrawCentered(SDL_Renderer* Renderer);

    //if not found returns nullptr
    Cell* CellAtAbsPos(int x, int y);
    Cell* CellAtGridPos(int x, int y);

    void KillPiece(Piece* p);

    Cell* CellLeft(Cell* c);
    Cell* CellRight(Cell* c);
    Cell* CellTop(Cell* c);
    Cell* CellBottom(Cell* c);
    Cell* CellTopLeft(Cell* c);
    Cell* CellTopRight(Cell* c);
    Cell* CellBottomLeft(Cell* c);
    Cell* CellBottomRight(Cell* c);

    Piece* PieceAtCell(Cell* c);
    std::vector<Piece>& Pieces();

    void AddPiece(TYPE Type, TEAM Team, int row, int col);
    void HighlightCell(Cell* cell, SDL_Color color);
    void UnhighlightAll();

    int rows();
    int columns();

    void SetHoveredCell(Cell* c);

    //returns a garbage cell so calculations dont get affected
    Cell* TempCell();

    void Reset();

    void ChangePiece(Piece* p, TYPE type);

    const char* PieceToStr(Piece* p);
    Piece StrToPiece(const char* str);
    void SaveBoard(const char* filepath);
    void LoadBoard(const char* filepath);

    std::vector<std::vector<Cell>>& AllCells();
    void RevertAllCellColors();

};


#endif //OPENGL_BOARD_H
