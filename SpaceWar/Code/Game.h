#pragma once
#ifndef GAME_HEAD
#define GAME_HEAD
#include "Actor.h"
#include "Ship.h"
class Game
{
public:
    Game();
    ~Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(Actor *actor);
    void RemoveActor(Actor *actor);

    SDL_Texture *GetTexture(const std::string &fileName);

    void DrawActor(Actor *actor);

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    // All the acotrs in the game
    std::vector<Actor *> mActors;

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;

    // Game-specific
    Ship *mShip;
};
#endif // !GAME_HEAD
