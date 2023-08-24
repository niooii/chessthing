//
// Created by niooi on 8/19/23.
//

#include <iostream>
#include <fstream>
#include <utility>
#include "Piece.h"

Piece::Piece(TYPE Type, TEAM Team, std::string id)
: type(Type), team(Team), identifier(std::move(id))
{
    switch (Type)
    {
        case TYPE::PAWN:
            tex = (Team == TEAM::WHITE ? Textures::WhitePawn : Textures::BlackPawn);
            points = 1;
            break;

        case TYPE::KING:
            tex = (Team == TEAM::WHITE ? Textures::WhiteKing : Textures::BlackKing);
            points = 0; // Assign the appropriate points for a king
            break;

        case TYPE::QUEEN:
            tex = (Team == TEAM::WHITE ? Textures::WhiteQueen : Textures::BlackQueen);
            points = 9; // Assign the appropriate points for a queen
            break;

        case TYPE::BISHOP:
            tex = (Team == TEAM::WHITE ? Textures::WhiteBishop : Textures::BlackBishop);
            points = 3; // Assign the appropriate points for a bishop
            break;

        case TYPE::KNIGHT:
            tex = (Team == TEAM::WHITE ? Textures::WhiteKnight : Textures::BlackKnight);
            points = 3; // Assign the appropriate points for a knight
            break;

        case TYPE::ROOK:
            tex = (Team == TEAM::WHITE ? Textures::WhiteRook : Textures::BlackRook);
            points = 5; // Assign the appropriate points for a rook
            break;

        default:
            std::cout << "Unsupported type" << '\n';
            break;
    }
    int w, h;
    SDL_QueryTexture(tex, 0, 0, &w, &h);
//    std::cout << w << ", " << h << '\n';
    dest.w = w;
    dest.h = h;
}

Piece::~Piece()
{
    //SDL_DestroyTexture(tex);
}

void Piece::DrawCentered(SDL_Renderer* Renderer, int x, int y)
{
    dest.x = x - dest.w/2;
    dest.y = y - dest.h/2;
    SDL_RenderCopy(Renderer, tex, NULL, &dest);
}

int Piece::Points() {
    return points;
}

SDL_FPoint Piece::AbsPos()
{
    return absPos;
}

void Piece::SetAbsPos(SDL_FPoint p)
{
    absPos = p;
}

Cell* Piece::cell()
{
    return cell_;
}

void Piece::SetCell(Cell *c)
{
    cell_ = c;
}

void Piece::Move(Cell *c)
{
    cell_ = c;
}

std::string Piece::id()
{
    return identifier;
}

void Piece::SetScale(float scaleX, float scaleY)
{
    dest.w = dest.w * scaleX;
    dest.h = dest.h * scaleY;
}

void Piece::ChangeTo(TYPE type, std::string id)
{
    TEAM Team = team;
    this->type = type;
    this->identifier = id;
    switch (type)
    {
        case TYPE::PAWN:
            tex = (Team == TEAM::WHITE ? Textures::WhitePawn : Textures::BlackPawn);
            points = 1;
            break;

        case TYPE::KING:
            tex = (Team == TEAM::WHITE ? Textures::WhiteKing : Textures::BlackKing);
            points = 0; // Assign the appropriate points for a king
            break;

        case TYPE::QUEEN:
            tex = (Team == TEAM::WHITE ? Textures::WhiteQueen : Textures::BlackQueen);
            points = 9; // Assign the appropriate points for a queen
            break;

        case TYPE::BISHOP:
            tex = (Team == TEAM::WHITE ? Textures::WhiteBishop : Textures::BlackBishop);
            points = 3; // Assign the appropriate points for a bishop
            break;

        case TYPE::KNIGHT:
            tex = (Team == TEAM::WHITE ? Textures::WhiteKnight : Textures::BlackKnight);
            points = 3; // Assign the appropriate points for a knight
            break;

        case TYPE::ROOK:
            tex = (Team == TEAM::WHITE ? Textures::WhiteRook : Textures::BlackRook);
            points = 5; // Assign the appropriate points for a rook
            break;

        default:
            std::cout << "Unsupported type" << '\n';
            break;
    }
}
