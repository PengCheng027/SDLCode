#pragma once
#ifndef SHIP_HEAD
#define SHIP_HEAD

#include "Actor.h"
class Ship : public Actor
{
public:
    Ship();
    Ship(const Vector2 &pos, const float &width, const float &height,
         const float &rockSpeed_, const std::vector<SDL_Texture *> &actions,
         const int actionIndex = 0, State state_ = EActive);
    ~Ship() override;

    // Getters/setters speed
    const float &GetHorizonalSpeed() const { return mHorizonalSpeed; }
    void SetHorizonalSpeed(const float &speed) { mHorizonalSpeed = speed; }
    const float &GetVerticalSpeed() const { return mVerticalSpeed; }
    void SetVerticalSpeed(const float &speed) { mVerticalSpeed = speed; }

    void UpdateActor(const float &deltaTime) override;

    void ProcessInput(const uint8_t *keyState);

private:
    // Ship's speed
    float mHorizonalSpeed;
    float mVerticalSpeed;
};
#endif // !SHIP_HEAD