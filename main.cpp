#include <SDL.h>
#undef main
#include <iostream>
#include <arrayfire.h>
#include "GameWindow.h"

int main(int argc, char **argv) {
    //af::setBackend(AF_BACKEND_CUDA);

    SDL_Color c1 {255,255,255,255};
    SDL_Color c2 {50,150,50,255};

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    int ROWS = 8;
    int COLS = 8;

    GameWindow gw(ROWS, COLS, c1, c2, {100, 100, 600, 600});

    while (true)
    {
        //Images::pawn = GPU_LoadImage("../Pieces/Textures/pawn.png");

        gw.Update();

    }


    return 0;
}