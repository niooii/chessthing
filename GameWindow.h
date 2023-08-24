//
// Created by niooi on 8/15/23.
//

#ifndef OPENGL_GAMEWINDOW_H
#define OPENGL_GAMEWINDOW_H

#include <vector>
#include <iostream>
#include "Textures.h"
#include "Board.h"
#include "Game.h"
#include "Utils/Timer.h"

class GameWindow {
private:
    //stuff for deltatime
    Uint64 NOW{SDL_GetPerformanceCounter()};
    Uint64 LAST;
    bool TriedQuit{false};

    SDL_Window* Window;
    SDL_Renderer* Renderer;

    Game game;
    Timer GameTimer{};

    // deltatime in seconds
    double GetDeltaTime();

    bool autoplay{false};
    bool Agent1Move{true};

public:
    SDL_Event event;

    bool DebugRender{true};

    GameWindow(Uint8 Rows, Uint8 Cols, SDL_Color Color1, SDL_Color Color2, SDL_FRect GridArea);
    // runs every frame
    void Update();

    void HandleInput();

    void Quit();

};


#endif //OPENGL_GAMEWINDOW_H
