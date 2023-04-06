#include "Actor.h"

Actor::Actor()
{
    mPosition = Vector2::Zero;
    mRect = {0, 0, 0, 0};
    rockSpeed = 0.0f;
    mActionIndex = 0;
    state = EActive;
    rockIndex = 0.0f;
    mActorTextures.clear();
}

Actor::Actor(const Vector2 &pos, const float &width, const float &height,
             const float &rockSpeed_, const std::vector<SDL_Texture *> &actions,
             const int actionIndex, State state_ )
{
    mPosition = pos;
    mRect = {
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        static_cast<int>(width),
        static_cast<int>(height)};
    rockSpeed = rockSpeed_;
    mActorTextures = actions;
    mActionIndex = actionIndex;
    state = state_;
    rockIndex = 0.0f;
}

Actor::~Actor()
{
    // Destroy textures
    for (auto texture : mActorTextures)
    {
        SDL_DestroyTexture(texture);
    }

    mActorTextures.clear();
}

void Actor::UpdateActor(const float &deltaTime)
{
    return;
}
