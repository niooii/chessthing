//
// Created by niooi on 8/19/23.
//

#ifndef OPENGL_GAME_H
#define OPENGL_GAME_H

#include <algorithm>
#include "Board.h"
#include <SDL_image.h>
#include <memory>
#include "Textures.h"
#include "Structs.h"
#include "Agents/Agent.h"
#include "Agents/RandomAgent.h"
#include "Positions.h"
#include <unordered_set>

class Game {
private:
    Piece* activePiece{nullptr};
    std::vector<Cell*> CurrentAllowedMoves;

    Positions positionsobj;

    std::shared_ptr<Agent> Agent1;
    std::shared_ptr<Agent> Agent2;

//    //threatened cells BY white
//    std::unordered_set<Cell*> WhiteThreatenedCells;
//    //threatened cells BY black
//    std::unordered_set<Cell*> BlackThreatenedCells;

    STATE state;

public:
    Game(Uint8 Rows, Uint8 Cols, SDL_Color Color1, SDL_Color Color2, SDL_FRect GridArea);

    Board board;

    void InitPieces();

    bool SetActivePiece(Piece* p);
    void UnsetActivePiece();
    bool IsAllowedMove(Cell* c);
    bool KingInCheck(TEAM kingteam);
    //bad name. this applys a move temporarily and checks if the king for the side that moved is still in check.
    bool IsCheckedAfterMove(Piece* p, Cell* c);
    Piece* ActivePiece();
    std::vector<Cell*> LegalMoves(Piece* p);
    std::vector<Move> AllLegalMoves(TEAM player);
    //void UpdateDangerCells(TEAM enemy);
    std::unordered_set<Cell*> ThreatenedCellsByPiece(Piece* p);
    void SetAgents(std::shared_ptr<Agent> a1, std::shared_ptr<Agent> a2);
    void DoMove(Move m);

    void Reset();
    void Agent1Move();
    void Agent2Move();
    bool IsStalemate();
    bool GameOver();

    STATE GetState();
    STATE EndGame();

    Positions& positions();



};


#endif //OPENGL_GAME_H
