//
// Created by niooi on 8/19/23.
//

#include <utility>
#include "Game.h"

Game::Game(Uint8 Rows, Uint8 Cols, SDL_Color Color1, SDL_Color Color2, SDL_FRect GridArea)
: board(Rows, Cols, Color1, Color2, GridArea)
{
    state = IN_PROGRESS;
}

void Game::InitPieces()
{
    board.AddPiece(TYPE::ROOK, TEAM::BLACK, 0, 0);
    board.AddPiece(TYPE::KNIGHT, TEAM::BLACK, 0, 1);
    board.AddPiece(TYPE::BISHOP, TEAM::BLACK, 0, 2);
    board.AddPiece(TYPE::QUEEN, TEAM::BLACK, 0, 3);
    board.AddPiece(TYPE::KING, TEAM::BLACK, 0, 4);
    board.AddPiece(TYPE::BISHOP, TEAM::BLACK, 0, 5);
    board.AddPiece(TYPE::KNIGHT, TEAM::BLACK, 0, 6);
    board.AddPiece(TYPE::ROOK, TEAM::BLACK, 0, 7);
    board.AddPiece(TYPE::PAWN, TEAM::BLACK, 1, 0);
    board.AddPiece(TYPE::PAWN, TEAM::BLACK, 1, 1);
    board.AddPiece(TYPE::PAWN, TEAM::BLACK, 1, 2);
    board.AddPiece(TYPE::PAWN, TEAM::BLACK, 1, 3);
    board.AddPiece(TYPE::PAWN, TEAM::BLACK, 1, 4);
    board.AddPiece(TYPE::PAWN, TEAM::BLACK, 1, 5);
    board.AddPiece(TYPE::PAWN, TEAM::BLACK, 1, 6);
    board.AddPiece(TYPE::PAWN, TEAM::BLACK, 1, 7);

    board.AddPiece(TYPE::ROOK, TEAM::WHITE, 7, 0);
    board.AddPiece(TYPE::KNIGHT, TEAM::WHITE, 7, 1);
    board.AddPiece(TYPE::BISHOP, TEAM::WHITE, 7, 2);
    board.AddPiece(TYPE::QUEEN, TEAM::WHITE, 7, 3);
    board.AddPiece(TYPE::KING, TEAM::WHITE, 7, 4);
    board.AddPiece(TYPE::BISHOP, TEAM::WHITE, 7, 5);
    board.AddPiece(TYPE::KNIGHT, TEAM::WHITE, 7, 6);
    board.AddPiece(TYPE::ROOK, TEAM::WHITE, 7, 7);
    board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 7);
    board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 6);
    board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 5);
    board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 4);
    board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 3);
    board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 2);
    board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 1);
    board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 0);
    //board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 0);
    //board.AddPiece(TYPE::PAWN, TEAM::WHITE, 6, 4);
}

bool Game::SetActivePiece(Piece *p) {
    //unset all
//    activePiece = nullptr;
//    for(Cell* c : CurrentAllowedMoves)
//    {
//        c->RevertToOriginalColor();
////        std::cout << "unhighlighted cell_" << '\n';
//    }
//    CurrentAllowedMoves.clear();

    //set stuff
    activePiece = p;
    std::vector<Cell*> cells = LegalMoves(p);
    if(cells.size() == 0)
        return false;
    CurrentAllowedMoves = cells;
    for(Cell* c : CurrentAllowedMoves)
    {
        c->SetColor({255,0,0,255});
    }
    return true;
}

void Game::UnsetActivePiece() {
    activePiece = nullptr;
    for(Cell* c : CurrentAllowedMoves)
    {
        c->RevertToOriginalColor();
//        std::cout << "unhighlighted cell_" << '\n';
    }
    CurrentAllowedMoves.clear();
}

