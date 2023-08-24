//
// Created by niooi on 8/15/23.
//

#include <memory>
#include "GameWindow.h"

GameWindow::GameWindow(Uint8 Rows, Uint8 Cols, SDL_Color Color1, SDL_Color Color2, SDL_FRect GridArea)
 : game(Rows, Cols, Color1, Color2, GridArea) {

    SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &Window, &Renderer);

    SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);

    Textures::Generate(Renderer);

    std::shared_ptr<Agent> agent1 = std::make_shared<RandomAgent>(TEAM::WHITE);
    std::shared_ptr<Agent> agent2 = std::make_shared<RandomAgent>(TEAM::BLACK);

    game.SetAgents(agent1, agent2);
    game.InitPieces();
    game.positions().Init(&game.board);

    GameTimer.Reset();
}

double GameWindow::GetDeltaTime()
{
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    return ((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() ) * 0.001;
}

void GameWindow::Update()
{
    if(TriedQuit)
        Quit();

    HandleInput();

    double dt = GetDeltaTime();

    SDL_SetRenderDrawColor(Renderer, 30, 30, 30, 100);
    SDL_RenderClear(Renderer);

    if(autoplay)
    {
        STATE state = game.GetState();
        if(game.GameOver() && state != FATAL)
        {
            std::string s;
            if(state==WHITE_CHECKMATE)
                s = "White checkmated";
            else if(state == BLACK_CHECKMATE)
                s = "Black checkmated";
            else if(state==STALEMATE)
                s = "Stalemate";
            std::cout << s << " in " << GameTimer.ElapsedSeconds() << " seconds." << '\n';
            GameTimer.Reset();
            game.Reset();
        }
        if(Agent1Move)
        {
            Agent1Move = !Agent1Move;
            game.Agent1Move();
            game.board.RevertAllCellColors();
        }
        else
        {
            Agent1Move = !Agent1Move;
            game.Agent2Move();
            game.board.RevertAllCellColors();
        }
    }

    game.board.DrawCentered(Renderer);
//    std::unordered_set<Cell*> wdc = game.positions().DangerCells(WHITE);
//    std::unordered_set<Cell*> bdc = game.positions().DangerCells(BLACK);
//    for(Cell* c : wdc)
//    {
//        c->SetColor({0,255,0,255});
//    }
//    for(Cell* c : bdc)
//    {
//        if(wdc.size() != 0 && wdc.find(c) != wdc.end())
//        {
//            c->SetColor({255,0,255,255});
//        }
//        else
//            c->SetColor({0,0,255,255});
//    }

    //GPU_Blit(GPU_LoadImage("../Pieces/Textures/pawn.png"), NULL, Target, 200, 200);

    SDL_RenderPresent(Renderer);

//    for(Cell* c : wdc)
//    {
//        c->RevertToOriginalColor();
//    }
//    for(Cell* c : bdc)
//    {
//        c->RevertToOriginalColor();
//    }

}

void GameWindow::HandleInput() {
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                TriedQuit = true;
                break;

            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {

                    case SDLK_ESCAPE:
                        TriedQuit = true;
                        break;

                    case SDLK_r:
                        game.Reset();
                        break;

                    case SDLK_t:
                        if(Agent1Move)
                        {
                            Agent1Move = !Agent1Move;
                            game.Agent1Move();
                        }
                        else
                        {
                            Agent1Move = !Agent1Move;
                            game.Agent2Move();
                        }

                        break;

                    case SDLK_y:
                        autoplay = !autoplay;
                        break;
                }

                break;
            case SDL_WINDOWEVENT:

                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                        int w = event.window.data1;
                        int h = event.window.data2;
                        std::cout << "resized viewport to width: " << w << ", " << h << "\n";

                        break;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    Cell* c = game.board.CellAtAbsPos(event.button.x, event.button.y);
                    if(c == nullptr)
                        return;

                    if(game.ActivePiece() != nullptr)
                    {
                            if(game.IsAllowedMove(c))
                            {
                                game.DoMove({game.ActivePiece(), c});
                                game.board.RevertAllCellColors();
                            }
                    }

                    Piece* p;
                    if((p = game.board.PieceAtCell(c)) == nullptr)
                        return;
                    //delete later
                    //p = &game.board.Pieces().at(3); //this works
                    //p = game.board.CellAtGridPos(6, 1)->piece; //this doesnt work
                    std::cout << "you have " << game.AllLegalMoves(p->team).size() << " legal moves!" << '\n';
                    if(game.ActivePiece() == p)
                    {
                        game.UnsetActivePiece();
                        return;
                    }

                    if(game.ActivePiece() != nullptr)
                    {
                        game.UnsetActivePiece();
                    }

                    game.SetActivePiece(p);
                }
                break;

            case SDL_MOUSEMOTION:
                Cell* c;
                if((c = game.board.CellAtAbsPos(event.motion.x, event.motion.y)) != nullptr)
                {
                    //std::cout << (*c).rect.x << ", " << (*c).rect.y << '\n';
                    game.board.SetHoveredCell(c);
                }
                else
                {
                    game.board.SetHoveredCell(nullptr);
                }
                break;

            case SDL_MOUSEWHEEL:

                break;
        }
    }
}

void GameWindow::Quit() {
    //SDL_DestroyRenderer(Renderer);
    //SDL_Quit();
    //IMG_Quit();
    exit(0);
}