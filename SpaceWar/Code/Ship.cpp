#include "Ship.h"

Ship::Ship()
{
    mPosition = Vector2::Zero;
    mRect = {0, 0, 0, 0};
    rockSpeed = 0.0f;
    mActionIndex = 0;
    state = EActive;
    mHorizonalSpeed = 0.0f;
    mVerticalSpeed = 0.0f;
}

Ship::Ship(const Vector2 &pos, const float &width, const float &height,
           const float &rockSpeed_, const std::vector<SDL_Texture *> &actions,
           const int actionIndex, State state_ )
{
    Actor(pos, width, height, rockSpeed_, actions, actionIndex, state_);
    mHorizonalSpeed = 0.0f;
    mVerticalSpeed = 0.0f;
}

Ship::~Ship()
{
    return;
}

void Ship::ProcessInput(const uint8_t *keyState)
{
    mHorizonalSpeed = 0.0f;
    mVerticalSpeed = 0.0f;
    if (keyState[SDL_SCANCODE_D])
    {
        mHorizonalSpeed += 250.0f;
    }
    if (keyState[SDL_SCANCODE_A])
    {
        mHorizonalSpeed -= 250.0f;
    }
    if (keyState[SDL_SCANCODE_W])
    {
        mVerticalSpeed -= 250.0f;
    }
    if (keyState[SDL_SCANCODE_S])
    {
        mVerticalSpeed += 250.0f;
    }

    return;
}

void Ship::UpdateActor(const float &deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // Update position based on speed and delta time
    Vector2 pos = GetPosition();
    pos.x += mHorizonalSpeed * deltaTime;
    pos.y += mVerticalSpeed * deltaTime;

    // Restrict ship to left half of screen
    if (pos.x < 0.0f)
    {
        pos.x = 0.0f;
    }
    else if (pos.x + GetWidth() * 1.5 > 512.0f)
    {
        pos.x = 512.0f - GetWidth() * 1.5;
    }
    if (pos.y < 0.0f)
    {
        pos.y = 0.0f;
    }
    else if (pos.y + GetHeight() * 1.5 > 768.0f)
    {
        pos.y = 768.0f - GetHeight() * 1.5;
    }

    SetPosition(pos);

    rockIndex += rockSpeed;
    if (rockIndex >= 1)
    {
        mActionIndex += 1;
        mActionIndex %= mActorTextures.size();
        rockIndex = 0.0f;
    }

    mRect.x = static_cast<int>(pos.x);
    mRect.y = static_cast<int>(pos.y);
    SDL_QueryTexture(mActorTextures[mActionIndex], nullptr, nullptr, &mRect.w, &mRect.h);
}