std::vector<Cell *> Game::LegalMoves(Piece *p) {
    std::vector<Cell *> t;
    int row = p->cell()->row;
    int column = p->cell()->col;
    //if kingcheck is true, apply moves before adding them to see if it would put king out of check.
    //made mistake, kingcheck always has to be true so a move that puts the king in danger cant be performed.
//    bool kingCheck{true};
//    if(KingInCheck(p->team))
//        kingCheck = true;
    switch(p->type)
    {
        case TYPE::KING:
        {
            Cell* start = p->cell();
            positionsobj.Update(p->type, p->team);
            //UpdateDangerCells(p->team == WHITE ? BLACK : WHITE);
            for(int it = 0; it < 8; it++)
            {
                Cell* temp;
                switch(it)
                {
                    case 0:
                        temp = board.CellTopLeft(start);
                        break;
                    case 1:
                        temp = board.CellTopRight(start);
                        break;
                    case 2:
                        temp = board.CellBottomLeft(start);
                        break;
                    case 3:
                        temp = board.CellBottomRight(start);
                        break;
                    case 4:
                        temp = board.CellLeft(start);
                        break;
                    case 5:
                        temp = board.CellRight(start);
                        break;
                    case 6:
                        temp = board.CellBottom(start);
                        break;
                    case 7:
                        temp = board.CellTop(start);
                        break;
                    default:
                        //no defalt for you
                        break;
                }
                if(temp != nullptr)
                {
                    std::unordered_set<Cell*> DangerCells = positionsobj.DangerCells(p->team == WHITE ? BLACK : WHITE);
                    if(DangerCells.find(temp) != DangerCells.end())
                    {
                        continue;
                    }

                    Piece* ptemp = board.PieceAtCell(temp);
                    if(ptemp == nullptr)
                    {
                        if(!IsCheckedAfterMove(p, temp))
                        {
                            t.emplace_back(temp);
                        }
                       // else if(!kingCheck)
//                        {
//                            t.emplace_back(temp);
//                        }
                    }
                    else if(ptemp->team != (p->team == WHITE ? WHITE : BLACK))
                    {
                        if(!IsCheckedAfterMove(p, temp))
                        {
                            t.emplace_back(temp);
                        }
//                        else if(!kingCheck)
//                        {
//                            t.emplace_back(temp);
//                        }
                    }
                }
            }
            break;
        }
        case TYPE::PAWN:
        {
            int moveDir = (p->team == TEAM::WHITE ? -1 : 1);
            int startingRow = (p->team == WHITE ? board.rows() - 2 : 1);
            Cell* start = p->cell();

            // Check for moving two squares forward
            if (row == startingRow) {
                Cell* twoAway = board.CellAtGridPos(row + 2 * moveDir, column);
                Cell* oneAway = board.CellAtGridPos(row + moveDir, column);

                if (twoAway != nullptr && board.PieceAtCell(twoAway) == nullptr &&
                    board.PieceAtCell(oneAway) == nullptr) {

                    if (!IsCheckedAfterMove(p, twoAway)) {
                        t.emplace_back(twoAway);
                    }
                }
            }

            // Check for moving one square forward
            Cell* oneForward = board.CellAtGridPos(row + moveDir, column);
            if (oneForward != nullptr && board.PieceAtCell(oneForward) == nullptr) {
                if (!IsCheckedAfterMove(p, oneForward)) {
                    t.emplace_back(oneForward);
                }
            }

            // Check for capturing diagonally
            for (int col_t = column - 1; col_t <= column + 1; col_t += 2) {
                Cell* c = board.CellAtGridPos(row + moveDir, col_t);

                if (c != nullptr) {
                    Piece* p_t = board.PieceAtCell(c);

                    if (p_t != nullptr && p_t->team != p->team) {
                        if (!IsCheckedAfterMove(p, c)) {
                            t.emplace_back(c);
                        }
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
                Cell *temp = board.CellAtGridPos(p->cell()->row + r[i], p->cell()->col + c[i]);
                if (temp != nullptr) {
                    Piece *pieceAtCell = board.PieceAtCell(temp);
                    if (pieceAtCell == nullptr) {
                        if(!IsCheckedAfterMove(p, temp))
                        {
                            t.emplace_back(temp);
                        }
//                        else if(!kingCheck)
//                        {
//                            t.emplace_back(temp);
//                        }
                        continue;
                    }
                    if ((pieceAtCell->team != (p->team == WHITE ? WHITE : BLACK))) {
                        if(!IsCheckedAfterMove(p, temp))
                        {
                            t.emplace_back(temp);
                        }
//                        else if(!kingCheck)
//                        {
//                            t.emplace_back(temp);
//                        }
                    }
                }
            }
            break;
        }

        case TYPE::ROOK:
        {
            Cell* start = p->cell();

            // Check in all four directions
            for (int dir = 0; dir < 4; dir++) {
                Cell* temp = start;

                while (true) {
                    switch (dir) {
                        case 0:
                            temp = board.CellTop(temp);
                            break;
                        case 1:
                            temp = board.CellRight(temp);
                            break;
                        case 2:
                            temp = board.CellBottom(temp);
                            break;
                        case 3:
                            temp = board.CellLeft(temp);
                            break;
                        default:
                            // No default for you
                            break;
                    }

                    if (temp != nullptr) {
                        Piece* pieceAtCell = board.PieceAtCell(temp);
                        if (pieceAtCell == nullptr) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(temp);
                            }
                        } else {
                            if (pieceAtCell->team != p->team) {
                                if (!IsCheckedAfterMove(p, temp)) {
                                    t.emplace_back(temp);
                                }
                            }
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
            break;
        }


        case TYPE::BISHOP:
        {
            Cell* start = p->cell();

            // Check in all four diagonal directions
            for (int dir = 0; dir < 4; dir++) {
                Cell* temp = start;

                while (true) {
                    switch (dir) {
                        case 0:
                            temp = board.CellTopLeft(temp);
                            break;
                        case 1:
                            temp = board.CellTopRight(temp);
                            break;
                        case 2:
                            temp = board.CellBottomLeft(temp);
                            break;
                        case 3:
                            temp = board.CellBottomRight(temp);
                            break;
                        default:
                            // No default for you
                            break;
                    }

                    if (temp != nullptr) {
                        Piece* pieceAtCell = board.PieceAtCell(temp);
                        if (pieceAtCell == nullptr) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(temp);
                            }
                        } else {
                            if (pieceAtCell->team != p->team) {
                                if (!IsCheckedAfterMove(p, temp)) {
                                    t.emplace_back(temp);
                                }
                            }
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
            break;
        }
            //i am god copy paste coder
        case TYPE::QUEEN:
        {
            Cell* start = p->cell();

            // Check in all eight possible directions (horizontally, vertically, and diagonally)
            for (int dir = 0; dir < 8; dir++) {
                Cell* temp = start;

                while (true) {
                    switch (dir) {
                        case 0:
                            temp = board.CellTopLeft(temp);
                            break;
                        case 1:
                            temp = board.CellTopRight(temp);
                            break;
                        case 2:
                            temp = board.CellBottomLeft(temp);
                            break;
                        case 3:
                            temp = board.CellBottomRight(temp);
                            break;
                        case 4:
                            temp = board.CellLeft(temp);
                            break;
                        case 5:
                            temp = board.CellRight(temp);
                            break;
                        case 6:
                            temp = board.CellBottom(temp);
                            break;
                        case 7:
                            temp = board.CellTop(temp);
                            break;
                        default:
                            // No default for you
                            break;
                    }

                    if (temp != nullptr) {
                        Piece* pieceAtCell = board.PieceAtCell(temp);
                        if (pieceAtCell == nullptr) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(temp);
                            }
                        } else {
                            if (pieceAtCell->team != p->team) {
                                if (!IsCheckedAfterMove(p, temp)) {
                                    t.emplace_back(temp);
                                }
                            }
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
            break;
        }

    }
    return t;
}

//void Game::UpdateDangerCells(TEAM enemy) {
//
//    enemy == WHITE ? WhiteThreatenedCells.clear() : BlackThreatenedCells.clear();
//
//    for(Piece& piece : board.Pieces())
//    {
//        if(piece.team != enemy || piece.IsDead)
//            continue;
//
//
//        for(Cell* c : ThreatenedCellsByPiece(&piece))
//        {
//            (enemy == WHITE ? WhiteThreatenedCells.insert(c) : BlackThreatenedCells.insert(c));
//        }
//
//    }
//}

Piece *Game::ActivePiece() {
    return activePiece;
}

bool Game::IsAllowedMove(Cell *c)
{
    for(Cell* cell : CurrentAllowedMoves)
    {
        if(c == cell)
            return true;
    }
    return false;
}

bool Game::KingInCheck(TEAM kingteam) {
    //UpdateDangerCells((kingteam == WHITE ? BLACK : WHITE));
    Piece* k = nullptr;
    for (Piece& p : board.Pieces()) {
        if (p.type == KING && p.team == kingteam) {
            k = &p;
            break;  // Exit the loop once the king is found
        }
    }
    std::unordered_set<Cell*> dangercells = positionsobj.DangerCells(kingteam == WHITE ? BLACK : WHITE);
    return dangercells.find(k->cell()) != dangercells.end();
}

bool Game::IsCheckedAfterMove(Piece *p, Cell *c)
{
    bool ret{false};
    Piece* tempkilled;
    Cell* tempPos;
    tempkilled = board.PieceAtCell(c);
    if(tempkilled != nullptr && tempkilled != p)
    {
        tempPos = tempkilled->cell();
        tempkilled->IsDead = true;
        tempkilled->Move(board.TempCell());
        positionsobj.Update(tempkilled->type, tempkilled->team);
    }
    Cell* orgPos = p->cell();

    std::unordered_set<TYPE> typesAttackingOriginalLocationWhite = positionsobj.TypesAttackingCell(orgPos, WHITE);
    std::unordered_set<TYPE> typesAttackingOriginalLocationBlack = positionsobj.TypesAttackingCell(orgPos, BLACK);

    p->Move(c);
    positionsobj.Update(p->type, p->team);

    for(TYPE t : typesAttackingOriginalLocationWhite)
    {
        if(t == PAWN || t == KING || t == KNIGHT)
            continue;
//        std::cout << "updating type " << t << '\n';
        positionsobj.Update(t, WHITE);
    }
    for(TYPE t : typesAttackingOriginalLocationBlack)
    {
        if(t == PAWN || t == KING || t == KNIGHT)
            continue;

        positionsobj.Update(t, BLACK);
    }

    if(KingInCheck(p->team))
    {
        ret = true;
    }

    p->Move(orgPos);
    if(tempkilled != nullptr && tempkilled != p)
    {
        tempkilled->IsDead = false;
        tempkilled->Move(tempPos);
        positionsobj.Update(tempkilled->type, tempkilled->team);
    }
    positionsobj.Update(p->type, p->team);

    for(TYPE t : typesAttackingOriginalLocationWhite)
    {
        if(t == PAWN || t == KING || t == KNIGHT)
            continue;

        positionsobj.Update(t, WHITE);
    }
    for(TYPE t : typesAttackingOriginalLocationBlack)
    {
        if(t == PAWN || t == KING || t == KNIGHT)
            continue;

        positionsobj.Update(t, BLACK);
    }

    return ret;
}

std::vector<Move> Game::AllLegalMoves(TEAM player) {
    std::vector<Move> moves;
    for(Piece& p : board.Pieces())
    {
        if(p.team != player || p.IsDead)
            continue;

        std::vector<Cell*> possible = LegalMoves(&p);
        for(Cell* c : possible)
        {
            moves.emplace_back(&p, c);
        }
    }
    return moves;
}

void Game::DoMove(Move m)
{
    Piece* p = m.p;
    Cell* c = m.c;
    //if promo == NONE, then it is not a promotionable move!

    if(p == nullptr)
        return;

    Cell* orgPos = p->cell();
    //use this for TypesAttackingCell
    //gave up on names, evidently.
    std::unordered_set<TYPE> typesAttackingOriginalLocationWhite = positionsobj.TypesAttackingCell(orgPos, WHITE);
    std::unordered_set<TYPE> typesAttackingOriginalLocationBlack = positionsobj.TypesAttackingCell(orgPos, BLACK);

    Piece* pieceatcell = board.PieceAtCell(c);
    if(pieceatcell != nullptr)
    {
        board.KillPiece(pieceatcell);
        positionsobj.Update(pieceatcell->type, pieceatcell->team);
    }
    p->Move(c);
    if(p->type == PAWN && (c->row == board.rows() - 1 || c->row == 0))
    {
        board.ChangePiece(p, QUEEN);
        positionsobj.Update(PAWN, p->team);
        positionsobj.AddNew(p);
    }
    positionsobj.Update(p->type, p->team);

    for(TYPE t : typesAttackingOriginalLocationWhite)
    {
        if(t == PAWN || t == KING || t == KNIGHT)
            continue;

        positionsobj.Update(t, WHITE);
    }
    for(TYPE t : typesAttackingOriginalLocationBlack)
    {
        if(t == PAWN || t == KING || t == KNIGHT)
            continue;

        positionsobj.Update(t, BLACK);
    }

}

void Game::SetAgents(std::shared_ptr<Agent> a1, std::shared_ptr<Agent> a2)
{
    Agent1 = std::move(a1);
    Agent2 = std::move(a2);
}

void Game::Reset()
{
    UnsetActivePiece();
    positionsobj.Reset();
    board.Reset();
    board.Pieces().clear();
    InitPieces();
    positionsobj.Init(&board);
    state = IN_PROGRESS;
}

void Game::Agent1Move()
{
    if(state != IN_PROGRESS)
        return;
    if(IsStalemate())
    {
        state = STALEMATE;
        return;
    }
    Move m = Agent1->GetMove(AllLegalMoves(Agent1->team));
    if(m.p == nullptr)
    {
        state = EndGame();
        return;
    }
//    if(board.PieceAtCell(m.c)!= nullptr && board.PieceAtCell(m.c)->type == KING)
//    {
//        std::cout << "king about to be eaten." << '\n';
//        std::cout << "MOVE: " << m.p->id() << " to (" << m.c->row << ", " << m.c->col << ")" << '\n';
//        state = FATAL;
//        return;
//    }
    DoMove(m);
}

void Game::Agent2Move()
{
    if(state != IN_PROGRESS)
        return;
    if(IsStalemate())
    {
        state = STALEMATE;
        return;
    }
    Move m = Agent2->GetMove(AllLegalMoves(Agent2->team));
    if(m.p == nullptr)
    {
        state = EndGame();
        return;
    }
    DoMove(m);
}

//this is only called when one side has no legal moves left.
STATE Game::EndGame() {
    if(KingInCheck(TEAM::WHITE))
    {
        return WHITE_CHECKMATE;
    }
    else if(KingInCheck(TEAM::BLACK))
    {
        return BLACK_CHECKMATE;
    }
    else
    {
        return STALEMATE;
    }
}

//insufficient material stalemate conditions
bool Game::IsStalemate()
{
    std::vector<Piece*> alive;
    int knights{};
    int bishops{};
    for(Piece& p : board.Pieces())
    {
        if(!p.IsDead)
        {
            alive.emplace_back(&p);
            if(p.type == BISHOP)
                bishops++;
            else if(p.type == KNIGHT)
                knights++;
        }
    }
    if(alive.size() == 2)
    {
        return true;
    }
    else if(alive.size() == 3)
    {
        if(knights == 1 || bishops == 1)
            return true;
    }
    return false;
}

bool Game::GameOver()
{
    return state != IN_PROGRESS;
}

STATE Game::GetState()
{
    return state;
}

std::unordered_set<Cell *> Game::ThreatenedCellsByPiece(Piece *piece)
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
                        tmp = board.CellTopLeft(start);
                        break;
                    case 1:
                        tmp = board.CellTopRight(start);
                        break;
                    case 2:
                        tmp = board.CellBottomLeft(start);
                        break;
                    case 3:
                        tmp = board.CellBottomRight(start);
                        break;
                    case 4:
                        tmp = board.CellLeft(start);
                        break;
                    case 5:
                        tmp = board.CellRight(start);
                        break;
                    case 6:
                        tmp = board.CellBottom(start);
                        break;
                    case 7:
                        tmp = board.CellTop(start);
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
                if ((c = board.CellAtGridPos(row + (piece->team == TEAM::WHITE ? -1 : 1), col_t)) != nullptr) {
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
                Cell *temp = board.CellAtGridPos(piece->cell()->row + r[i], piece->cell()->col + c[i]);
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
                            temp2 = board.CellTop(holder);
                            break;
                        case 1:
                            temp2 = board.CellRight(holder);
                            break;
                        case 2:
                            temp2 = board.CellBottom(holder);
                            break;
                        case 3:
                            temp2 = board.CellLeft(holder);
                            break;
                        default:
                            //no defalt for you
                            break;
                    }
                    if(temp2 != nullptr)
                    {
                        Piece* pieceatcell = board.PieceAtCell(temp2);
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
                            temp2 = board.CellTopLeft(holder);
                            break;
                        case 1:
                            temp2 = board.CellTopRight(holder);
                            break;
                        case 2:
                            temp2 = board.CellBottomLeft(holder);
                            break;
                        case 3:
                            temp2 = board.CellBottomRight(holder);
                            break;
                        default:
                            //no defalt for you
                            break;
                    }
                    if(temp2 != nullptr)
                    {
                        Piece* pieceatcell = board.PieceAtCell(temp2);
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
                            temp2 = board.CellTopLeft(holder);
                            break;
                        case 1:
                            temp2 = board.CellTopRight(holder);
                            break;
                        case 2:
                            temp2 = board.CellBottomLeft(holder);
                            break;
                        case 3:
                            temp2 = board.CellBottomRight(holder);
                            break;
                        case 4:
                            temp2 = board.CellLeft(holder);
                            break;
                        case 5:
                            temp2 = board.CellRight(holder);
                            break;
                        case 6:
                            temp2 = board.CellBottom(holder);
                            break;
                        case 7:
                            temp2 = board.CellTop(holder);
                            break;
                        default:
                            //no defalt for you
                            break;
                    }
                    if(temp2 != nullptr)
                    {
                        Piece* pieceatcell = board.PieceAtCell(temp2);
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

Positions &Game::positions() {
    return positionsobj;
}

//testament to an hour of debugging

//bool Game::CellInDanger(Cell *c, TEAM enemy)
//{
//    for(Piece& piece : board.Pieces())
//    {
//        if(piece.team != enemy || piece.IsDead)
//            continue;
//
//        if(piece.id()[0] == 'k')
//        {
//            std::vector<Cell*> attacked;
//
//            Cell* enemyKingCell = piece.cell();
//
//            attacked.push_back(board.CellTopLeft(enemyKingCell));
//            attacked.push_back(board.CellTop(enemyKingCell));
//            attacked.push_back(board.CellTopRight(enemyKingCell));
//            attacked.push_back(board.CellLeft(enemyKingCell));
//            attacked.push_back(board.CellRight(enemyKingCell));
//            attacked.push_back(board.CellBottomLeft(enemyKingCell));
//            attacked.push_back(board.CellBottom(enemyKingCell));
//            attacked.push_back(board.CellBottomRight(enemyKingCell));
//
//            for(Cell* tmp : attacked)
//            {
//                if(tmp != nullptr && tmp==c)
//                    return true;
//            }
//            continue;
//        }
//
//        std::vector<Cell*> attacked = LegalMoves(&piece);
//        if(std::find(attacked.begin(), attacked.end(), c) != attacked.end())
//            return true;
//
//    }
//
//    return false;
//}
//
