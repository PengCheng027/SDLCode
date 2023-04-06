#include "Game.h"

Game::Game()
{
    mWindow = nullptr;
    mRenderer = nullptr;
    mTicksCount = 0;
    mIsRunning = true;
    mShip = nullptr;
    mActors.clear();
}

Game::~Game()
{
    while (!mActors.empty())
    {
        delete mActors.back();
        mActors.pop_back();
    }

    return;
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 1)", 100, 100, 1024, 768, 0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    LoadData();
    mTicksCount = SDL_GetTicks();
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

SDL_Texture *Game::GetTexture(const std::string &fileName)
{
    SDL_Texture *tex = nullptr;
    SDL_Surface *surf = nullptr;

    surf = IMG_Load(fileName.c_str());
    if (!surf)
    {
        SDL_Log("Failed to load texture file %s", fileName.c_str());
        return nullptr;
    }

    tex = SDL_CreateTextureFromSurface(mRenderer, surf);
    if (!tex)
    {
        SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
        return nullptr;
    }

    return tex;
}

void Game::DrawActor(Actor *actor)
{
    SDL_Rect r;
    r = actor->GetRect();
    r.w = r.w * 1.5f;
    r.h = r.h * 1.5f;
    int actionIndex = actor->GetActionIndex();
    SDL_Texture *tex = actor->GetActorTextures()[actionIndex];

    SDL_RenderCopyEx(mRenderer, tex, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
}

void Game::LoadData()
{
    // Create player's ship
    mShip = new Ship();
    mShip->SetPosition(Vector2(100.0f, 384.0f));
    mShip->SetActionIndex(0);
    mShip->SetRockIndex(0.0f);
    mShip->SetRockSpeed(0.3f);
    mShip->SetState(Actor::State::EActive);
    // Load textures
    std::vector<SDL_Texture *> shipTextures{
        GetTexture("Assets/Ship01.png"),
        GetTexture("Assets/Ship02.png"),
        GetTexture("Assets/Ship03.png"),
        GetTexture("Assets/Ship04.png")};

    mShip->SetActorTextures(shipTextures);

    // Add to actors
    AddActor(mShip);
}

void Game::UnloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back();
        mActors.pop_back();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const uint8_t *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }

    // Process ship input
    mShip->ProcessInput(state);
}

void Game::UpdateGame()
{
    // Compute delta time
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    // Update all actors
    for (auto actor : mActors)
    {
        actor->UpdateActor(deltaTime);
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    // Draw all actors
    for (auto actor : mActors)
    {
        DrawActor(actor);
    }

    SDL_RenderPresent(mRenderer);
}

void Game::AddActor(Actor *actor)
{
    if (actor)
    {
        mActors.push_back(actor);
    }
    return;
}

void Game::RemoveActor(Actor *actor)
{
    auto iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
    return;
}