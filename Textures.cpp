#include <iostream>
#include "Textures.h"

namespace Textures
{
    SDL_Texture* WhitePawn{nullptr};
    SDL_Texture* BlackPawn{nullptr};

    SDL_Texture* WhiteRook{nullptr};
    SDL_Texture* BlackRook{nullptr};

    SDL_Texture* WhiteKnight{nullptr};
    SDL_Texture* BlackKnight{nullptr};

    SDL_Texture* WhiteBishop{nullptr};
    SDL_Texture* BlackBishop{nullptr};

    SDL_Texture* WhiteQueen{nullptr};
    SDL_Texture* BlackQueen{nullptr};

    SDL_Texture* WhiteKing{nullptr};
    SDL_Texture* BlackKing{nullptr};

    void Generate(SDL_Renderer* Renderer)
    {
        WhitePawn = IMG_LoadTexture(Renderer, "../Pieces/Textures/whitepawn.png");
        BlackPawn = IMG_LoadTexture(Renderer, "../Pieces/Textures/blackpawn.png");
        WhiteRook = IMG_LoadTexture(Renderer, "../Pieces/Textures/whiterook.png");
        BlackRook = IMG_LoadTexture(Renderer, "../Pieces/Textures/blackrook.png");
        WhiteKnight = IMG_LoadTexture(Renderer, "../Pieces/Textures/whiteknight.png");
        BlackKnight = IMG_LoadTexture(Renderer, "../Pieces/Textures/blackknight.png");
        WhiteBishop = IMG_LoadTexture(Renderer, "../Pieces/Textures/whitebishop.png");
        BlackBishop = IMG_LoadTexture(Renderer, "../Pieces/Textures/blackbishop.png");
        WhiteQueen = IMG_LoadTexture(Renderer, "../Pieces/Textures/whitequeen.png");
        BlackQueen = IMG_LoadTexture(Renderer, "../Pieces/Textures/blackqueen.png");
        WhiteKing = IMG_LoadTexture(Renderer, "../Pieces/Textures/whiteking.png");
        BlackKing = IMG_LoadTexture(Renderer, "../Pieces/Textures/blackking.png");
        std::cout << "loaded textures!" << '\n';
    }
}